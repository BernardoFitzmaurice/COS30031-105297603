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

    map<string, Location> gameWorld; // A graph to store the game locations
	map<string, vector<Entity>> locationEntities; // Entities in each location

    string line, locationName, description, connections;

    while (getline(inputFile, line)) {
        if (line.find("Location") != string::npos) {
            Location loc;

            // Extract location name
            locationName = line.substr(line.find(":") + 2);
            loc.name = locationName;  // Keep the original case

            // Read the description
            getline(inputFile, line);
            description = line.substr(line.find(":") + 2);
            loc.description = description;

            // Read the connections
            getline(inputFile, line);
            connections = line.substr(line.find(":") + 2);

            // Analyze the connections
            stringstream ss(connections);
            string connection;

            while (getline(ss, connection, ',')) {
                size_t equalPos = connection.find("=");
                string direction = connection.substr(0, equalPos);
                string destLocation = connection.substr(equalPos + 1);

                // Remove extra spaces
                direction.erase(direction.find_last_not_of(' ') + 1);
                destLocation.erase(0, destLocation.find_first_not_of(' '));

                direction = lowercase(direction); // Convert to lowercase

                // Store the connection
                loc.addConnection(direction, destLocation);
                cout << "Loading " << locationName << " direction: " << direction << " -> " << destLocation << '\n';
            }

            // Add the location to the game
            gameWorld[loc.name] = loc;
        }
        else if (line.find("Entities") != string::npos) {
			string entityNames = line.substr(line.find(":") + 2);
			vector<string> entities;
            stringstream ss(entityNames);
			string entityName;

            while (getline(ss, entityName, ',')) {
				entities.push_back(entityName);
            }

            for (const string& entityName : entities) {
				getline(inputFile, line);
				string entityDesc = line.substr(line.find(":") + 2);
				locationEntities[locationName].push_back(Entity(entityName, entityDesc));
            }
        }
    }

    inputFile.close();

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
        cout << "\nCommands:\n- go <direction>\n- look at <entity>\n- open inventory\n- quit\nEnter command: ";
        getline(cin, input);

        if (input == "quit") {
			cout << "Weak" << endl;
            break;
        }
        // Pass input to command manager
        commandManager.execute(input, player, gameWorld, locationEntities, playerInventory);

    }

    return 0;
}