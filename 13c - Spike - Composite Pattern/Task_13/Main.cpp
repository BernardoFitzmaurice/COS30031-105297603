#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
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

    map<string, Location> gameWorld;  // A graph to store the game locations
    map<string, vector<Entity>> locationEntities;  // Entities in each location
    string line, locationName, description, connections;

    while (getline(inputFile, line)) {
        if (line.find("Location") != string::npos) {
            Location loc;

            // Extract location name
            size_t colonPos = line.find(":");
            if (colonPos != string::npos) {
                locationName = line.substr(colonPos + 2);
                loc.name = locationName;  // Keep the original case
            }
            else {
                cout << "Error: Missing ':' in line: " << line << endl;
                continue;  // Skip this line
            }

            // Read the description
            getline(inputFile, line);
            colonPos = line.find(":");
            if (colonPos != string::npos) {
                description = line.substr(colonPos + 2);
                loc.description = description;
            }
            else {
                cout << "Error: Missing ':' in line: " << line << endl;
                continue;
            }

            // Read the connections
            getline(inputFile, line);
            colonPos = line.find(":");
            if (colonPos != string::npos) {
                connections = line.substr(colonPos + 2);
            }
            else {
                cout << "Error: Missing ':' in line: " << line << endl;
                continue;
            }

            // Analyze the connections
            stringstream ss(connections);
            string connection;

            while (getline(ss, connection, ',')) {
                size_t equalPos = connection.find("=");
                if (equalPos != string::npos) {
                    string direction = connection.substr(0, equalPos);
                    string destLocation = connection.substr(equalPos + 1);

                    // Remove extra spaces
                    direction.erase(direction.find_last_not_of(' ') + 1);
                    destLocation.erase(0, destLocation.find_first_not_of(' '));

                    direction = lowercase(direction);  // Convert to lowercase

                    // Store the connection
                    loc.addConnection(direction, destLocation);
                    cout << "Loading " << locationName << " direction: " << direction << " -> " << destLocation << '\n';  // Debug
                }
                else {
                    cout << "Error: Missing '=' in connection: " << connection << endl;
                }
            }

            // Add the location to the game
            gameWorld[loc.name] = loc;
        }
        else if (line.find("Entities") != string::npos) {
            size_t colonPos = line.find(":");
            if (colonPos != string::npos) {
                string entityNames = line.substr(colonPos + 2);
                vector<string> entities;
                stringstream ss(entityNames);
                string entityName;

                while (getline(ss, entityName, ',')) {
                    entities.push_back(entityName);
                }

                for (const string& entityName : entities) {
                    getline(inputFile, line);
                    colonPos = line.find(":");
                    if (colonPos != string::npos) {
                        string entityDesc = line.substr(colonPos + 2);

                        // Check if this entity is marked as a container
                        bool isContainer = (entityDesc.find("Container=true") != string::npos);

                        // Create the entity with container status and add it to location entities
                        Entity newEntity(entityName, entityDesc, isContainer);
                        locationEntities[locationName].push_back(newEntity);
                    }
                    else {
                        cout << "Error: Missing ':' in entity description line: " << line << endl;
                    }
                }
            }
            else {
                cout << "Error: Missing ':' in Entities line: " << line << endl;
            }
        }
        // Handling standalone Entity entries to place them within specified containers
        else if (line.find("Entity:") != string::npos) {
            // Extract entity name
            string entityName = line.substr(line.find(":") + 2);

            // Extract the description line
            getline(inputFile, line);
            string entityDesc = line.substr(line.find(":") + 2);

            // Extract location/container line
            getline(inputFile, line);
            string containerName = line.substr(line.find(":") + 2);

            // Create the entity and add to its container
            Entity nestedEntity(entityName, entityDesc);

            // Search for the container in the locationEntities map
            auto& entitiesInLocation = locationEntities[locationName];
            auto containerIt = std::find_if(entitiesInLocation.begin(), entitiesInLocation.end(),
                [&containerName](const Entity& e) { return e.getName() == containerName && e.canContainEntities(); });

            if (containerIt != entitiesInLocation.end()) {
                containerIt->addNestedEntity(nestedEntity);  // Add entity to container
            }
            else {
                cout << "Error: Container not found for entity " << entityName << " in location " << locationName << endl;
            }
        }

    }

    inputFile.close();

    Player player("Kitchen");  // Starting location, no lowercase conversion
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
        cout << "\nCommands:\n- go <direction>\n- help\n- open inventory\n- lookat <entity>\n- lookin <entity>\n- put <entity> in <container>\n- take <entity> from <container>\n- alias <command - new command>\n- debug tree\n- quit\nEnter command: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Exiting the game." << endl;
            break;
        }
        // Pass input to command manager
        commandManager.execute(input, player, gameWorld, locationEntities, playerInventory);
    }

    return 0;
}
