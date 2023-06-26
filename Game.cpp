#include "Game.h"
SDL_Event Game::event;


Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	Width = width/4;
	Height = height/4;
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("Rendering to a texture!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
		SDL_RenderSetScale(renderer, 4, 4);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 16, 16, 16, 255);
			SDL_SetRenderDrawBlendMode(renderer,
				SDL_BLENDMODE_BLEND);
		}

		isRunning = true;
	}
	IMG_Init(IMG_INIT_PNG);
}





//Testing
class Gass : public Effect {
private:
	float gravity;
	int Xspread;
	int Yspread;
public:
	Gass(int i_max, float i_gravity, int i_Xspread, int i_Yspread) {
		max = i_max;
		gravity = i_gravity;
		Xspread = i_Xspread;
		Yspread = i_Yspread;
	}
	void update() override {
		for (auto& particle : particles) {
			particle.y -= gravity;
		}
		int sx;
		int sy;
		int tx;
		int ty;
		for (auto& Sparticle : particles) {

			for (auto& Tparticle : particles) {
				sx = floor(Sparticle.x + 0.5f);
				sy = floor(Sparticle.y + 0.5f);
				tx = floor(Tparticle.x + 0.5f);
				ty = floor(Tparticle.y + 0.5f);

				if (sx == tx) {
					if (sy == ty) {
						if (Xspread > 0) {
							Sparticle.x += (rand() % Xspread);
							Tparticle.x -= (rand() % Xspread);
						}
						if (Yspread > 0) {
							Sparticle.y += (rand() % Yspread);
							Tparticle.y -= (rand() % Yspread);
						}

					}
				}
			}
		}
	}
};



struct R_Body {
	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float width;
	float height;
	float bounce;
	float gravity;

	R_Body(float i_xpos, float i_ypos, float i_xvel, float i_yvel, float i_width, float i_height, float i_bounce, float i_gravity) {
		xpos = i_xpos;
		ypos = i_ypos;
		xvel = i_xvel;
		yvel = i_yvel;
		width = i_width;
		height = i_height;
		bounce = i_bounce;
		gravity = i_gravity;
	}

	void update() {
		if (ypos + height > 143) {
			ypos = 143;
			yvel *= -bounce;
			xvel *= bounce;
		}
		else {
			yvel += gravity;
		}

		xpos += xvel;
		ypos += yvel;
		ypos += 0.5f;
		floor(ypos);
	}
};


struct Mouse {
	bool P;
	int x;
	int y;
	void update() {
		SDL_GetMouseState(&x, &y);
		x /= 4;
		y /= 4;
	}
};
Mouse mouse;





class Fire {
private:
	float x;
	float y;
	Gass cloud;
	Gass flame;
	Gass blue;
	R_Body rbod;
public:
	Fire()
		: cloud(128, 0.3f, 2, 0), flame(64, 0.3f, 2, 0), blue(16, 0.3f, 2, 0), rbod(64, 64, 2, 0, 0, 0, 0.6f, 0.16f)
	{}
	void pos(float i_x, float i_y) {
		x = i_x;
		y = i_y;
	}
	void update() {
		if (mouse.P) {
			rbod.xvel = (mouse.x - rbod.xpos) / 8;
			rbod.yvel = (mouse.y - rbod.ypos) / 8;
			if (rbod.xvel > 8) rbod.xvel = 8;
			if (rbod.xvel < -8) rbod.xvel = -8;
			if (rbod.yvel < -8) rbod.yvel = -8;
		}
		rbod.update();
		pos(rbod.xpos, rbod.ypos);
		cloud.emit(x, y);
		flame.emit(x, y);
		blue.emit(x, y);

		cloud.update();
		flame.update();
		blue.update();
	}
	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 20);
		cloud.draw(renderer, 1);
		SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
		flame.draw(renderer, 0);
		SDL_SetRenderDrawColor(renderer, 255, 40, 40, 255);
		blue.draw(renderer, 0);
	}
};
Fire spell;

class Lightning {
private:
	float x;
	float y;
	Gass arc1;
	Gass arc2;
	R_Body rbod;
public:
	Lightning()
		: arc1(64, 1.0f, 2, 4), arc2(64, 1.0f, 2, 2), rbod(64, 64, 2, 0, 0, 0, 0.6f, 0.0f)
	{}
	void pos(float i_x, float i_y) {
		x = i_x;
		y = i_y;
	}
	void update() {
		if (mouse.P) {
			rbod.xvel = (mouse.x - rbod.xpos) / 4;
			rbod.yvel = (mouse.y - rbod.ypos) / 4;
			if (rbod.xvel > 16) rbod.xvel = 16;
			if (rbod.xvel < -16) rbod.xvel = -16;
			if (rbod.yvel < -16) rbod.yvel = -16;
		}
		rbod.update();
		pos(rbod.xpos, rbod.ypos);
		arc1.emit(x, y);
		arc2.emit(x, y);

		arc1.update();
		arc2.update();
	}
	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
		arc1.draw(renderer, 1);
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 128);
		arc2.draw(renderer, 0);
	}

};
Lightning lightning;



void Game::handleEvents()
{
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		mouse.P = true;
		break;
	case SDL_MOUSEBUTTONUP:
		mouse.P = false;
		break;
	default:
		break;
	}
}




void Game::update()
{
	std::cout << mouse.P;

	spell.update();
	mouse.update();

	cnt++;
}

void Game::render()
{


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	spell.draw(renderer);

	
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
