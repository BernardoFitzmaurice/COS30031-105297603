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
    map<string, string> connections; // direction -> location name
};

string lowercase(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
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
            }

            // Add the location to the game
            gameWorld[loc.name] = loc;
        }
    }

    inputFile.close();

    // 'Go' & 'Quit' commands
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
            cout << dir << " ";
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
        else if (input.substr(0, 3) == "go ")
        {
            string direction = input.substr(3);
            direction = lowercase(direction); // convert to lowercase
            if (loc.connections.find(direction) != loc.connections.end())
            {
                currentLocation = loc.connections[direction]; // Move to new location
            }
            else
            {
                cout << "You crashed to a wall like a frog.\n" << endl;
            }
        }
        else
        {
            cout << "Invalid command.\n " << endl;
        }
    }

    return 0;
}
