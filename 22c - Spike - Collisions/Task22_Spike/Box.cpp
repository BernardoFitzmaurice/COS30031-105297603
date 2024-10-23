#include "Box.h"

// Constructor
Box::Box(int x, int y, int w, int h, SDL_Color col) {
	rect = { x, y, w, h };
	color = col;
}

// Draw the box
void Box::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

// Move the box by given delta
void Box::move(int dx, int dy) {
	rect.x += dx;
	rect.y += dy;
}