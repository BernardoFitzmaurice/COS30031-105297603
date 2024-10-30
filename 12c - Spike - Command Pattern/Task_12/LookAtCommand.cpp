#include "LookAtCommand.h"
#include <iostream>

void LookAtCommand::execute(const std::string& input, Player& player,
	std::map<std::string, Location>& gameWorld,
	std::map<std::string, std::vector<Entity>>& locationEntities,
	Inventory& inventory) {

	std::string entityName = input.substr(7);
	const auto& locEntities = locationEntities[player.currentLocation];
	bool found = false;

	for (const auto& entity : locEntities) {
		if (entity.getName() == entityName) {
			std::cout << entity.getDescription() << std::endl;
			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "No entity found." << std::endl;
	}
}