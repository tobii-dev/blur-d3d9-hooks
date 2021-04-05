#include <Windows.h>
#include <iostream>
#include <string>

#include "mem.h"


fn_ptr_t install_void_hook(void* src, fn_ptr_t f, int len) {
	//alloc trampoline
	LPVOID trampolineAddr = VirtualAlloc(0, len+OP_JMP_LEN, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (trampolineAddr) {
		//allow read-write
		DWORD srcProtection, _;
		VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &srcProtection);
		//save org bytes in the allocated mem
		memcpy(trampolineAddr, src, len);
		memset(src, OP_NOP, len); // set the rest to nops just in case

		// place a jump at the bottom of the bytes, so we can go back to the original function
		uintptr_t jmpInsAddr = (uintptr_t) trampolineAddr + len;
		uintptr_t relAddr = (uintptr_t) src - jmpInsAddr; //jmp from trampoline+len back to src+len)
		uint8_t jmpIns[OP_JMP_LEN];
		jmpIns[0] = OP_JMP;
		*(uintptr_t*)&jmpIns[1] = relAddr;
		memcpy((void*)jmpInsAddr, jmpIns, OP_JMP_LEN);

		//create hook
		//now replace src with a jump to hook;
		relAddr = (uintptr_t) f - (uintptr_t) src - OP_JMP_LEN; //jmp from src to f
		*(uintptr_t*)&jmpIns[1] = relAddr;
		memcpy(src, jmpIns, OP_JMP_LEN);

		//restore stuffs
		VirtualProtect(src, len, srcProtection, &_);
	}
	return (fn_ptr_t) trampolineAddr;
}


//uintptr_t follow_offsets(uintptr_t ptr, std::vector<unsigned int> offsets) {
uintptr_t follow_offsets(uintptr_t ptr, std::vector<uintptr_t> offsets) {
    uintptr_t addr = ptr;
	//uintptr_t tmp;
	//DWORD srcProtection, _;
    for (unsigned int i = 0; i<offsets.size(); i++) {
		//VirtualProtect((void*)addr, sizeof(addr), PAGE_EXECUTE_READWRITE, &srcProtection);
		//tmp = addr;
        addr = *(uintptr_t*) addr;
		if (addr != NULL) {
			addr += offsets[i];
			//restore stuffs
			//VirtualProtect((void*)tmp, sizeof(tmp), srcProtection, &_);
		} else {
			//VirtualProtect((void*)tmp, sizeof(tmp), srcProtection, &_);
			break;
		}
    }
    return addr;
}



bool __stdcall set_call_func(void* src, fn_ptr_t f) {
	bool ok = false;
	void* callArg = VirtualAlloc(0, sizeof(uintptr_t), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (callArg) {
		*(uintptr_t*)callArg = (uintptr_t) f;
		DWORD srcProtection, _;
		VirtualProtect(src, OP_CALL_LEN, PAGE_EXECUTE_READWRITE, &srcProtection);
		*(uintptr_t*)(((uint8_t*)src) + 2) = (uintptr_t)callArg;
		VirtualProtect(src, OP_CALL_LEN, srcProtection, &_);
		ok = true;
	}
	return ok;
}


bool set_nops(void* dst, unsigned int len) {
	bool ok = false;
	if ((len > 0) && (dst != NULL)) {
		DWORD org, _;
		uint8_t* ptr = (uint8_t*) dst;
		VirtualProtect(dst, len, PAGE_EXECUTE_READWRITE, &org);
		for (unsigned int i = 0; i < len; i++) ptr[i] = OP_NOP;
		VirtualProtect(dst, len, org, &_);
		ok = true;
	}
	return ok;
}
