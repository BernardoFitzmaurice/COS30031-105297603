#include <iostream>

int main()
{
	// Declare 2D 5x5 grid
	char grid[5][5];

	// Initialize values
	// i = row, j = column
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			// Set boundaries with # as a wall
			if (i == 0 || i == 4 || j == 0 || j == 4 || i == 1 && j == 1) {
				grid[i][j] = '#';
			}

			// Pocitions of start as S, gold as G, and death as D
			else if (i == 3 && j == 2) {
				grid[i][j] = 'S';
			}
			else if (i == 1 && j == 2 || i == 3 && j == 1 || i == 3 && j == 3) {
				grid[i][j] = 'D';
			}
			else if (i == 1 && j == 3) {
				grid[i][j] = 'G';
			}

			// Set empty spaces
			else {
				grid[i][j] = ' ';
			}

		}
	}

	// Startin row and column of the player
	int row = 3;
	int col = 2;

	while (true) {

		// Print grid
		std::cout << "Maze:" << std::endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				std::cout << grid[i][j] << " ";
			}
			std::cout << std::endl;
		}

		// Print allowed directions
		std::cout << "Directions allowed: ";
		if (row > 1 && grid[row - 1][col] != '#') {
			std::cout << "N ";
		}
		if ( col > 1 && grid[row][col - 1] != '#') {
			std::cout << "W ";
		}
		if (row < 3 && grid[row + 1][col] != '#') {
			std::cout << "S ";
		}
		if (col < 3 && grid[row][col + 1] != '#') {
			std::cout << "E ";
		}
		std::cout << std::endl;

		// User input for direction
		char direction;
		std::cout << "Enter direction: ";
		std::cin >> direction;

		// Clear current position
		grid[row][col] = ' ';

		// Moving the player 
		switch (direction) {

		case 'N':
			if (row > 1 && grid[row - 1][col] != '#') {
				row--;
			}
			break;

		case 'W':
			if (col > 1 && grid[row][col - 1] != '#') {
				col--;
			}
			break;

		case 'S':
			if (row < 3 && grid[row + 1][col] != '#') {
				row++;
			}
			break;

		case 'E':
			if (col < 3 && grid[row][col + 1] != '#') {
				col++;
			}
			break;

		default:
			std::cout << "Invalid direction. Try otra vez" << std::endl;
			continue;
		}

		// Check if player won or died and display message
		if (grid[row][col] == 'G') {
			std::cout << "Damn! You win this time. Adios!" << std::endl;
			break;
		}
		else if (grid[row][col] == 'D') {
			std::cout << "Congrats! You died! Better luck next time" << std::endl;
			break;
		}

		grid[row][col] = 'S'; // Set new position
	}
	return 0;
}