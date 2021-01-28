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
#define LEN_LAN_NAME 16


struct gameConfig {
	std::string user_name;
	float fps;
	bool bFPSLimit;
	gameConfig(char cfg_name[]);
};


struct gameAPI {
	uintptr_t moduleBase;
	gameHooks hooks;
	gameConfig config;
	gameConsole console;
	gameAPI(uintptr_t p);
	void load();
	void unload();

	bool toggle_SP_drifter();
	bool set_LAN_name(std::string szName);
};



extern gameAPI* blurAPI;
