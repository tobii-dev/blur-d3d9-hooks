#include <Windows.h>
#include <iostream>

#include "blur.h"


gameConfig::gameConfig(char cfg_name[]) {
	char cfg[MAX_PATH];
	GetModuleFileNameA(NULL, cfg, MAX_PATH);
	*strrchr(cfg, '\\') = '\0';
	strcat_s(cfg, "\\");
	strcat_s(cfg, cfg_name);
	fps = static_cast<float>(GetPrivateProfileInt("FPS", "intFPSLimit", 0, cfg));
	bFPSLimit = fps > 0.0;
	//TODO: actual name
	TCHAR name[LEN_LAN_NAME];
	if (GetPrivateProfileString("NAME", "Name", NULL, name, LEN_LAN_NAME, cfg)) {
		user_name = name;
	}
}


gameAPI::gameAPI(uintptr_t p) : config("cfg.ini") {
	moduleBase = p;
}

uintptr_t gameAPI::lobby_entlist_get_first_player() {
	uintptr_t addr = moduleBase + ADDY_LAN_PLAYERS_LL_PTR;

	addr = *(uintptr_t*) addr;
	if (addr != NULL) {
		addr += OFFSET_LL_FIRST;
		addr = *(uintptr_t*) addr;
	}
	return addr;
}


uintptr_t gameAPI::get_next_player(uintptr_t p) {
	uintptr_t addr = *(uintptr_t*) (p+OFFSET_PLAYER_NEXT);
	return addr;
}


std::string gameAPI::lobby_get_player_name(uintptr_t p) {
	std::string name = "";
	short* ptr = ((short*)(p + OFFSET_PLAYER_NAME));
	char c = NULL;
	do {
		c = (char) *ptr;
		ptr++;
		name += c;

	} while (c != NULL);
	return name;
}

std::string gameAPI::lobby_get_player_mods_as_string(uintptr_t p) {
	std::string str = "";
	int y = * ((int*) (p + OFFSET_PLAYER_MOD_Y));
	int o = * ((int*) (p + OFFSET_PLAYER_MOD_O));
	int g = * ((int*) (p + OFFSET_PLAYER_MOD_G));
	str += "[ YELLOW = " + (((y >= 0) && (y < MOD_ID_MAX)) ? std::string(BLUR_MOD_NAMES[y]) : std::to_string(y)) + " ] ";
	str += "[ ORANGE = " + (((o >= 0) && (o < MOD_ID_MAX)) ? std::string(BLUR_MOD_NAMES[o]) : std::to_string(o)) + " ] ";
	str += "[ GREEN  = " + (((g >= 0) && (g < MOD_ID_MAX)) ? std::string(BLUR_MOD_NAMES[g]) : std::to_string(g)) + " ]";
	return str;
}

std::string gameAPI::lobby_get_player_yellow_mod_as_string(uintptr_t p) {
	std::string str = "YELLOW MOD\t:= ";
	int y = * ((int*) (p + OFFSET_PLAYER_MOD_Y));
	if (y >= 0) {
		if (y <= BATTERING_RAM) {
			str += std::string(BLUR_MOD_NAMES[y]); //normal
		} else if (y < MOD_ID_MAX){
			str += std::string(BLUR_MOD_NAMES[y]) + "!!"; //using green or orange mods in yellow slot?
		} else {
			str += std::to_string(y) + "??"; // something is off
		}
	} else {
		str += std::to_string(y) + "??!!"; // negative mods?
	}
	return str;
}

std::string gameAPI::lobby_get_player_orange_mod_as_string(uintptr_t p) {
	std::string str = "ORANGE MOD\t:= ";
	int o = * ((int*) (p + OFFSET_PLAYER_MOD_O));
	if (o >= 0) {
		if (o <= BATTERING_RAM) {
			str += std::string(BLUR_MOD_NAMES[o]) + "!!"; //using yellow mods in orange slot?
		} else if (o <= SHIELDED_BAY){
			str += std::string(BLUR_MOD_NAMES[o]); // ok
		} else if (o < MOD_ID_MAX){
			str += std::string(BLUR_MOD_NAMES[o]) + "!!"; //using green slots in orange slot?
		} else {
			str += std::to_string(o) + "??"; //something is off
		}
	} else {
		str += std::to_string(o) + "??!!"; // negative mods
	}
	return str;
}

std::string gameAPI::lobby_get_player_green_mod_as_string(uintptr_t p) {
	std::string str = "GREEN MOD\t:= ";
	int g = * ((int*) (p + OFFSET_PLAYER_MOD_G));
	if (g >= 0) {
		if (g <= SHIELDED_BAY){
			str += std::string(BLUR_MOD_NAMES[g]) + "!!"; //  using yellow or orange mods in green slot?
		} else if (g < MOD_ID_MAX){
			str += std::string(BLUR_MOD_NAMES[g]); //ok
		} else {
			str += std::to_string(g) + "??"; //something is off
		}
	} else {
		str += std::to_string(g) + "??!!"; // negative mods ?
	}
	return str;
}

//TODO: lets have all the init code here
void gameAPI::load() {
	console.start();
	if (install_username_hook()) blurAPI->console.print("set_usr_hook() -> true");
	//if (!install_menu_hook()) blurAPI->console.print("ERROR in gameAPI::load() [install_menu_hook() returned false]");
}


void gameAPI::unload() {
	//TODO: unhooks
	console.close();
}


//TODO: move this somewhere sane
bool gameAPI::toggle_drifter_mod_SP() {
	uintptr_t modAdr = moduleBase + ADDY_SP_MOD;
	int* modPtr = (int*) modAdr;
	int curMod = *modPtr;
	bool drifter = false;
	if ((QUADSHOCK <= curMod) && (curMod <= SUPER_SHUNT)) { //if its SP mod
		*modPtr = DRIFTER; //set it to drift mod
		console.print(" -- Set SP mod to DRIFTER.");
		drifter = true;
	} else {
		*modPtr = QUADSHOCK; //set it to a SP mod
		console.print(" -- Set SP mod to QUADSHOCK.");
	}
	return drifter;
}


bool gameAPI::set_name_LAN(std::string szName) {
	bool set = false;
	int len = szName.length();
	if (len && (len <= LEN_LAN_NAME)) {
		uintptr_t nameAdr = moduleBase + ADDY_LAN_NAME;
		short* ptr = (short*) nameAdr;
		for (int i=0; i<len; i++) ptr[i] = szName[i];
		ptr[len] = NULL;
		set = true;
	}
	return set;
}


gameAPI* blurAPI = nullptr;
