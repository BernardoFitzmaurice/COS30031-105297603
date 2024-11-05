#ifndef TAKE_COMMAND_H
#define TAKE_COMMAND_H

#include "Command.h"
#include "Player.h"
#include "Location.h"
#include "Entity.h"
#include "Inventory.h"
#include <map>
#include <vector>

class TakeCommand : public Command {
public:
    void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;
};

#endif