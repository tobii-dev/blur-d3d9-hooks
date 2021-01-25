#include <Windows.h>
#include <iostream>

#include "blur.h"

gameAPI blurAPI;


bool set_LAN_name(std::string szName) {
	bool set = false;
	int len = szName.length();
	if (len && len <= LEN_LAN_NAME) {
		uintptr_t nameAdr = blurAPI.moduleBase + ADDY_LAN_NAME;
		short* ptr = (short*) nameAdr;
		for (int i = 0; i < len; i++) ptr[i] = szName[i];
		ptr[len] = NULL;
		set = true;
	}
	return set;
}
