#include "Debug_Tree.h"
#include <iostream>

void Debug_Tree::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

	const std::string& locationName = player.currentLocation;
    if (gameWorld.find(locationName) != gameWorld.end()) {
		const Location& location = gameWorld.at(locationName);

		std::cout << "Loading: " << location.name << "\nConnections: ";
        for (const auto& connection : location.connections) {
			std::cout << " " << connection.first << " -> " << connection.second << "\n";
        }

		std::cout << "Entities in location: ";
        if (locationEntities.find(locationName) != locationEntities.end()) {
            for (const auto& entity : locationEntities.at(locationName)) {
				std::cout << " -" << entity.getName() << "\n";
            }
        }
        else {
			std::cout << "No entities found.\n";
        } 
    }
    else {
        std::cout << "Invalid location: " << locationName << std::endl;
    }
}