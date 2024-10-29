#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include "Location.h"
#include "Player.h"
#include "Inventory.h"

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
    }

    inputFile.close();

    Player player("Kitchen"); // Starting location, no lowercase conversion
    string input;

    while (true) {
        // Show location details
        Location& loc = gameWorld[player.currentLocation];
        cout << "\nThe location you're in is: " << loc.name << endl;
        cout << loc.description << endl;
        loc.displayConnections();

        // User input
        cout << "\nEnter: go <direction> or quit: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Weak" << endl;
            break;
        }
        else if (input.substr(0, 3) == "go ") {
            // Extract direction and move player
            string direction = lowercase(input.substr(3));
            player.move(direction, gameWorld);
        }
        else {
            cout << "Invalid command.\n " << endl;
        }
    }

    Inventory playerInventory;
    playerInventory.viewInventory(); // Show initial inventory
    int choice;

    do {
        std::cout << "\nEnter your choice:\n1: Pick up a coin\n2: Remove Frog\n3: View Inventory\n4: Exit Inventory\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            playerInventory.addCoin();
            break;
        case 2:
            playerInventory.removeFrog();
            break;
        case 3:
            playerInventory.viewInventory();
            break;
        case 4:
            std::cout << "Exiting Inventory.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}