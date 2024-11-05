#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include "Location.h"

class Player {
public:
    std::string currentLocation;

    Player(const std::string& startLocation);

    void move(const std::string& direction, const std::map<std::string, Location>& gameWorld);
};

#endif