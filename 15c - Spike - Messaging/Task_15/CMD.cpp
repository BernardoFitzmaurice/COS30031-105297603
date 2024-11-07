#include "CMD.h"
#include <iostream>

void CMD::executeCommand(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    aliasCommand.processAliasCommand(input); // Process alias command input

    std::string resolvedInput = resolveAlias(input); // Resolve aliases before executing

    // Debug output to verify resolved command
    //std::cout << "Resolved Command: " << resolvedInput << std::endl;

    // Check if the input starts with any command registered
    for (const auto& pair : commandMap) { // Use 'pair' to hold the key-value pair
        const std::string& key = pair.first; // Access the key
        const std::unique_ptr<Command>& command = pair.second; // Access the command

        if (resolvedInput.find(key) == 0) { // If the input starts with the command key
            command->execute(resolvedInput, player, gameWorld, locationEntities, inventory);
            return; // Command executed, return early
        }
    }
    std::cout << "Invalid command." << std::endl;
}

void CMD::addAlias(const std::string& alias, const std::string& command) {
    aliasCommand.addAlias(alias, command); // Add alias to instance
}

std::string CMD::resolveAlias(const std::string& input) const {
    return aliasCommand.getOriginalCommand(input); // Get original command
}