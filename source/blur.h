#pragma once
#include <string>

#include "blur_hooks.h"
#include "mem.h"


#define ADDY_LAN_MOD_YELLOW 0xE12F84
#define ADDY_LAN_MOD_ORANGE 0xE12F88
#define ADDY_LAN_MOD_GREENY 0xE12F8C

#define ADDY_SP_MOD 0xE14240

#define ADDY_LAN_NAME 0xCE5898
#define LEN_LAN_NAME 16



struct gameAPI {
	uintptr_t moduleBase {};
	gameHooks hooks {};
	std::string user_name;
	gameAPI() {};
	gameAPI(uintptr_t p) {
		moduleBase = p;
	};
};



bool set_LAN_name(std::string szName);

extern struct gameAPI blurAPI;
