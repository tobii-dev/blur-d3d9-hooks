#pragma once
#include <Windows.h>
#include <string>

#include "blur_console.h"
#include "blur_hooks.h"
#include "mem.h"


enum BLUR_MOD_ID {
	//Yellow
	IRON_FIST = 0,
	JUMP_THE_GUN,
	FRONT_RUNNER,
	DRIFTER,
	TIATNIUM_ARMOR,
	SHOWY_FLOURISH,
	STABLE_FRAME,
	BATTERING_RAM,
	//Orange
	DECOY_DROP,
	MAGNETIC_FIELD,
	SCRAMBLER,
	SPLASH_DAMAGE,
	SHIELDING_EFFICIENCY,
	ADAPTIVE_SHIELDING,
	SAFETY_NET,
	SHIELDED_BAY,
	//Green
	ECM,
	VAMPIRIC_WRECK,
	BRIBE,
	FAN_FAVOURITE,
	LASER_SIGHT,
	SILENT_RUNNING,
	LAST_GASP,
	MASTERMINE,
	//SP
	QUADSHOCK,
	OVERBOLT,
	TITANIUM_SHIELD,
	FAN_NITRO,
	NITRO_RIFT,
	ARMOR_PLATING,
	SCATTER_SHOT,
	SUPER_SHUNT,
	//aux
	MOD_ID_MAX
};


const char * const BLUR_MOD_NAMES[] = {
	"(y) IRON FIST",
	"(y) JUMP THE GUN",
	"(y) FRONT RUNNER",
	"(y) DRIFTER",
	"(y) TIATNIUM ARMOR",
	"(y) SHOWY FLOURISH",
	"(y) STABLE FRAME",
	"(y) BATTERING RAM",
	"(o) DECOY DROP",
	"(o) MAGNETIC FIELD",
	"(o) SCRAMBLER",
	"(o) SPLASH DAMAGE",
	"(o) SHIELDING EFFICIENCY",
	"(o) ADAPTIVE SHIELDING",
	"(o) SAFETY NET",
	"(o) SHIELDED BAY",
	"(g) ECM",
	"(g) VAMPIRIC WRECK",
	"(g) BRIBE",
	"(g) FAN FAVOURITE",
	"(g) LASER SIGHT",
	"(g) SILENT RUNNING",
	"(g) LAST GASP",
	"(g) MASTERMINE",
	"(SP) QUADSHOCK",
	"(SP) OVERBOLT",
	"(SP) TITANIUM SHIELD",
	"(SP) FAN NITRO",
	"(SP) NITRO RIFT",
	"(SP) ARMOR PLATING",
	"(SP) SCATTER SHOT",
	"(SP) SUPER SHUNT"
};


#define ADDY_LAN_MOD_YELLOW 0xE142DC
#define ADDY_LAN_MOD_ORANGE 0xE142E0
#define ADDY_LAN_MOD_GREENY 0xE142E4
#define ADDY_SP_MOD 0xE15598


#define ADDY_LAN_NAME 0xCE6B28
#define ADDY_DISP_NAME 0xDA8878
#define LEN_LAN_NAME 32


// TODO elaborate info:
//addy of player_0 = value of whatever is @ [ [@base]+0x18 ]
//addy string name of player_0 = whatever is @ [ player]+0x58 ]
//addy of player_(n+1) = whaterver is @ [player_n + 4 ]
//addy of player_(n+1) = whaterver is @ [player_n + 4 ]
#define ADDY_LAN_PLAYERS_LL_PTR 0xDB4530
#define OFFSET_LL_FIRST 0x18

#define OFFSET_PLAYER_NEXT 0x4
#define OFFSET_PLAYER_NAME 0x58
#define OFFSET_PLAYER_MOD_Y 0x150
#define OFFSET_PLAYER_MOD_O 0x154
#define OFFSET_PLAYER_MOD_G 0x158


// what the user sees as laps
#define ADDY_LAN_LAPS_READ 0xE3E8F9
//what the rest of the lobby sees
#define ADDY_LAN_LAPS_LOBBY 0xE3923B


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

	uint8_t lobby_get_laps();
	bool lobby_set_laps(uint8_t laps);
	std::string lobby_get_player_name(uintptr_t p);
	std::string lobby_get_player_mods_as_string(uintptr_t p);
	std::string lobby_get_player_yellow_mod_as_string(uintptr_t p);
	std::string lobby_get_player_orange_mod_as_string(uintptr_t p);
	std::string lobby_get_player_green_mod_as_string(uintptr_t p);
	uintptr_t lobby_entlist_get_first_player();
	uintptr_t get_next_player(uintptr_t p);
};



extern gameAPI* blurAPI;
