#include "Inventory.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory() : items{ "Sword", "Body Armor", "Shield", "Frog" }, coinAdded(false) {}

void Inventory::viewInventory() const {
    std::cout << "Inventory: ";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << items[i];
        if (i != items.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Inventory::addCoin() {
    if (!coinAdded) {
        items.push_back("Coin");
        coinAdded = true;
        std::cout << "Coin added to inventory." << std::endl;
    }
    else {
        std::cout << "You already have a coin in your inventory." << std::endl;
    }
}

void Inventory::removeFrog() {
    auto it = std::find(items.begin(), items.end(), "Frog");
    if (it != items.end()) {
        items.erase(it);
        std::cout << "Frog removed from your inventory." << std::endl;
    }
    else {
        std::cout << "No Frog found in your inventory." << std::endl;
    }
}

void Inventory::manageInventory() {
    int choice;
    do {
        viewInventory();
        std::cout << "\n1: Pick up a coin\n2: Remove Frog\n3: Exit Inventory\nChoice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            addCoin();
            break;
        case 2:
            removeFrog();
            break;
        case 3:
            std::cout << "Closing inventory.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}
