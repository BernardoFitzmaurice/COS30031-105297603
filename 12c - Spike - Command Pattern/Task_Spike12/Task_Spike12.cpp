#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;

struct Location
{
    string name;
    string description;
    vector<string> entities; // List of entities in the location
    map<string, string> connections; // direction -> location name
};

string lowercase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// Process user command
void processCommand(const string& command, const string& argument, map<string, Location>& gameWorld, string& currentLocation)
{
	// Command to move in specified direction
    if (command == "go")
    {
        string direction = lowercase(argument);
        Location& loc = gameWorld[currentLocation];
        if (loc.connections.find(direction) != loc.connections.end())
        {
            currentLocation = loc.connections[direction];
        }
        else
        {
            cout << "You crashed to a wall like a frog.\n" << endl;
        }
    }
    // COmmand of Location details
    else if (command == "look")
    {
        Location& loc = gameWorld[currentLocation];
        cout << "\nYou are in: " << loc.name << endl;
        cout << loc.description << endl;
        cout << "Entities here: ";
        for (const auto& entity : loc.entities)
        {
            cout << entity << ", ";
        }
        cout << endl;
    }
	// Command of Entitie details
    else if (command == "look at")
    {
        Location& loc = gameWorld[currentLocation];
        if (find(loc.entities.begin(), loc.entities.end(), argument) != loc.entities.end())
        {
            cout << "You see a " << argument << " here.\n";
        }
        else
        {
            cout << "No such entity here.\n";
        }
    }
    // To show all commands
    else if (command == "help")
    {
        cout << "Available commands:\n";
        cout << "go <direction> - Move to a different location.\n";
        cout << "look - Show details of the current location.\n";
        cout << "look at <entity> - Show details of a specific entity.\n";
        cout << "help - List known commands.\n";
        cout << "inventory - Show what the player has.\n";
        cout << "alias <alias> <command> - Remap a command.\n";
        cout << "debug tree - Show debug information.\n";
    }
    // Additional commands like INVENTORY, ALIAS, and DEBUG TREE can be implemented similarly.
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <Adventure.txt>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) // Check if file is open
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    map<string, Location> gameWorld; // A graph to store the game locations

    string line, locationName, description, connections;

    while (getline(inputFile, line))
    {
        if (line.find("Location") != string::npos)
        {
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
            while (getline(ss, connection, ','))
            {
                size_t equalPos = connection.find("=");
                string direction = connection.substr(0, equalPos);
                string destLocation = connection.substr(equalPos + 1);

                // Remove extra spaces
                direction.erase(direction.find_last_not_of(' ') + 1);
                destLocation.erase(0, destLocation.find_first_not_of(' '));

                direction = lowercase(direction); // convert to lowercase

                // Store the connection
                loc.connections[direction] = destLocation;
                cout << "Loading " << locationName << " direction: " << direction << " -> " << destLocation << '\n';
            }

            // Read the entities
            getline(inputFile, line);
            if (line.find("Entities") != string::npos)
            {
                string entitiesStr = line.substr(line.find(":") + 2);
                stringstream entitiesStream(entitiesStr);
                string entity;
                while (getline(entitiesStream, entity, ','))
                {
                    entity.erase(entity.find_last_not_of(' ') + 1); // Remove trailing spaces
                    entity.erase(0, entity.find_first_not_of(' ')); // Remove leading spaces
                    loc.entities.push_back(entity);
                }
            }

            // Add the location to the game
            gameWorld[loc.name] = loc;
        }
    }

    inputFile.close();

    // 'Go' & 'Quit' commands
    map<string, string> aliases; // To store command aliases
    string currentLocation = "Kitchen"; // Starting location, no lowercase conversion
    string input;

    while (true)
    {
        // Show location details
        Location& loc = gameWorld[currentLocation];
        cout << "\nThe location you're in is: " << loc.name << endl;
        cout << loc.description << endl;

        // Display connections
        cout << "Possible connections: ";
        for (const auto& pair : loc.connections)
        {
            string dir = pair.first;
            cout << dir << "->" << pair.second << " ";
        }
        cout << endl;

        // User input
        cout << "\nEnter: go <direction> or quit: ";
        getline(cin, input);

        if (input == "quit")
        {
            cout << "Weak" << endl;
            break;
        }
        size_t spacePos = input.find(' ');
        string command = input.substr(0, spacePos);
        string argument = (spacePos != string::npos) ? input.substr(spacePos + 1) : "";

        if (aliases.find(command) != aliases.end())
        {
            command = aliases[command]; // Use alias if it exists
        }

        processCommand(command, argument, gameWorld, currentLocation);
    }

    return 0;
}
