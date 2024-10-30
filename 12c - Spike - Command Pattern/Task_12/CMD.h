#ifndef CMD_H
#define CMD_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "GoCommand.h"
#include "LookAtCommand.h"
#include "OpenInventoryCommand.h"
#include "AliasCommand.h"
#include "Command.h"
#include "AliasCommand.h"
#include "Debug_Tree.h"
#include "HelpCommand.h"

class CMD {
private:
    GoCommand goCommand;
    LookAtCommand lookAtCommand;
    OpenInventoryCommand openInventoryCommand;
    AliasCommand aliasCommand;
	Debug_Tree debugTree;

	std::unordered_map<std::string, std::unique_ptr<Command>> commandMap;

public:
    CMD() {
        // Register commands
        commandMap["go"] = std::make_unique<GoCommand>();
        commandMap["lookat"] = std::make_unique<LookAtCommand>();
        commandMap["open inventory"] = std::make_unique<OpenInventoryCommand>();
        commandMap["debug tree"] = std::make_unique<Debug_Tree>();
        commandMap["help"] = std::make_unique<HelpCommand>();
    }
	void executeCommand(const std::string& input, Player& player,
        std::map<std::string, Location>& gameWorld,
        std::map<std::string, std::vector<Entity>>& locationEntities,
        Inventory& inventory);

    void addAlias(const std::string& alias, const std::string& command);
    std::string resolveAlias(const std::string& input) const;
};

#endif // !CMD_H