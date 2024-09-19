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
		cout << line << endl;
	}

	inputFile.close(); //Close file

	return 0;
}