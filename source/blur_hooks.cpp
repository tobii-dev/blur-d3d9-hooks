#include <stdio.h>

#include "blur_hooks.h"
#include "blur.h"
#include "mem.h"


bool install_menu_hook() {
	return install_menu_hook(fn_hello_world);
}


fn_ptr_t tmp_global_i_hate_this_variable = nullptr;
bool install_menu_hook(fn_ptr_t fn) {
	bool hooked = false;
	uintptr_t src = blurAPI->moduleBase + HOOK_MENU_FUNC_ADDY;
	fn_ptr_t t = install_void_hook((void*) src, menu_hook_func, HOOK_MENU_FUNC_INS_LEN);
	if (t) {
		blurAPI->hooks.fn = fn;
		blurAPI->hooks.fn_trampoline = t;
		tmp_global_i_hate_this_variable = t; //PLEASE I DONT LIKE YOU SO JUST WORK
		hooked = true;
	}
	return hooked;
}

void __declspec(naked) menu_hook_func() {
	__asm nop;
	__asm nop;
	__asm PUSHAD;
	__asm PUSHFD;
	(blurAPI->hooks.fn)();
	__asm nop;
	__asm nop;
	__asm POPFD;
	__asm POPAD;
	__asm jmp [tmp_global_i_hate_this_variable];
	//__asm jmp [blurAPI->hooks.fn_trampoline];
	//(blurAPI->hooks.fn_trampoline)();
}


void fn_hello_world() {
	if (blurAPI->set_LAN_name(blurAPI->config.user_name)) {
		blurAPI->console.print("SET NAME TO: [" + blurAPI->config.user_name + "]");
	} else {
		blurAPI->console.print("FAILED TO SET NAME TO: [" + blurAPI->config.user_name + "]");
	}
	//aux_print_registers();
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
