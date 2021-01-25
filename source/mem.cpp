#include <Windows.h>
#include <iostream>

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
