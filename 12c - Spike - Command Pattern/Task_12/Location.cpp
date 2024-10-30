#include "Location.h"
#include <iostream>

Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Location::addConnection(const std::string& direction, const std::string& destination) {
    connections[direction] = destination;
}

void Location::addEntity(const Entity& entity) {
	entities.push_back(entity);
}

void Location::displayConnections() const {
    // Display connections
    std::cout << "Possible connections: ";
    for (const auto& pair : connections) {
        std::cout << pair.first << " -> " << pair.second << " ";
    }
    std::cout << std::endl;
}

void Location::displayEntities() const {
	// Display entities in the location
	std::cout << "Entities in " << name << ": " << std::endl;
	for (const Entity& entity : entities) {
		std::cout << "- " << entity.getName() << ": " << entity.getDescription() << std::endl;
	}
}