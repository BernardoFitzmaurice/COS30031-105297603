#ifndef LOOKINCOMMAND_H
#define LOOKINCOMMAND_H

#include "Command.h"
#include <string>

class LookInCommand : public Command {
public:
    void execute(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory) override;
};

#endif