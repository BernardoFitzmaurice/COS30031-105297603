#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <string>

class Inventory {
private:
    std::vector<std::string> items;
    bool coinAdded;

public:
    Inventory();
    void viewInventory() const;
    void addCoin();
    void removeFrog();

    // New function to handle inventory actions
    void manageInventory();
};

#endif