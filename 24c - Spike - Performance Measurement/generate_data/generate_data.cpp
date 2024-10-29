#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>

// Function to generate JSON data resembling social media posts
void generateJSONData(const std::string& filename, int numPosts) {
    std::ofstream jsonFile(filename);
    jsonFile << "{ \"posts\": [";
    for (int i = 0; i < numPosts; ++i) {
        jsonFile << "{ \"id\": " << i << ", \"text\": \"Sample post text #" << i << "\" }";
        if (i < numPosts - 1) jsonFile << ",";
    }
    jsonFile << "] }";
    jsonFile.close();
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Number of posts to generate
    int numPosts = 1000; // Set this to a larger number for scalability tests

    // Start timing
    Uint32 startTicks = SDL_GetTicks();

    // Generate data
    generateJSONData("generated_data.json", numPosts);

    // End timing
    Uint32 endTicks = SDL_GetTicks();
    std::cout << "Data generation took " << (endTicks - startTicks) << " milliseconds." << std::endl;

    // Optional: Create an SDL window for progress visualization (commented out)
    /*
    SDL_Window* window = SDL_CreateWindow("Data Generation Progress",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);

    if (window) {
        // Display a message or visual progress (optional implementation)
        SDL_Delay(3000); // Just to keep the window open for 3 seconds
        SDL_DestroyWindow(window);
    } else {
        std::cerr << "Could not create SDL window: " << SDL_GetError() << std::endl;
    }
    */

    SDL_Quit();
    return 0;
}
