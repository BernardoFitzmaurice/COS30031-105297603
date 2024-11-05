#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "PropertyComponent.h"
#include <unordered_map>

class HealthComponent : public PropertyComponent {
public:
    HealthComponent(int health);
    std::string getType() const override;
    std::unordered_map<std::string, int> getProperties() const override;

private:
    int health;
};

#endif