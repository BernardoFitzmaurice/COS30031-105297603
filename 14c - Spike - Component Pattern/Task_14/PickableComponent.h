#ifndef PICKABLE_COMPONENT_H
#define PICKABLE_COMPONENT_H

#include "ActionComponent.h"
#include <iostream>

class PickableComponent : public ActionComponent {
public:
    std::string getType() const override;
    void execute(Entity& entity) override;  // Ensure this matches ActionComponent's execute method
};

#endif