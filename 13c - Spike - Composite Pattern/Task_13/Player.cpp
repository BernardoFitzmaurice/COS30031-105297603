#include "Player.h"
#include <iostream>

Player::Player(const std::string& startLocation) : currentLocation(startLocation) {}

void Player::move(const std::string& direction, const std::map<std::string, Location>& gameWorld) {
    // 'Go' command - allows player to move in a specified direction
    const Location& loc = gameWorld.at(currentLocation);
    if (loc.connections.find(direction) != loc.connections.end()) {
        currentLocation = loc.connections.at(direction); // Move to new location
        std::cout << "Moved to " << currentLocation << std::endl;
    }
    else {
        std::cout << "You crashed to a wall like a frog.\n" << std::endl;
    }
}