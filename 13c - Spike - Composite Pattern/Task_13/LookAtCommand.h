#ifndef LOOK_AT_COMMAND_H
#define LOOK_AT_COMMAND_H

#include <map>
#include <vector>
#include <string>
#include "Entity.h"
#include "Player.h"
#include "Command.h"

class LookAtCommand : public Command {
public:
    void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;

private:
    void lookInsideEntity(const Entity& entity);
};

#endif