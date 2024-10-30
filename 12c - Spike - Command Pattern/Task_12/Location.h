#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "Entity.h"

class Location {
public:
    std::string name;
    std::string description;
    std::map<std::string, std::string> connections; // direction -> location name
	std::vector<Entity> entities; // Entities in the location

    Location() = default;
    Location(const std::string& name, const std::string& description);

    void addConnection(const std::string& direction, const std::string& destination);
	void addEntity(const Entity& entity);
    void displayConnections() const;
	void displayEntities() const;
};

#endif