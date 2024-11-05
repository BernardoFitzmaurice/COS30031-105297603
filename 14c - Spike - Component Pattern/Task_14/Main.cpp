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
#include "HealthComponent.h"
#include "PickableComponent.h"

using namespace std;

// Helper function to convert a string to lowercase
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

    map<string, Location> gameWorld;
    map<string, vector<Entity>> locationEntities;
    string line, locationName, description, connections;

    while (getline(inputFile, line)) {
        if (line.find("Location") != string::npos) {
            Location loc;
            size_t colonPos = line.find(":");
            if (colonPos != string::npos) {
                locationName = line.substr(colonPos + 2);
                loc.name = locationName;
            }
            else {
                cout << "Error: Missing ':' in line: " << line << endl;
                continue;
            }

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

            getline(inputFile, line);
            colonPos = line.find(":");
            if (colonPos != string::npos) {
                connections = line.substr(colonPos + 2);
            }
            else {
                cout << "Error: Missing ':' in line: " << line << endl;
                continue;
            }

            stringstream ss(connections);
            string connection;
            while (getline(ss, connection, ',')) {
                size_t equalPos = connection.find("=");
                if (equalPos != string::npos) {
                    string direction = connection.substr(0, equalPos);
                    string destLocation = connection.substr(equalPos + 1);

                    direction.erase(direction.find_last_not_of(' ') + 1);
                    destLocation.erase(0, destLocation.find_first_not_of(' '));
                    direction = lowercase(direction);

                    loc.addConnection(direction, destLocation);
                }
                else {
                    cout << "Error: Missing '=' in connection: " << connection << endl;
                }
            }

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
                        bool isContainer = (entityDesc.find("Container=true") != string::npos);
                        Entity newEntity(entityName, entityDesc, isContainer);

                        // Parse components based on keywords in description
                        if (entityDesc.find("Pickable=true") != string::npos) {
                            newEntity.addActionComponent(std::make_unique<PickableComponent>());
                        }

                        size_t healthPos = entityDesc.find("Health=");
                        if (healthPos != string::npos) {
                            int healthValue = std::stoi(entityDesc.substr(healthPos + 7));
                            newEntity.addPropertyComponent(std::make_unique<HealthComponent>(healthValue));
                        }

                        // Use emplace_back with move semantics to add the entity
                        locationEntities[locationName].emplace_back(std::move(newEntity));
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
        else if (line.find("Entity:") != string::npos) {
            // Parsing standalone entities (e.g., nested entities in containers)
            string entityName = line.substr(line.find(":") + 2);

            getline(inputFile, line);
            string entityDesc = line.substr(line.find(":") + 2);

            getline(inputFile, line);
            string containerName = line.substr(line.find(":") + 2);

            Entity nestedEntity(entityName, entityDesc);

            if (entityDesc.find("Pickable=true") != string::npos) {
                nestedEntity.addActionComponent(std::make_unique<PickableComponent>());
            }

            size_t healthPos = entityDesc.find("Health=");
            if (healthPos != std::string::npos) {
                int healthValue = std::stoi(entityDesc.substr(healthPos + 7));
                nestedEntity.addPropertyComponent(std::make_unique<HealthComponent>(healthValue));
            }

            // Locate the container entity and move the nested entity into it
            auto& entitiesInLocation = locationEntities[locationName];
            auto containerIt = std::find_if(entitiesInLocation.begin(), entitiesInLocation.end(),
                [&containerName](const Entity& e) { return e.getName() == containerName && e.canContainEntities(); });

            if (containerIt != entitiesInLocation.end()) {
                containerIt->addNestedEntity(std::move(nestedEntity));  // Move nested entity
            }
            else {
                cout << "Error: Container not found for entity " << entityName << " in location " << locationName << endl;
            }
        }
    }

    inputFile.close();

    Player player("Kitchen");
    Inventory playerInventory;
    CMD_Manager commandManager;

    string input;
    while (true) {
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

        cout << "\nEnter command: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Exiting the game." << endl;
            break;
        }

        commandManager.execute(input, player, gameWorld, locationEntities, playerInventory);
    }

    return 0;
}
