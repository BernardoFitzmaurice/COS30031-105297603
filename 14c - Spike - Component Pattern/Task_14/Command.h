#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <map>
#include "Player.h"
#include "Location.h"
#include "Entity.h"
#include "Inventory.h"

class Command {
public:
    virtual void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) = 0;

	virtual ~Command() = default; // Ensures proper cleanup of derivad classes
};

#endif