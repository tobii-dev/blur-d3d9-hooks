#pragma once
#include <Windows.h>
#include <string>

#include "blur_console.h"
#include "blur_hooks.h"
#include "mem.h"


#define ADDY_LAN_MOD_YELLOW 0xE12F84
#define ADDY_LAN_MOD_ORANGE 0xE12F88
#define ADDY_LAN_MOD_GREENY 0xE12F8C

#define ADDY_SP_MOD 0xE14240

#define ADDY_LAN_NAME 0xCE5898
#define LEN_LAN_NAME 32


#define ADDY_UNLOCK_INPUT 0xCC221C
#define OFFSETS_UNLOCK_INPUT {0x14, 0x35C, 0xC, 0x4B0}


struct gameConfig {
	std::string user_name;
	float fps;
	bool bFPSLimit;
	gameConfig(char ini[]);
};


struct gameAPI {
	uintptr_t moduleBase;
	gameHooks hooks;
	gameConfig config;
	gameConsole console;
	bool toggle_drifter_mod_SP();
	bool set_name_LAN(std::string szName);
	void load();
	void unload();
	gameAPI(uintptr_t p);
};



extern gameAPI* blurAPI;
