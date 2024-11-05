#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include "Command.h"
#include <iostream>

class HelpCommand : public Command {
public:
	void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;
};

#endif