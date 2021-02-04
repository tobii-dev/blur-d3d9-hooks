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
	if ((24 <= curMod) && (curMod <= 31)) { //if its SP mod
		*modPtr = 3; //set it to drift mod
		console.print(" -- Set SP mod to DRIFTER.");
		drifter = true;
	} else {
		*modPtr = 24; //set it to a SP mod
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
