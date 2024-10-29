#include <iostream>
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<std::string> items;
    bool coinAdded;

public:
    Inventory() : items{ "Sword", "Body Armor", "Shield", "Frog" }, coinAdded(false) {}

    void viewInventory() const {
        std::cout << "Inventory: ";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << items[i];
            if (i != items.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    void addCoin() {
        if (!coinAdded) {
            items.push_back("Coin");
            coinAdded = true;
        }
        else {
            std::cout << "You already have a coin in your inventory." << std::endl;
        }
    }

    void removeFrog() {
        auto it = std::find(items.begin(), items.end(), "Frog");
        if (it != items.end()) {
            items.erase(it);
            std::cout << "Frog removed from your inventory." << std::endl;
        }
    }
};