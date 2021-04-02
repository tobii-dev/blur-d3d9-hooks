#pragma once
#include <Windows.h>
#include <string>

#include "blur_console.h"
#include "blur_hooks.h"
#include "mem.h"

enum BLUR_MOD_ID {
	//Y
	IRON_FIST = 0,
	JUMP_THE_GUN,
	FRONT_RUNNER,
	DRIFTER,
	TIATNIUM_ARMOR,
	SHOWY_FLOURISH,
	STABLE_FRAME,
	BATTERING_RAM,
	//O
	DECOY_DROP,
	MAGNETIC_FIELD,
	SCRAMBLER,
	SPLASH_DAMAGE,
	SHIELDING_EFFICIENCY,
	ADAPTIVE_SHIELDING,
	SAFETY_NET,
	SHIELDED_BAY,
	//G
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
/* // for "old" blur version"
#define ADDY_LAN_MOD_YELLOW 0xE12F84
#define ADDY_LAN_MOD_ORANGE 0xE12F88
#define ADDY_LAN_MOD_GREENY 0xE12F8C
#define ADDY_SP_MOD 0xE14240

#define ADDY_LAN_NAME 0xCE5898
#define LEN_LAN_NAME 32


#define ADDY_UNLOCK_INPUT 0xCC221C
#define OFFSETS_UNLOCK_INPUT {0x14, 0x35C, 0xC, 0x4B0}

*/

//for "new" (discord) blur version:
// "new" addy = "old" addy + 0x1358
#define ADDY_LAN_MOD_YELLOW 0xE142DC
#define ADDY_LAN_MOD_ORANGE 0xE142E0
#define ADDY_LAN_MOD_GREENY 0xE142E4
#define ADDY_SP_MOD 0xE14240 + 0x1358


// "new" = "old" + 0x1290
#define ADDY_LAN_NAME 0xCE6B28
#define LEN_LAN_NAME 32

//TODO
#define ADDY_UNLOCK_INPUT 0xCC221C

//hope?
#define OFFSETS_UNLOCK_INPUT {0x14, 0x35C, 0xC, 0x4B0}

//"old"entlist start
//0xDB31D8 @ {18}

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

	std::string lobby_get_player_name(uintptr_t p);
	std::string lobby_get_player_mods_as_string(uintptr_t p);
	std::string lobby_get_player_yellow_mod_as_string(uintptr_t p);
	std::string lobby_get_player_orange_mod_as_string(uintptr_t p);
	std::string lobby_get_player_green_mod_as_string(uintptr_t p);
	uintptr_t lobby_entlist_get_first_player();
	uintptr_t get_next_player(uintptr_t p);
};



extern gameAPI* blurAPI;
