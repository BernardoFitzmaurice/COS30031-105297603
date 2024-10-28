#include "Location.h"

Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Location::addConnection(const std::string& direction, const std::string& destination) {
    connections[direction] = destination;
}

void Location::displayConnections() const {
    // Display connections
    std::cout << "Possible connections: ";
    for (const auto& pair : connections) {
        std::cout << pair.first << " -> " << pair.second << " ";
    }
    std::cout << std::endl;
}