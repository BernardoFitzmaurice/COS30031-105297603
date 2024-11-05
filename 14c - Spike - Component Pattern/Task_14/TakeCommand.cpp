#include "TakeCommand.h"
#include <iostream>
#include <sstream>

void TakeCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    std::istringstream iss(input);
    std::string command, entityName, word, containerName;
    iss >> command >> entityName >> word >> containerName;

    auto& entities = locationEntities[player.currentLocation];
    Entity* container = nullptr;
    Entity* entity = nullptr;

    for (auto& e : entities) {
        if (e.getName() == containerName && e.canContainEntities()) {
            container = &e;
        }
    }

    if (!container) {
        std::cout << "No container named " << containerName << " found here.\n";
        return;
    }

    entity = container->removeNestedEntity(entityName) ? new Entity(entityName, "") : nullptr;
    if (entity) {
        std::cout << "Took " << entityName << " from " << containerName << ".\n";
        entities.push_back(*entity); // Place the entity back in the location
    }
    else {
        std::cout << entityName << " not found in " << containerName << ".\n";
    }
}