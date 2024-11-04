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

void Entity::addEntity(const Entity& entity) {
	if (isContainer) {
		containedEntities.push_back(entity);
		std::cout << entity.getName() << "added to " << name << '\n';
	}
}

bool Entity::removeEntity(const std::string& entityName) {
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
            std::cout << "- " << entity.getName() << "\n";
        }
    }
    else {
        std::cout << name << " is empty.\n";
    }
}