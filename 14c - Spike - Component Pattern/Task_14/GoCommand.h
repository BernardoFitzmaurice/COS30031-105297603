#ifndef GO_COMMAND_h
#define GO_COMMAND_h

#include <string>
#include <map>
#include "Player.h"
#include "Location.h"
#include "Command.h"

class GoCommand: public Command {
public:
	void execute(const std::string& input, Player& player, 
		std::map<std::string, Location>& gameWorld,
		std::map<std::string, std::vector<Entity>>& locationEntities,
		Inventory& inventory) override;
};

#endif