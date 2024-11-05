#include "Entity.h"

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

// Method to add an entity to the container
void Entity::addNestedEntity(const Entity& entity) {
    if (isContainer) {
        containedEntities.push_back(entity);
        std::cout << entity.getName() << " added to " << name << "\n";
    }
    else {
        std::cout << name << " is not a container and cannot hold entities.\n";
    }
}

// Method to remove an entity from the container by name
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