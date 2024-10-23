#include "Circle.h"

// Constructor
Circle::Circle(int x, int y, int w, int h, SDL_Color col, SDL_Renderer* renderer, const char* imagePath) {
	rect = { x, y, w, h };
	color = col;
	texture = nullptr;

	// Load image
	SDL_Surface* surface = IMG_Load(imagePath);
	if (!surface) {
		SDL_Log("Failed to load image: %s",imagePath, IMG_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
}

// Destructor to free the texture
Circle::~Circle() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

// Draw the circle
void Circle::draw(SDL_Renderer* renderer) {
	if (texture) {
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
	else {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &rect);
	}
}

// Move the box by given delta
void Circle::move(int dx, int dy) {
	rect.x += dx;
	rect.y += dy;
}

// New texture
void Circle::setTexture(SDL_Renderer* renderer, const char* imagePath) {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface = IMG_Load(imagePath);
	if (!surface) {
		SDL_Log("Failed to load image: %s", imagePath, IMG_GetError());
		texture = nullptr;
	}
	else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}
}