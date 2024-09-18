#include <iostream>
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
	Goku.tacos = 2;

	//Writing values to text file
	//ofstream outFile("");

	//Outpot to the console
	std::cout << "Goku's frog is: " << Goku.frog << endl;
	std::cout << "Goku's power level is: " << Goku.power << endl;
	std::cout << "Goku's taco count is: " << Goku.tacos << endl;

	return 0;
}