#include "blur_console.h"
#include "blur.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <vector>



//TODO: command handler, close button, tab complete, colours, game input
DWORD WINAPI input_thread(void* arg) {
	std::cout << "HELLO WORLD :: Console has been created!" << std::endl;
	std::string buff, cmd;
	std::vector<std::string> cmd_args;
	std::string tmp;
	char* c = NULL;
	while (true) {
		std::cout << "> "; 
		std::getline(std::cin, buff);
		cmd_args = split(buff, " ");
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
					blurAPI->console.print(" name: [" + blurAPI->config.user_name + "]");
				} else {
					blurAPI->console.print(" USAGE:  > name <your_username>");
				}
			} else if (cmd == "fps") {
				blurAPI->console.print("  " + std::to_string((float) blurAPI->config.fps));
			}
		}
	}
	return 0;
}

void handler_func() {
	std::cout << "hello from *handler_func()!" << std::endl;
}

gameConsole::gameConsole() {
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout.clear();
	std::cin.clear();
	freopen_s(&f, "CONIN$", "r", stdin);
	//_setmode(_fileno(stdout), _O_U16TEXT); //let me use unicode some day
	SetConsoleTitle("BLUR CONSOLE");
}


void gameConsole::start() {
	std::cout << "Starting console..." << std::endl;
	HANDLE input_thread_handle = CreateThread(NULL, 0, input_thread, nullptr, 0, NULL);
}


void gameConsole::close() {
	print("Closing console"); // might not get printed
	FreeConsole();
	fclose(f);
}


void gameConsole::print(std::string out) {
	//TODO: mutex with input thread, make nicer, make usable, etc...
	std::cout << "] " << out << std::endl;
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
