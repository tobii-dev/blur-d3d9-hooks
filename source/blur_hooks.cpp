#include <stdio.h>

#include "blur_hooks.h"
#include "blur.h"
#include "mem.h"


bool install_menu_hook() {
	return install_menu_hook(fn_hello_world);
}

bool install_menu_hook(fn_ptr_t fn) {
	bool hooked = false;
	uintptr_t src = blurAPI.moduleBase + HOOK_MENU_FUNC_ADDY;
	fn_ptr_t t = install_void_hook((void*) src, menu_hook_func, HOOK_MENU_FUNC_INS_LEN);
	if (t) {
		blurAPI.hooks.fn = fn;
		blurAPI.hooks.fn_trampoline = t;
		hooked = true;
	}
	return hooked;
}

void __declspec(naked) menu_hook_func() {
	__asm nop;
	__asm nop;
	__asm PUSHAD;
	__asm PUSHFD;
	(blurAPI.hooks.fn)();
	__asm nop;
	__asm nop;
	__asm POPFD;
	__asm POPAD;
	__asm jmp [blurAPI.hooks.fn_trampoline];
}


void fn_hello_world() {
	std::printf("HELLO CRUEL WORLD!");
	if (set_LAN_name(blurAPI.user_name)) {
		std::printf("SET NAME TO: <%s>", blurAPI.user_name.c_str());
	} else {
		std::printf("FAILED TO CHANGE NAME TO: <%s>", blurAPI.user_name.c_str());
	}
}
