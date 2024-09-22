#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
	//Open the .json file
	std::ifstream inputFile("text3.json");

	if (!inputFile.is_open())
	{
		std::cout << "Error: File not found" << std::endl;
		return 1;
	}

	json jsonData;
	inputFile >> jsonData;

	/*
	//Print data as a hole
	//Gonna commented, but live it here just in case
	std::cout << "Information: " << std::endl;
	std::cout << jsonData.dump(4) << std::endl;
	*/

	//Access data individualy
	std::cout << "exp: " << jsonData["exp"] << std::endl;
	std::cout << "health: " << jsonData["health"] << std::endl;
	std::cout << "jsonType: " << jsonData["jsonType"] << std::endl;
	std::cout << "level: " << jsonData["level"] << std::endl;
	std::cout << "name: " << jsonData["name"] << std::endl;
	std::cout << "uuid: " << jsonData["uuid"] << std::endl;

	return 0;
}