#include <SDL.h>
#include <SDL_image.h>
#include "Box.h"
#include "Collision.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
		return 1;
	}


	SDL_Window* window = SDL_CreateWindow("Collision", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };
	SDL_Color orange = { 255, 165, 0, 255 };
	SDL_Color purple = { 128, 0, 128, 255 };

	// Create boxes
	Box fixedBox(100, 100, 150, 150, blue);
	Box movingBox(50, 60, 100, 100, red);

	// Create Circles
	Circle fixedCircle(100, 100, 150, 150, purple, renderer, "Circle.png");
	Circle movingCircle(50, 60, 100, 100, orange, renderer, "Circle.png");

	// Figure's velocity
	int velX = 3, velY = 3;

	bool running = true;
	bool collided = false;
	bool drawBox = true; // Track if a box or a circle is drawn
	SDL_Event e;

	//Main loop
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_SPACE) {
					drawBox = !drawBox;
				}
			}
		}
		
		//Moving box
		if (drawBox) {
			movingBox.move(velX, velY);

			// Bounce off the walls
			if (movingBox.rect.x < 0 || movingBox.rect.x + movingBox.rect.w > 640) {
				velX = -velX;
			}
			else if (movingBox.rect.y <= 0 || movingBox.rect.y + movingBox.rect.h >= 480) {
				velY = -velY;
			}

			// Check collision
			collided = Collision::checkCollision(fixedBox, movingBox);
		}
		else {
			movingCircle.move(velX, velY);

			if (movingCircle.rect.x < 0 || movingCircle.rect.x + movingCircle.rect.w > 640) {
				velX = -velX;
			}
			else if (movingCircle.rect.y <= 0 || movingCircle.rect.y + movingCircle.rect.h >= 480) {
				velY = -velY;
			}

			// Check collision
			collided = Collision::checkCollision(fixedCircle, movingCircle);
		}

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw the boxes
		if (drawBox) {
			if (collided) {
				movingBox.color = { 255, 255, 0 ,255 }; // Yellow
			}
			else {
				movingBox.color = red;
			}
			fixedBox.draw(renderer);
			movingBox.draw(renderer);
		}
		else {
			// Draw the circles
			if (collided) {
				movingCircle.setTexture(renderer, "Face.png"); // Green
			}
			else {
				movingCircle.setTexture(renderer, "Circle.png");
			}
			fixedCircle.draw(renderer);
			movingCircle.draw(renderer);
		}

		// Show on screen
		SDL_RenderPresent(renderer);

		SDL_Delay(16);  // Delay to limit frame rate
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();

	return 0;
}