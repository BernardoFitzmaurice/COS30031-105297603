#include "Entity.h"

Entity::Entity(const std::string& name, const std::string& description)
	: name(name), description(description) {}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getDescription() const {
    return description;
}

void Entity::addEntity(std::shared_ptr<Entity> entity) {
    containedEntities.push_back(entity);
}

std::vector<std::shared_ptr<Entity>> Entity::getEntities() const {
    return containedEntities;
}

std::shared_ptr<Entity> Entity::findEntity(const std::string& name) const {
    for (const auto& entity : containedEntities) {
        if (entity->getName() == name) {
            return entity;
        }
    }
    return nullptr;
}