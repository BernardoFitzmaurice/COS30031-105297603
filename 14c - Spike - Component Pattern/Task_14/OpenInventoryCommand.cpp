#include "OpenInventoryCommand.h"

void OpenInventoryCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {
	inventory.manageInventory();
}