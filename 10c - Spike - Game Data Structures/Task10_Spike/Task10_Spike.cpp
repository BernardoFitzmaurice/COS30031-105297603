#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> Inventory = { "Sword", "\nBody Armor", "\nShield", "\nFrog"};


	int choice;
	do {
		//Print vector
		std::cout << "View inventory:" << std::endl;
		for (int i = 0; i < Inventory.size(); i++)
		{
			std::cout << Inventory[i];
			if (i != Inventory.size() - 1)
			{
				std::cout << ", ";
			}
		}
		std::cout << std::endl;

		//Add and Remove item to inventory
		std::cout << "\nEnter your choice: \nTo pick up a coin: 1 \nTo remove The Frog and ruin you life: 2 \nTo exit inventory: 3" << std::endl;
		std::cin >> choice;

		switch (choice) {
			//Add coin to inventory
		case 1:
			Inventory.push_back("\nCoin");
			break;

			//Remove Mitic Frog from inventory and ruin your life
		case 2:
			for (int i = Inventory.size() - 1; i >= 0; i--)
			{
				if (Inventory[i] == "\nFrog")
				{
					Inventory.erase(Inventory.begin() + i);
				}
			}
			break;

			//Exit inventory
		case 3:
			break;

		default:
			std::cout << "Invalid choice" << std::endl;
		}
	} while (choice != 3);

	return 0;
}