#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>

class Entity {
public:
    Entity(const std::string& name, const std::string& description);

    // Accessor functions to get the name and description
    std::string getName() const;
    std::string getDescription() const;

private:
    std::string name;
    std::string description;
};

#endif