#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "InputManager.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL

	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 500, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Player object
	Player player;

	// Input manager object
	InputManager inputManager;
	inputManager.loadKeyMapping();

	// Game loop flag
	bool running = true;
	SDL_Event event;

	bool remapMode = false;
	SDL_Keycode keyToRemap = 0;

	// Main Game loop
	while (running) {
		while (SDL_PollEvent(&event)) {
			// Exit loop if window closed
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode key = event.key.keysym.sym;

				// Remap mode
				if (remapMode) {
					if (keyToRemap == 0) {
						// Key to remap (W, A, S, D)
						keyToRemap = key;
						std::cout << "Key to remap: " << SDL_GetKeyName(keyToRemap) << std::endl;
						std::cout << "Select new movement key." << std::endl;
					}
					else {
						// Select new key
						inputManager.remapKey(keyToRemap, key);
						std::cout << "New key: " << SDL_GetKeyName(key) << std::endl;
						remapMode = false;
						keyToRemap = 0;
					}
				}
				else if (key == SDLK_p) {
					remapMode = true;
					std::cout << "Enter remap." << std::endl;
				}
				else if (key == SDLK_r) {
					inputManager.loadKeyMappingFromFile("keymapping.txt");
					std::cout << "Key Mapping reloaded." << std::endl;
				}
				else {
					// Handle regular input (non-remapping)
					if (inputManager.handleInput(key, player)) {
						std::cout << "Player action: " << SDL_GetKeyName(key) << std::endl;
					}
					else {
						std::cout << "Invalid key: " << SDL_GetKeyName(key) << std::endl;
					}
				}
			}
		}

		// Clear and present the renderer (no actual rendering in this example)
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup SDL resources before exiting
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}