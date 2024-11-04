#include "PutInCommand.h"
#include <iostream>
#include <sstream>

void PutInCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    std::istringstream iss(input);
    std::string command, entityName, containerName, word;
	iss >> command >> entityName >> word >> containerName;

	auto& entities = locationEntities[player.currentLocation];
    Entity* entity = nullptr;
	Entity* container = nullptr;

    for (auto& e : entities) {
        if (e.getName() == entityName) {
			entity = &e;
        }
        else if (e.getName() == containerName && e.canContainEntities()) {
			container = &e;
        }
    }
    if (!entity) {
        std::cout << entityName << " is not found here.\n";
        return;
    }

    if (!container) {
        std::cout << containerName << " is not a container or is not found here.\n";
        return;
    }

    container->addEntity(*entity);
    std::cout << "Placed " << entityName << " inside " << containerName << ".\n";
}