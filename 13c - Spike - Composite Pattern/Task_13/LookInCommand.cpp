#include "LookInCommand.h"
#include <iostream>

void LookInCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {
    std::string entityName = input.substr(8);

    auto& entities = locationEntities[player.currentLocation];
    for (const auto& entity : entities) {
        if (entity.getName() == entityName && entity.canContainEntities()) {
            entity.displayContents();
            return;
        }
    }
    std::cout << entityName << " cannot contain other items or was not found.\n";
}