#include "Entity.h"
#include <iostream>

Entity::Entity(const std::string& name, const std::string& description, bool container)
    : name(name), description(description), isContainer(container) {}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getDescription() const {
    return description;
}

bool Entity::canContainEntities() const {
    return isContainer;
}

// Method to add an entity to the container using move semantics
void Entity::addNestedEntity(Entity&& entity) {
    if (isContainer) {
        // Display name before moving to avoid accessing moved-from object
        std::cout << entity.getName() << " added to " << name << "\n";
        containedEntities.emplace_back(std::move(entity));
    }
    else {
        std::cout << name << " is not a container and cannot hold entities.\n";
    }
}

bool Entity::removeNestedEntity(const std::string& entityName) {
    for (auto it = containedEntities.begin(); it != containedEntities.end(); ++it) {
        if (it->getName() == entityName) {
            containedEntities.erase(it);
            std::cout << entityName << " removed from " << name << ".\n";
            return true;
        }
    }
    return false;
}

void Entity::displayContents() const {
    if (!containedEntities.empty()) {
        std::cout << name << " contains:\n";
        for (const auto& entity : containedEntities) {
            std::cout << "- " << entity.getName() << ": " << entity.getDescription() << "\n";
        }
    }
    else {
        std::cout << name << " is empty.\n";
    }
}

// Move components into component maps
void Entity::addPropertyComponent(std::unique_ptr<PropertyComponent> component) {
    propertyComponents[component->getType()] = std::move(component);
}

void Entity::addActionComponent(std::unique_ptr<ActionComponent> component) {
    actionComponents[component->getType()] = std::move(component);
}

PropertyComponent* Entity::getPropertyComponent(const std::string& type) {
    return propertyComponents.count(type) ? propertyComponents[type].get() : nullptr;
}

ActionComponent* Entity::getActionComponent(const std::string& type) {
    return actionComponents.count(type) ? actionComponents[type].get() : nullptr;
}
