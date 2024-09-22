#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	//Reading text2
	ifstream inputFile("text2.txt"); //Open file
	if (!inputFile) //Check if file is open
	{
		cout << "Error opening file." << endl;
		return 1;
	}

	std::string line;
	while (std::getline(inputFile, line)) //Read file line by line
	{
		//Trim whitespace
		line.erase(0, line.find_first_not_of(" \t\n\r")); // Trim leading whitespace
		line.erase(line.find_last_not_of(" \t\n\r") + 1); // Trim trailing whitespace

		//Ignore blank lines
		if (line.empty())
		{
			continue;
		}

		//Ignore lines that start with #
		if (line[0] == '#')
		{
			continue;
		}

		//Split line by ":"
		std::istringstream ss(line);
		std::string token;
		vector<string> tokens;
		while (getline(ss, token, ':'))
		{
			tokens.push_back(token);
		}

		//Check number of tokens
		if (tokens.size() == 3)
		{
			//Print token on new line
			for (const auto& t : tokens)
			{
				cout << t << endl;
			}
		}
		else 
		{
			cout << "Invalid number of tokens: " << line << endl;
		}
	}

	inputFile.close(); //Close file

	return 0;
}