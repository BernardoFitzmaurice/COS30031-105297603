#include <iostream>
#include <cstdlib>
#include <ctime>
// I needed to include cstdlib and ctime for section 5
#include <sstream>
#include <string>
// I needed to include sstream and string for section 6

#define SECTION1 true;
#define SECTION2 true;
#define SECTION3 true;
#define SECTION4 true;
#define SECTION5 true;
#define SECTION6 true;
#define SECTION7 true;

// Section 1
void printValues(int value1, int value2) {
    std::cout << "Value 1: " << value1 << std::endl;
    std::cout << "Value 2: " << value2 << std::endl;
}

// Section 2
// orgvalue = Original Value. altvalue = Alter Value.
void alterValue(int orgvalue, int altvalue) {
    std::cout << "Original Value: " << orgvalue << std::endl;
    std::cout << "Alter Value: " << altvalue << std::endl;
}

// Section 5
void FiveIntArray() {
	// The seed for the random number generator
    std::srand(std::time(0));

    // Generate and print the random numbers
    std::cout << "Five numbers: ";
    for (int i = 0; i < 5; i++) {
        std::cout << (std::rand() % 100) << " ";
    }
    std::cout << std::endl;
}

// Section 7
class FE3H {
private:
    int releaseDate;

public:
    std::string developer;

    void info() {
        std::cout << "Fire emblem 3 houses developer is: " << developer << " and the release date was: " << releaseDate << std::endl;
    }

    FE3H(int releaseDate, std::string developer) : releaseDate(releaseDate), developer(developer) {}
};

int main() {
#if SECTION1
    // Section 1
	std::cout << "Section 1" << std::endl;

    // Call the function with two values
    printValues(10, 20);
    //return 0;
#endif

#if SECTION2
	// Section 2
    std::cout << "\nSection 2" << std::endl;

    // Original value = 10, allter value = Original value + 4
    // Then print both origial and alter values
    int orgvalue = 10;
    int altvalue = orgvalue + 4;
	alterValue(orgvalue, altvalue);
#endif

#if SECTION3

    // Section 3
    std::cout << "\nSection 3" << std::endl;

    // 1st i declare the variable as int and the pointer (ptr) as 'int *', making it point to the int variable
    int variable;
    int *ptr;

    // I use the address of operator & to get the address of the variable and I set the value of the variable at 18
    // I did this by using the dereference operatror * at the pointer, giving me access to the variable that the pointer is pointing to
    ptr = &variable;
    *ptr = 18;

    // Por ultimo se lee e imprime la variable usando el pointer, y luego usando la variable para comprobar que todo este correcto
	std::cout << "Value of variable: " << *ptr << std::endl;
	std::cout << "Value of variable (verifying): " << variable << std::endl;

#endif

#if SECTION4

	// Section 4 (i had no need to create any void function)
    std::cout << "\nSection 4 " << std::endl;

    for (int i = 1; i <= 20; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

#endif

#if SECTION5

	// Section 5
    std::cout << "\nSection 5 " << std::endl;

    FiveIntArray();

#endif

#if SECTION6

    // Section 6 (just like in section 4, i had no need to create any void function)
    std::cout << "\nSection 6 " << std::endl;

    std::string text = "I'm really tired right now";
    std::istringstream frase(text);
    std::string space;

    while (frase >> space) {
        std::cout << space << std::endl;
    }

#endif

#if SECTION7
    // Class stated before the main
    std::cout << "\nSection 7 " << std::endl;

    FE3H ip(2019, "Nintendo");

    ip.developer = "Intelligent Systems";

    ip.info();

#endif

    return 0;
}