#pragma once
#include "StandardIncludes.h"




class Effect {
protected:

	std::vector<SDL_FPoint> particles;
	int max = 128;
public:
	~Effect() {
		particles.clear();
	}

	void emit(float x, float y)
	{

		if (particles.size() > max) {
			particles.resize(max);
		}

		SDL_FPoint tempPoint;
		tempPoint.x = x;
		tempPoint.y = y;
		particles.insert(particles.begin(), tempPoint);

	}

	void clear() {
		particles.clear();
	}

	void draw(SDL_Renderer* renderer, unsigned int DrawMode)
	{
		switch (DrawMode) {

		case 0:
			for (auto& particle : particles)
				SDL_RenderDrawPointF(renderer, particle.x, particle.y);
			break;


		case 1:
			for (int i = 1; i < particles.size(); i++)
				SDL_RenderDrawLineF(renderer, particles[i].x, particles[i].y, particles[i - 1].x, particles[i - 1].y);
			break;


		case 2:
			SDL_Rect rect;
			for (int i = 1; i < particles.size(); i++) {


				rect.x = particles[i].x;
				rect.y = particles[i].y;
				rect.w = particles[i - 1].x - rect.x;
				rect.h = particles[i - 1].y - rect.y;

				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
			}
			break;
		}

	}

	virtual void update() = 0;
};