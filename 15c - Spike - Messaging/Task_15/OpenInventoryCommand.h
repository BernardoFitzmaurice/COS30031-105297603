#ifndef OPEN_INVENTORY_COMMAND_H
#define OPEN_INVENTORY_COMMAND_H

#include "Inventory.h"
#include "Command.h"

class OpenInventoryCommand : public Command {
public:
	void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;
};

#endif