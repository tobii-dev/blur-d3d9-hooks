#pragma once
#include "mem.h"

#define HOOK_MENU_FUNC_ADDY 0x34B8A7
#define HOOK_MENU_FUNC_INS_LEN 6


struct gameHooks {
	fn_ptr_t fn_trampoline;
	fn_ptr_t fn;
};


bool install_menu_hook();
bool install_menu_hook(fn_ptr_t fn);


void menu_hook_func();


void fn_hello_world();
