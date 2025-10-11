#include "header.h"
#include <vector>
#include <iostream>

void displayTheMaze::display(int height, int width, std::vector<std::vector<int>> grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0)
                std::cout << "88";
            else
                std::cout << "  ";
        }
        std::cout << "\n";
    }
}
