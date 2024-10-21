#include "InputManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Load default key mapping (WASD)
void InputManager::loadKeyMapping() {
	keyMapping[SDLK_w] = "moveUp";
	keyMapping[SDLK_s] = "moveDown";
	keyMapping[SDLK_a] = "moveLeft";
	keyMapping[SDLK_d] = "moveRight";
}

// Save key mapping to file
void InputManager::saveKeyMapping(const std::string& filename) {
	std::ofstream outFile(filename); // Open file for writing
	for (const auto& pair : keyMapping) {
		outFile << pair.first << " " << pair.second << "\n"; // Write key and action to file
	}
	outFile.close();
}

// Load key mapping from file
void InputManager::loadKeyMappingFromFile(const std::string& filename) {
	std::ifstream inFile(filename); // Open file for reading
	SDL_Keycode key;
	std::string action;
	char str[50];
	keyMapping.clear(); // Clear existing key mapping
	while (inFile.getline(str, 9999, '\n')) {
		std::stringstream(str) >> key >> action;
		keyMapping[key] = action; // Read key and action from file
	}
	inFile.close();
}

// Handle input to trigger player action
bool InputManager::handleInput(SDL_Keycode key, Player& player) {
	// Find the action corresponding to the key
	if (keyMapping.find(key) != keyMapping.end()) {
		std::string action = keyMapping[key]; // Get action from key

		// Trigger corresponding action
		if (action == "MOVE_UP") {
			player.moveUp();
		}
		else if (action == "MOVE_DOWN")
		{
			player.moveDown();
		}
		else if (action == "MOVE_LEFT") {
			player.moveLeft();
		}
		else if (action == "MOVE_RIGHT") {
			player.moveRight();
		}
		return true;
	}
	return false; // Invalid key
}

void InputManager::remapKey(SDL_Keycode oldkey, SDL_Keycode newkey) {
	if (keyMapping.find(oldkey) != keyMapping.end()) {
		std::string action = keyMapping[oldkey]; // Get action from old key
		keyMapping.erase(oldkey); // Remove old key mapping
		keyMapping[newkey] = action; // Add new key mapping
		std::cout << "Key remapped: " << SDL_GetKeyName(oldkey) << " to " << SDL_GetKeyName(newkey) << std::endl;
	}
	else {
		std::cout << "Invalid key to remap: " << SDL_GetKeyName(oldkey) << std::endl;
	}
}