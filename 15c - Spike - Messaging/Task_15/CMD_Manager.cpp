#include "CMD_Manager.h"

void CMD_Manager::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {
	cmd.executeCommand(input, player, gameWorld, locationEntities, inventory);
}