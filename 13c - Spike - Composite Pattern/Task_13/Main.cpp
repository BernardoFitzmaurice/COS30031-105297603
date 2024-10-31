#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include "Location.h"
#include "Player.h"
#include "Inventory.h"
#include "Entity.h"
#include "CMD_Manager.h"

using namespace std;

// Convert string to lowercase
string lowercase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <Adventure.txt>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    map<string, Location> gameWorld; // A graph to store the game locations
    map<string, vector<Entity>> locationEntities; // Entities in each location
    string line, locationName;

    cout << "Starting to load adventure data..." << endl;

    while (getline(inputFile, line)) {
        if (line.find("Location") != string::npos) {
            Location loc;
            locationName = line.substr(line.find(":") + 2);
            loc.name = locationName;

            getline(inputFile, line);
            loc.description = line.substr(line.find(":") + 2);

            // Read connections for the location
            getline(inputFile, line);
            string connections = line.substr(line.find(":") + 2);
            stringstream ss(connections);
            string connection;

            while (getline(ss, connection, ',')) {
                size_t equalPos = connection.find("=");
                if (equalPos != string::npos) {
                    string direction = connection.substr(0, equalPos);
                    string destLocation = connection.substr(equalPos + 1);

                    // Remove extra spaces and lowercase direction
                    direction.erase(direction.find_last_not_of(' ') + 1);
                    destLocation.erase(0, destLocation.find_first_not_of(' '));
                    direction = lowercase(direction);

                    loc.addConnection(direction, destLocation);
                }
                else {
                    std::cerr << "Error parsing connection in line: " << line << std::endl;
                }
            }

            gameWorld[loc.name] = loc; // Add location to the game world
            cout << "Loaded location: " << loc.name << endl; // Debug
        }
        else if (line.find("Entities") != string::npos) {
            vector<string> entities;
            string entityNames = line.substr(line.find(":") + 2);
            stringstream ss(entityNames);
            string entityName;

            while (getline(ss, entityName, ',')) {
                entityName.erase(entityName.find_last_not_of(' ') + 1); // trim spaces
                entities.push_back(entityName);
            }

            for (const string& entityName : entities) {
                getline(inputFile, line);
                string entityDesc = line.substr(line.find(":") + 2);
                Entity mainEntity(entityName, entityDesc);

                // Check if entity has nested entities
                while (getline(inputFile, line) && line.find("Contained") != string::npos) {
                    string containedEntityName = line.substr(line.find(":") + 2);
                    getline(inputFile, line);
                    string containedEntityDesc = line.substr(line.find(":") + 2);

                    auto nestedEntity = std::make_shared<Entity>(containedEntityName, containedEntityDesc);
                    mainEntity.addEntity(nestedEntity);
                }

                locationEntities[locationName].push_back(mainEntity);
            }
            cout << "Loaded entities for location: " << locationName << endl; // Debug
        }
    }

    inputFile.close();
    cout << "Adventure data loaded successfully." << endl;

    // Initialize player and command manager
    Player player("Kitchen"); // Starting location, no lowercase conversion
    Inventory playerInventory;
    CMD_Manager commandManager;

    string input;
    while (true) {
        // Show location details
        Location& loc = gameWorld[player.currentLocation];
        cout << "\nThe location you're in is: " << loc.name << endl;
        cout << loc.description << endl;
        loc.displayConnections();

        if (locationEntities.find(loc.name) != locationEntities.end()) {
            cout << "Entities in this location: ";
            for (const auto& entity : locationEntities[loc.name]) {
                cout << entity.getName() << ", ";
            }
            cout << endl;
        }

        // User input
        cout << "\nCommands:\n- go <direction>\n- help\n- open inventory\n- lookat <entity>\n- alias <command - new command>\n- debug tree\n- quit\nEnter command: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        // Pass input to command manager
        commandManager.execute(input, player, gameWorld, locationEntities, playerInventory);
    }

    return 0;
}
