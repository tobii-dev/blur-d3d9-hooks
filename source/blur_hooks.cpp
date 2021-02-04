#include <stdio.h>

#include "blur_hooks.h"
#include "blur.h"
#include "mem.h"


bool install_menu_hook() {
	return install_menu_hook(fn_hello_world);
}


bool install_menu_hook(fn_ptr_t fn) {
	bool hooked = false;
	uintptr_t src = blurAPI->moduleBase + HOOK_MENU_FUNC_ADDY;
	fn_ptr_t t = install_void_hook((void*) src, hook_menu_leave, HOOK_MENU_FUNC_INS_LEN);
	if (t) {
		blurAPI->hooks.fn_menu_callback = fn;
		blurAPI->hooks.fn_menu_trampoline = t;
		hooked = true;
	}
	return hooked;
}


//https://www.agner.org/optimize/calling_conventions.pdf
//its a __thiscall, pointer to __THIS @ ECX register
void __declspec(naked) hook_menu_leave() {
	/* no direct innits in __declspec(naked) funcs */
	void* f;
	f = blurAPI->hooks.fn_menu_trampoline;
	__asm PUSHAD;
	__asm PUSHFD;
	__asm nop;
	__asm nop;
	(blurAPI->hooks.fn_menu_callback)();
	__asm nop;
	__asm nop;
	__asm POPFD;
	__asm POPAD;
	__asm jmp [f];
}


void fn_hello_world() {
	blurAPI->console.print("Hello world -- fn_hello_world()!");
	//aux_print_registers();
}


bool install_username_hook() {
	return set_call_func((void*)(blurAPI->moduleBase + HOOK_NAME_FUNC_ADDY), (fn_ptr_t) hook_GetUserNameA);
}



bool __stdcall hook_GetUserNameA(char* buff, unsigned long * len) {
	//bool r = GetUserNameA(buff, len); //original func
	bool r = true;
	std::string name = blurAPI->config.user_name;
	int n = name.length();
	for (int i=0; i<n; i++) buff[i] = name[i];
	buff[n] = NULL;
	*len = n;
	blurAPI->console.print("Name set to: " + name);
	return r;
}



//TODO: debug stuff
//https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture
void aux_print_registers() {
	uint32_t reg_acumulator = 0;
	__asm {mov [reg_acumulator], eax};
	std::printf("%#010x  [reg_acumulator], eax\n", reg_acumulator);
	uint32_t reg_counter = 0;
	__asm {mov [reg_counter], ecx};
	std::printf("%#010x  [reg_counter], ecx\n", reg_counter);
	uint32_t reg_data = 0;
	__asm {mov [reg_data], ecx};
	std::printf("%#010x  [reg_data], ecx\n", reg_data);
	uint32_t reg_base = 0;
	__asm {mov [reg_base], ebx};
	std::printf("%#010x  [reg_base], ebx\n", reg_base);
	uint32_t reg_stackptr = 0;
	__asm {mov [reg_stackptr], esp};
	std::printf("%#010x  [reg_stackptr], esp\n", reg_stackptr);
	uint32_t reg_stackbaseptr = 0;
	__asm {mov [reg_stackbaseptr], ebp};
	std::printf("%#010x  [reg_stackbaseptr], ebp\n", reg_stackbaseptr);
	uint32_t reg_src = 0;
	__asm {mov [reg_src], esi};
	std::printf("%#010x  [reg_src], esi\n", reg_src);
	uint32_t reg_dst = 0;
	__asm {mov [reg_dst], edi};
	std::printf("%#010x  [reg_dst], edi\n", reg_dst);
}

