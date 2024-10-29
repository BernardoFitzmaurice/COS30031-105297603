#include <SDL.h>
#include <iostream>
#include <fstream>

// Function to be tested
void functionToTest() {
    // Simulate work, e.g., a loop or computation
    for (int i = 0; i < 1000000; ++i) {}
}

int main(int argc, char* argv[]) {
    if (SDL_Init(0) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Open CSV file for writing
    std::ofstream file("performance_results.csv");
    file << "Run,ExecutionTime(s)\n";  // Header for CSV

    // Run the test multiple times and log results
    for (int run = 1; run <= 10; ++run) {
        Uint64 start = SDL_GetPerformanceCounter();

        functionToTest();  // Run the function

        Uint64 end = SDL_GetPerformanceCounter();
        double elapsed = (end - start) / static_cast<double>(SDL_GetPerformanceFrequency());

        std::cout << "Run " << run << " - Execution Time: " << elapsed << " seconds\n";

        // Write to CSV
        file << run << "," << elapsed << "\n";
    }

    file.close();
    SDL_Quit();
    return 0;
}
