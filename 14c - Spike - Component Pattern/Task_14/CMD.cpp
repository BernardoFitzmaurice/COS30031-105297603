#include "CMD.h"
#include <iostream>

void CMD::executeCommand(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    aliasCommand.processAliasCommand(input);
    std::string resolvedInput = resolveAlias(input);

    // Custom handling for "pick up <entity>" command using components
    if (resolvedInput.find("pick up ") == 0) {
        std::string entityName = resolvedInput.substr(8);
        auto& locEntities = locationEntities[player.currentLocation];
        for (auto& entity : locEntities) {
            if (entity.getName() == entityName) {
                if (auto* pickable = entity.getActionComponent("Pickable")) {
                    pickable->execute(entity);  // Call execute with the entity reference
                    return;
                }
                std::cout << "You can't pick up " << entityName << "!\n";
                return;
            }
        }
        std::cout << entityName << " not found here.\n";
    }

    // Custom handling for "check health of <entity>" command
    else if (resolvedInput.find("check health of ") == 0) {
        std::string entityName = resolvedInput.substr(16);
        auto& locEntities = locationEntities[player.currentLocation];
        for (auto& entity : locEntities) {
            if (entity.getName() == entityName) {
                if (auto* health = entity.getPropertyComponent("Health")) {
                    std::cout << entityName << " has " << health->getProperties().at("health") << " health.\n";
                    return;
                }
                std::cout << entityName << " does not have a health attribute.\n";
                return;
            }
        }
        std::cout << entityName << " not found here.\n";
    }

    // Standard command processing
    else {
        for (const auto& pair : commandMap) {
            const std::string& key = pair.first;
            if (resolvedInput.rfind(key, 0) == 0) {
                pair.second->execute(resolvedInput, player, gameWorld, locationEntities, inventory);
                return;
            }
        }
        std::cout << "Invalid command." << std::endl;
    }
}

void CMD::addAlias(const std::string& alias, const std::string& command) {
    aliasCommand.addAlias(alias, command);
}

std::string CMD::resolveAlias(const std::string& input) const {
    return aliasCommand.getOriginalCommand(input);
}
