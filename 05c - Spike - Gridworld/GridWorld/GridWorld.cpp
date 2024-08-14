#include <iostream>

int main()
{
	// Declare 2D 3x3 grid
    char grid[5][5];

	// Initialize values
	// i = row, j = column
	// TRY TO FIND A DIFFERENT WAY TO MAKE THE BORDER '#' AND THE INSIDE ' '
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == 0 || i == 4 || j == 0 || j == 4) {
				grid[i][j] = '#';
			}
			else if (i == 3 && j == 2) {
				grid[i][j] = 'S';
			}
			else if (i == 1 && j == 2 || i == 3 && j == 1 || i == 3 && j == 3) {
				grid[i][j] = 'D';
			}
			else if (i == 1 && j == 3) {
				grid[i][j] = 'G';
			}
			else {
				grid[i][j] = ' ';
			}
			
		}
	}

	// Print grid
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu