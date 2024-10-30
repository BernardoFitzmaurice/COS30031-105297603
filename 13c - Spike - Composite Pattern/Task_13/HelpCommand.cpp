#include "HelpCommand.h"

void HelpCommand::execute(const std::string& input, Player& player,
    std::map<std::string, Location>& gameWorld,
    std::map<std::string, std::vector<Entity>>& locationEntities,
    Inventory& inventory) {

    std::cout << "Available Commands:\n";
    std::cout << "GO - Change location.\n";
    std::cout << "HELP - Lists known commands and what they do.\n";
    std::cout << "INVENTORY - Items the player has.\n";
    std::cout << "LOOKAT - Show details of an entity.\n";
    std::cout << "ALIAS - Remap commands to another word the user wants.\n";
    std::cout << "DEBUG TREE - Show useful details of the game world and entities.\n";
}