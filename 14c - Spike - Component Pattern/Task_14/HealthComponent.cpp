#include "HealthComponent.h"

HealthComponent::HealthComponent(int health) : health(health) {}

std::string HealthComponent::getType() const {
    return "Health";
}

std::unordered_map<std::string, int> HealthComponent::getProperties() const {
    return { {"health", health} };
}