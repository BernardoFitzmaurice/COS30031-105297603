#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
	//Initialize SDL & Create window
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, 0);
	if (window == nullptr) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Get the window surface
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	//Set backgrond to green
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 255, 0)); //Green in RGB format
	
	//Update the window surface
	SDL_UpdateWindowSurface(window);

	//Loop to keep window open
	SDL_Event windowEvent;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) {
				running = false; //Exit the loop when the window is closed
			}
			else if (windowEvent.type == SDL_KEYDOWN) {
				if (windowEvent.key.keysym.sym == SDLK_r) {
					//Generate random color
					Uint8 r = std::rand() % 256;
					Uint8 g = std::rand() % 256;
					Uint8 b = std::rand() % 256;

					//Set background to random color
					SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
					SDL_UpdateWindowSurface(window);
				}
			}
		}
	}

	//Message when window is closed
	std::cout << "Byebye Pepe the Frog" << std::endl;

	//Clean up
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}