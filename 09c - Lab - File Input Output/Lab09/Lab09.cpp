#include <iostream>
#include <fstream>
using namespace std;

class compoundType {
public:
    char frog;
    int power;
    float tacos;
};

int main()
{
	//Creating the instance of the class
    compoundType Goku;
	Goku.frog = 'E';
	Goku.power = 9000;
	Goku.tacos = 6.7;

	/*
	//Writing values to text file
	ofstream outFile("GokuData.txt");
	if (outFile.is_open()) {
		outFile << Goku.frog << endl;
		outFile << Goku.power << endl;
		outFile << Goku.tacos << endl;
		outFile.close();
	} else {
		std::cout << "Error opening file" << endl;
	}*/

	/*
	//Reading values from text file
	compoundType GokuFromFile;
	ifstream inFile("GokuData.txt"); 
	if (inFile.is_open()) {
		inFile >> GokuFromFile.frog;
		inFile >> GokuFromFile.power;
		inFile >> GokuFromFile.tacos;
		inFile.close();
	}
	else {
		std::cout << "Error opening file" << endl;
	}

	//Outpot to the console
	cout << "Goku's frog is: " << GokuFromFile.frog << endl;
	cout << "Goku's power level is: " << GokuFromFile.power << endl;
	cout << "Goku's taco count is: " << GokuFromFile.tacos << endl;
	*/

	/*
	//Values in binary file
	ofstream binFile("test1.bin", ios::binary); //Opens binari file in write mode
	if (binFile.is_open()) {
		binFile.write(reinterpret_cast<char*>(&Goku), sizeof(Goku)); //Write the binary
		binFile.close();
	} else {
		std::cout << "Error opening file" << endl;
	}
	*/

	//Reading values from binary file
	compoundType GokuFromBinary;
	ifstream binInputFile("test1.bin", ios::in | ios::binary); //Opens binary file in read mode

	if (binInputFile.is_open()) {
		binInputFile.read(reinterpret_cast<char*>(&GokuFromBinary), sizeof(GokuFromBinary)); //Read the binary
		binInputFile.close(); //close binary
	} else {
		std::cout << "Error opening file" << endl;
	}

	cout << "Goku's frog is: " << GokuFromBinary.frog << endl;
	cout << "Goku's power level is: " << GokuFromBinary.power << endl;
	cout << "Goku's taco count is: " << GokuFromBinary.tacos << endl;

	return 0;
}