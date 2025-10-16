#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "maze.h"
#include <vector>
#include <utility>

class DijkstraSolver {
public:
    static std::vector<std::pair<int, int>> solveDijkstra(Maze& maze,
        int startX, int startY, int endX, int endY);

    static void displaySolution(const Maze& maze,
        const std::vector<std::pair<int, int>>& path);

    static void analyzeSolution(const std::vector<std::pair<int, int>>& path);
};

#endif