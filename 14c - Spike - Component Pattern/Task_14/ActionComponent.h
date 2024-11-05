#ifndef ACTION_COMPONENT_H
#define ACTION_COMPONENT_H

#include <string>

// Forward declaration of Entity
class Entity;

class ActionComponent {
public:
    virtual ~ActionComponent() = default;
    virtual std::string getType() const = 0;
    virtual void execute(Entity& entity) = 0;  // Ensure execute takes Entity& as parameter
};

#endif
