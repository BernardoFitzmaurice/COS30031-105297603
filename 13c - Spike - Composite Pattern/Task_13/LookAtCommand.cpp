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
			if (!entity.getEntities().empty()) {
				lookInsideEntity(entity);
			}
			found = true;
			break;
		}
	}

	if (!found) {
		std::cout << "No entity found." << std::endl;
	}
}

void LookAtCommand::lookInsideEntity(const Entity& entity) {
	if (entity.getEntities().empty()) {
		std::cout << "Nothing to see inside." << std::endl;
		return;
	}

	std::cout << "Inside " << entity.getName() << " you see: ";
	for (const auto& subEntity : entity.getEntities()) {
		std::cout << subEntity->getName() << " (" << subEntity->getDescription() << "), ";
	}
	std::cout << std::endl;
}