#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Entity {
public:
    Entity(const std::string& name, const std::string& description);

    // Accessor functions to get the name and description
    std::string getName() const;
    std::string getDescription() const;

    // Methods to support nested entities
    void addEntity(std::shared_ptr<Entity> entity);
    std::vector<std::shared_ptr<Entity>> getEntities() const;
    std::shared_ptr<Entity> findEntity(const std::string& name) const;

private:
    std::string name;
    std::string description;
    std::vector<std::shared_ptr<Entity>> containedEntities;  // Entities contained within this entity
};

#endif