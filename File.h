#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <iostream>
#include <string>

class Directory {
public:
	Directory(const char* name) {
		Path = "assets/Sprite/";
		Name = name;
	}
	Directory(const char* name, std::string path) {
		Path = path;
		Name = name;
	}

	std::string getFile(std::string File) {
		std::string var = Path + Name + "/" + File;
		std::cout << var << std::endl;
		return var;
	}
	std::string getFrame(std::string File, int frame) {
		std::string var = File + "/";
		if (frame < 1000) var.append("0");
		if (frame < 100) var.append("0");
		if (frame < 10) var.append("0");
		std::cout << var + std::to_string(frame) + ".png" << std::endl;
		return var + std::to_string(frame) + ".png";
	}

	friend std::string operator / (Directory dir, std::string file) {
		return dir.getFile(file);
	}
private:
	std::string Path = "assets/Sprite/";
	const char* Name;
};