#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <iostream>

class Location {
public:
    std::string name;
    std::string description;
    std::map<std::string, std::string> connections; // direction -> location name

    Location() = default;
    Location(const std::string& name, const std::string& description);

    void addConnection(const std::string& direction, const std::string& destination);
    void displayConnections() const;
};

#endif