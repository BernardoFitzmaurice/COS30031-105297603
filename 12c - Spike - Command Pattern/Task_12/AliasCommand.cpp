#include "AliasCommand.h"

// Alias a command 'remaps' ('move' -> 'go')
void AliasCommand::addAlias(const std::string& alias, const std::string& command) {
	aliasMap[command] = alias;
}

// Get the original command from an alias
std::string AliasCommand::getOriginalCommand(const std::string& input) const {
    std::istringstream iss(input);
    std::string firstWord;
    iss >> firstWord;

	auto it = aliasMap.find(firstWord);
	if (it != aliasMap.end()) {
        //replace the first word with it->second
        std::string resolvedCommand = it->second + input.substr(firstWord.length());
		return resolvedCommand;
	}
	return input; // Return OG command if no alias is found
}

void AliasCommand::processAliasCommand(const std::string& input) {
    if (input.substr(0, 5) == "alias") {
        // Extract alias and command, assuming input is in the form: alias <alias> <command>
        std::istringstream iss(input);
        std::string cmdType, alias, command;
        iss >> cmdType >> alias;
        std::getline(iss, command); // Get the rest of the line as the command

        if (!command.empty() && command[0] == ' ') {
            command = command.substr(1); // Remove leading space
        }
        addAlias(alias, command); // Add the alias to the alias map
        std::cout << "Alias added: " << alias << " -> " << command << std::endl;
    }
}