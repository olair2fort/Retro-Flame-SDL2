#pragma once
#include "Effect.h"

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	SDL_Renderer* getRenderer() { return renderer; };

	static SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
private:

	int Width;
	int Height;
	int cnt = 0;
	bool isRunning;
};