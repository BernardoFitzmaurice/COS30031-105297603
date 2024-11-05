#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "PropertyComponent.h"
#include "ActionComponent.h"

class Entity {
private:
    std::string name;
    std::string description;
	bool isContainer; // Can a entity contain other entities?
    std::vector<Entity> containedEntities; // Nested entities
    std::unordered_map<std::string, std::unique_ptr<PropertyComponent>> propertyComponents;
    std::unordered_map<std::string, std::unique_ptr<ActionComponent>> actionComponents;

public:
    // Constructor
    Entity(const std::string& name, const std::string& description, bool container = false);

    // Delete copy constructor and copy assignment operator
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Define move constructor and move assignment operator
    Entity(Entity&&) noexcept = default;
    Entity& operator=(Entity&&) noexcept = default;

    // Accessor functions to get the name and description
    std::string getName() const;
    std::string getDescription() const;
    bool canContainEntities() const;

    // Managing contained entities
    void addNestedEntity(Entity&& entity);  // Pass by rvalue reference for move semantics
    bool removeNestedEntity(const std::string& entityName);
    void displayContents() const;

    // Component management
    void addPropertyComponent(std::unique_ptr<PropertyComponent> component);
    void addActionComponent(std::unique_ptr<ActionComponent> component);
    PropertyComponent* getPropertyComponent(const std::string& type);
    ActionComponent* getActionComponent(const std::string& type);

};

#endif