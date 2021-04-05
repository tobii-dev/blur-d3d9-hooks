#pragma once
#include "mem.h"

//TODO: clean menu hook
#define HOOK_MENU_FUNC_ADDY 0x34B8A7
#define HOOK_MENU_FUNC_INS_LEN 6

//winapi32 call to GetUserNameA() hook here
#define HOOK_NAME_FUNC_ADDY 0x95E0EA 
#define HOOK_NAME_FUNC_INS_LEN 6


// mov [edi], al   //gets EDI ptr register from some odd func earlier (im too dumb to dive into it)
#define FUNC_SET_LOBBY_LAPS_ADDY 0x6F41B2
#define FUNC_SET_LOBBY_LAPS_INS_LEN 0x2
#define FUNC_SET_LOBBY_LAPS_INS_BYTE0 0x88
#define FUNC_SET_LOBBY_LAPS_INS_BYTE1 0x07

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

bool patch_lobby_laps_func();
bool restore_lobby_laps_func();

//void aux_print_registers();
