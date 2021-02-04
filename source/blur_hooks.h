#pragma once
#include "mem.h"

//TODO: clean menu hook
#define HOOK_MENU_FUNC_ADDY 0x34B8A7
#define HOOK_MENU_FUNC_INS_LEN 6

//winapi32 call to GetUserNameA() hook here
#define HOOK_NAME_FUNC_ADDY 0x95CD2A
#define HOOK_NAME_FUNC_INS_LEN 6

struct gameHooks {
	fn_ptr_t fn_menu_trampoline = nullptr;
	fn_ptr_t fn_menu_callback = nullptr;
};


bool install_menu_hook();
bool install_menu_hook(fn_ptr_t fn);
void hook_menu_leave(); //its a __thiscall in Blur.exe?

void fn_hello_world();


bool install_username_hook();
bool __stdcall hook_GetUserNameA(char* buff, unsigned long *len);


//void aux_print_registers();
