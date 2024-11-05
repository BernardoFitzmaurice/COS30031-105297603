#ifndef DEBUG_TREE_H
#define DEBUG_TREE_H

#include <string>
#include <map>
#include <vector>
#include "Location.h"
#include "Entity.h"
#include "Command.h"

class Debug_Tree : public Command {
public:
	// Display all connections and entities
	void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;
};

#endif