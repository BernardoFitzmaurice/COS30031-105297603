#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL.h>
#include <map>
#include <string>
#include "Player.h"

class InputManager {
private:
	std::map<SDL_Keycode, std::string> keyMapping; // Map to store actions
public:
	void loadKeyMapping(); // Load default mapping
	void saveKeyMapping(const std::string& filename); // Save key mapping to file
	void loadKeyMappingFromFile(const std::string& filename); // Load key mapping from file
	bool handleInput(SDL_Keycode key, Player& player); // Handle input to trigger player action

	void remapKey(SDL_Keycode oldkey, SDL_Keycode newkey); // Remap a key
};

#endif // INPUT_MANAGER_H
