#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Circle {
public:
	SDL_Rect rect;
	SDL_Color color;
	SDL_Texture* texture;

	Circle(int x, int y, int w, int h, SDL_Color col, SDL_Renderer* renderer, const char* imagePath);
	~Circle();

	void draw(SDL_Renderer* renderer);

	void move(int dx, int dy);

	void setTexture(SDL_Renderer* renderer, const char* imagePath);
};