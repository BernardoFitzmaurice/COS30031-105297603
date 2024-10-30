#ifndef ALIAS_COMMAND_H
#define ALIAS_COMMAND_H

#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>

class AliasCommand{
private:
	std::unordered_map<std::string, std::string> aliasMap;

public:
	void addAlias(const std::string& alias, const std::string& command);
	std::string getOriginalCommand(const std::string& alias) const;

	void processAliasCommand(const std::string& input);
};

#endif