#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <vector>

class Entity {
private:
    std::string name;
    std::string description;
	bool isContainer; // Can a entity contain other entities?
    std::vector<Entity> containedEntities; // Nested entities

public:
    Entity(const std::string& name, const std::string& description, bool container = false);

    // Accessor functions to get the name and description
    std::string getName() const;
    std::string getDescription() const;
	bool canContainEntities() const;
	void addEntity(const Entity& entity);
	bool removeEntity(const std::string& entityName);
	void displayContents() const;
};

#endif