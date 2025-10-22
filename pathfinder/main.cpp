#include "bfs.h"
#include "dijkstra.h"
#include <iostream>
#include <exception>

// Run both algorithms and compare the results
int main() {
    try {
        demo::runBFSDemo();
        std::cout << "\n" << std::string(50, '=') << "\n";
        demo::runDijkstraDemo();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown application error occurred" << std::endl;
        return 1;
    }
}