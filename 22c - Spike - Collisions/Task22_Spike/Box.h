#pragma once
#include <SDL.h>

class Box {
public:
	SDL_Rect rect;
	SDL_Color color;

	Box(int x, int y, int w, int h, SDL_Color col);

	void draw(SDL_Renderer* renderer);

	void move(int dx, int dy);
};

