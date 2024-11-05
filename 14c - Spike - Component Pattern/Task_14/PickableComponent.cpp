#include "PickableComponent.h"
#include "Entity.h"

std::string PickableComponent::getType() const {
    return "Pickable";
}

void PickableComponent::execute(Entity& entity) {
    std::cout << "You picked up the " << entity.getName() << "!" << std::endl;
}