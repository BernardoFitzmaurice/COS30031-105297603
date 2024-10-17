#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>

Mix_Music* bgm = NULL;

Mix_Chunk* echo = NULL;
Mix_Chunk* fire = NULL;
Mix_Chunk* gun = NULL;

void playMusic(Mix_Music* music) {
	// Stop the current song
	if (Mix_PlayingMusic() == 1) {
		Mix_HaltMusic();
	}
}

int main(int argc, char* argv[]) {
	//Initialize SDL & Create window
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 500, 0);
	if (window == nullptr) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;

		return 1;
	}

	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		SDL_DestroyWindow(window); // Clean up
		SDL_Quit();

		return 1;
	}

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	// Load image to surface
	SDL_Surface* image = IMG_Load("Charles.png");
	if (image == nullptr) {
		std::cerr << "Could not create surface: " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	// Create texture from surface
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	if (texture == nullptr) {
		std::cerr << "Could not create texture: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	// Load second image
	SDL_Surface* randomSheet = IMG_Load("Wooper.jpg");
	if (randomSheet == nullptr) {
		std::cerr << "Could not create surface: " << IMG_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}else {
		std::cout << "Image loaded successfully!" << std::endl; // Debug statement
	}

	// Create texture from surface (second image)
	SDL_Texture* randomTexture = SDL_CreateTextureFromSurface(renderer, randomSheet);
	SDL_FreeSurface(randomSheet);
	if (randomTexture == nullptr) {
		std::cerr << "Could not create texture: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}else {
		std::cout << "Texture created successfully!" << std::endl; // Debug statement
	}

	// Define sub-regions of the second image
	SDL_Rect reg1 = {0, 0, 64, 6};
	SDL_Rect reg2 = { 0, 6, 64, 6 };
	SDL_Rect reg3 = { 0, 12, 64, 6 };

	// Random region for second image
	srand(static_cast<unsigned>(time(0)));
	SDL_Rect reg1Dest = { rand() % 736, rand() % 436, 64, 64 };
	SDL_Rect reg2Dest = { rand() % 736, rand() % 436, 64, 64 };
	SDL_Rect reg3Dest = { rand() % 736, rand() % 436, 64, 64 };

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;

		return 1;
	}

	// Load music
	Mix_Music* bgm = Mix_LoadMUS("Charles(Cover) - Mano Aloe.mp3");
	if (bgm == nullptr) {
		std::cout << "Failed to load bgm! SDL_mixer Error: " << Mix_GetError() << std::endl;

		return 1;
	}

	// Load sound effects
	Mix_Chunk* echo = Mix_LoadWAV("cinematic-echo-noisy-bright-01.wav");
	if (echo == nullptr) {
		std::cout << "Failed to load echo! SDL_mixer Error: " << Mix_GetError() << std::endl;

		return 1;
	}

	Mix_Chunk* fire = Mix_LoadWAV("elements-fire-whoosh-01.wav");
	if (fire == nullptr) {
		std::cout << "Failed to load fire! SDL_mixer Error: " << Mix_GetError() << std::endl;

		return 1;
	}

	Mix_Chunk* gun = Mix_LoadWAV("game-fx-lasergun-01.wav");
	if (gun == nullptr) {
		std::cout << "Failed to load gun! SDL_mixer Error: " << Mix_GetError() << std::endl;

		return 1;
	}

	// Music in loop
	Mix_PlayMusic(bgm, -1);

	// Event handler
	SDL_Event SDLevent;

	bool quit = false;

	// Variable to control image showing
	bool showImage = true;

	bool showreg1 = false;
	bool showreg2 = false;
	bool showreg3 = false;

	// Maion loop
	while (!quit) {
		while (SDL_PollEvent(&SDLevent) != 0) {
			// Handle quit event
			if (SDLevent.type == SDL_QUIT) {
				quit = true;
			}

			// Key press event
			if (SDLevent.type == SDL_KEYDOWN) {
				if (SDLevent.key.keysym.sym == SDLK_0) {
					// Toggle music
					if (Mix_PausedMusic() == 1) {
						Mix_ResumeMusic(); // If pause then resume
					}
					else {
						Mix_PauseMusic(); // If playing then pause
					}
				}

				// Togglo sound effects
				if (SDLevent.key.keysym.sym == SDLK_1) {
					Mix_PlayChannel (-1, echo, 0);
				}

				if (SDLevent.key.keysym.sym == SDLK_2) {
					Mix_PlayChannel(-1, fire, 0);
				}

				if (SDLevent.key.keysym.sym == SDLK_3) {
					Mix_PlayChannel(-1, gun, 0);
				}

				// Toggle image
				if (SDLevent.key.keysym.sym == SDLK_o) {
					showImage = !showImage;
				}

				// Toggle regions
				if (SDLevent.key.keysym.sym == SDLK_4) {
					showreg1 = !showreg1;
				}

				// Toggle regions
				if (SDLevent.key.keysym.sym == SDLK_5) {
					showreg2 = !showreg2;
				}

				// Toggle regions
				if (SDLevent.key.keysym.sym == SDLK_6) {
					showreg3 = !showreg3;
				}
			}
		}

		// Creal Screen
		SDL_RenderClear(renderer);

		// Render image
		if (showImage) {
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		}

		if (showreg1) {
			SDL_RenderCopy(renderer, randomTexture, &reg1, &reg1Dest);
		}

		if (showreg2) {
			SDL_RenderCopy(renderer, randomTexture, &reg2, &reg2Dest);
		}

		if (showreg3) {
			SDL_RenderCopy(renderer, randomTexture, &reg3, &reg3Dest);
		}

		// Update screen
		SDL_RenderPresent(renderer);
	}

	// Clean up
	Mix_FreeMusic(bgm);
	Mix_CloseAudio();

	// Free resources and close SDL
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(randomTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}