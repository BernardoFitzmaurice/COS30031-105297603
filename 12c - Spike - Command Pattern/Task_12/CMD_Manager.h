#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include <map>
#include <vector>
#include <string>
#include "CMD.h"
#include "Player.h"
#include "Location.h"
#include "Entity.h"
#include "Inventory.h"

class CMD_Manager {
private:
	CMD cmd;

public:
	void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory);
};

#endif 