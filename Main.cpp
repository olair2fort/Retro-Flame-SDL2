#include <time.h>
#include <iostream>
#include "Game.h"

Game game;

int main(int argc, char* argv[]){


	const unsigned int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;


	int frameTime;

	game.init("Game", 256*4, 144*4, false);

	while (game.running()) {
		frameStart = SDL_GetTicks();
		game.handleEvents();
		game.update();
		game.render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game.clean();
	return 0;
}
