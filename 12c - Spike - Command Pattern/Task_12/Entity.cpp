#include "Entity.h"

Entity::Entity(const std::string& name, const std::string& description)
	: name(name), description(description) {}

std::string Entity::getName() const {
    return name;
}

std::string Entity::getDescription() const {
    return description;
}