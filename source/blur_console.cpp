#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <conio.h>


#include "blur_console.h"
#include "blur.h"


//TODO: buttons, better screen,
DWORD WINAPI input_thread(void* arg) {
	std::cout << "HELLO WORLD :: Console has been created!" << std::endl;
    std::string* input = (std::string*) arg;
	std::string cmd;
	std::vector<std::string> cmd_args;
	input->clear();
	char c = NULL;
	char prompt = '+';
	while (true) {
		std::cout << "\r" << prompt << " " << *input;
		c = _getch();
		if ((c == EOF) || (c == '\n') || (c == '\r')) { //parse the stuff
			std::cout << std::endl;
			cmd = *input;
			input->clear();
			blurAPI->console.cmd_handler(cmd);
			prompt = '=';
			cmd.clear();
		} else if (c == '\b') {
			if (!input->empty()) {
				prompt = '-';
				input->pop_back();
				std::cout << "\b ";
			} else {
				prompt = '>';
			}
		} else {
			input->push_back(c);
			prompt = '+';
		}
	}
	return 0;
}


gameConsole::gameConsole() {
	(void)_setmode(_fileno(stdout), _O_U16TEXT); //let me use unicode some day
	// enabling VT100 style in current console
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD l_mode;
	GetConsoleMode(hStdout, &l_mode);
	SetConsoleMode(hStdout, l_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
	freopen_s(&f, "CONIN$", "r", stdin);
	SetConsoleTitle("BLUR CONSOLE");
	input = new std::string; //not like this...
}


void gameConsole::start() {
	std::cout << "Loading console..." << std::endl;
	std::ios_base::sync_with_stdio(false);
	HANDLE input_thread_handle = CreateThread(NULL, 0, input_thread, input, 0, NULL);
}

void gameConsole::close() {
	print("Closing console..."); // might not get printed
	FreeConsole();
	fclose(f);
	delete input;
}


//TODO: mutex with input thread, custom prompt status, colours, allow open/close
void gameConsole::print(std::string text) {
	std::cout << "\r] " << text << std::endl;
	if (input->empty()) {
		std::cout << "\r> ";
	} else {
		std::cout << "\n\r: " << *input;
	}
}


bool gameConsole::cmd_handler(std::string cmd) {
	bool isCmd = false;
	std::vector<std::string> cmd_args = split(cmd, " ");
	if (!cmd_args.empty()) {
		if (cmd_args[0] == "hey") {
			print("blurAPI->console.print(HELLO!)");
			isCmd = true;
		} else if (cmd_args[0] == "name") {
			if (cmd_args.size() > 1) {
				if ((cmd_args[1].front() == '"') && (cmd_args.back().back() == '"')) {
					std::vector<std::string> tmp = split(cmd, "\"");
					if (tmp.size() == 2) {
						if (blurAPI->set_name_LAN(tmp[1])) {
							print("Name changed to \""+tmp[1]+"\", exit multiplayer menu to use it.");
							blurAPI->config.user_name = tmp[1];
						} else {
							print("Unable to change name to \""+tmp[1]+"\"");
						}
					} else {
						print("*Error* USAGE:  name \"your_username\"");
					}
				} else {
					print("*Error*(Try with quotes?) USAGE:  name \"your_username\"");
				}
			} else {
				print("Current name is \"" + blurAPI->config.user_name + "\"");
			} 
			isCmd = true;
		} else if (cmd_args[0] == "fps") {
			print("  " + std::to_string((float) blurAPI->config.fps));
			isCmd = true;
		} else if (cmd_args[0] == "tg") {
			blurAPI->toggle_drifter_mod_SP();
			isCmd = true;
		} else if (cmd_args[0] == "info") { //get lobby info
			print("LOBBY PLAYERS INFO: ");
			uintptr_t p = blurAPI->lobby_entlist_get_first_player();
			while (p != NULL) {
				//TODO format & colours
				print("\tNAME: \"" + blurAPI->lobby_get_player_name(p) + "\"");
				print("\t MODS:");
				print("\t\t\t" + blurAPI->lobby_get_player_yellow_mod_as_string(p));
				print("\t\t\t" + blurAPI->lobby_get_player_orange_mod_as_string(p));
				print("\t\t\t" + blurAPI->lobby_get_player_green_mod_as_string(p));
				p = blurAPI->get_next_player(p);
			}
			isCmd = true;
		} else if (cmd_args[0] == "laps") {
			int argsc = cmd_args.size();
			//FIXME there HAS to be a more elegant way to do this, maybe by hooking the verify function...
			if (argsc == 1) {
				print("LAPS: OFF" );
				restore_lobby_laps_func();
				print("\tEnter and exit the lobby settings menu to apply.");
				//let the player reset them from the game settings
			} else if (argsc == 2) {
				int laps = atoi(cmd_args[1].c_str());
				if ((9<laps) && (laps<256)) {
					//TODO patch verify func
					patch_lobby_laps_func();
					//set lobby laps to laps
					blurAPI->lobby_set_laps((uint8_t)laps);
					print("LAPS: " + std::to_string(laps));
					//tell them to open and close the menu
					print("\tEnter and exit the lobby settings menu to apply this change to other players.");
				} else {
					print("\t*Error*(We want more laps!) USAGE: laps <10..255>)");
				}
			} else {
				print("\t*Error*(Too many args! (" + std::to_string(argsc) + ")) USAGE: laps <10..255>)");
			}
		}
	}
	return isCmd;
}

//util func to split strings
std::vector<std::string> split(std::string str, std::string delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
