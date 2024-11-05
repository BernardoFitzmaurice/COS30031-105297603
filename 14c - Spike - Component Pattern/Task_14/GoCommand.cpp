#include "GoCommand.h"
#include <iostream>

void GoCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

	std::string direction = input.substr(3);
	player.move(direction, gameWorld);

}