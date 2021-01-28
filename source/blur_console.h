#pragma once
#include <Windows.h>
#include <vector>
#include <string>

std::vector<std::string> split(std::string str, std::string delim);



struct gameConsole {
	FILE* f;
	std::string* input;
	gameConsole();
	void start();
	void print(std::string t);
	void close();
	bool cmd_handler(std::string cmd);
};

