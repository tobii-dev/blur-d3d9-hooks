#include "blur_console.h"
#include "blur.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <conio.h>



//TODO: command handler, close button, tab complete, colours, game input
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
			cmd_args = split(*input, " ");
			input->clear();
			if (!cmd_args.empty()) {
				cmd = cmd_args[0];
				if (cmd == "hey") {
					blurAPI->console.print("blurAPI->console.print() from console thread");
				} else if (cmd == "name") {
					if (cmd_args.size() == 2) {
						if (blurAPI->set_LAN_name(cmd_args[1])) {
							blurAPI->console.print("Name changed to ["+cmd_args[1]+"], exit multiplayer menu to use it.");
							blurAPI->config.user_name = cmd_args[1];
						} else {
							blurAPI->console.print("Could not change name to ["+cmd_args[1]+"]");
						}
					} else if (cmd_args.size() == 1) {
						blurAPI->console.print("Current name is [" + blurAPI->config.user_name + "]");
					} else {
						blurAPI->console.print("USAGE:  name <your_username>");
					}
				} else if (cmd == "fps") {
					blurAPI->console.print("  " + std::to_string((float) blurAPI->config.fps));
				}
			}
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
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
	freopen_s(&f, "CONIN$", "r", stdin);
	SetConsoleTitle("BLUR CONSOLE");
	input = new std::string; //we should do this differently...
}


void gameConsole::start() {
	std::cout << "Loading console..." << std::endl;
	HANDLE input_thread_handle = CreateThread(NULL, 0, input_thread, input, 0, NULL);
}


void gameConsole::close() {
	print("Closing console..."); // might not get printed
	FreeConsole();
	fclose(f);
	delete input;
}


void gameConsole::print(std::string text) {
	//TODO: mutex with input thread, make nicer, make usable, etc...
	std::cout << "\r] " << text << std::endl;
	if (input->empty()) {
		std::cout << "\r> ";
	} else {
		std::cout << "\n\r: " << *input;
	}
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
