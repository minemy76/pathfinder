#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>

class Maze {
private:
    int width, height;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    // Directions: UP, RIGHT, DOWN, LEFT
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

public:
    Maze(int w, int h);
    // Core functionality
    void generateMaze(int startX = 1, int startY = 1);
    // Utility methods
    bool isValid(int x, int y);
    void display() const;
    void resetVisited();
    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::pair<int, int> getStart() const { return { 0, 1 }; }
    std::pair<int, int> getEnd() const { return { width - 1, height - 2 }; }
    const std::vector<std::vector<int>>& getGrid() const { return grid; }
    std::vector<std::vector<bool>>& getVisited() { return visited; }
};

namespace demo {
    void runDemo();
}

namespace graph {
    void drawGraph();
}

#endif