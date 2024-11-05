#include "PutInCommand.h"
#include <iostream>
#include <sstream>

void PutInCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    std::istringstream iss(input);
    std::string command, entityName, preposition, containerName;
    iss >> command >> entityName >> preposition >> containerName;

    // Check for "put <entity> in <container>"
    if (command != "put" || preposition != "in") {
        std::cout << "Invalid format. Use: put <entity> in <container>\n";
        return;
    }

    // Locate entity and container in current location
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
        std::cout << "Entity '" << entityName << "' is not found here.\n";
        return;
    }

    if (!container) {
        std::cout << "Container '" << containerName << "' is not found here or is not a container.\n";
        return;
    }

    // Move entity into the container to avoid copying
    container->addNestedEntity(std::move(*entity));
    std::cout << "Placed " << entityName << " inside " << containerName << ".\n";
}
