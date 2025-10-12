#ifndef BFS_SOLVER_H
#define BFS_SOLVER_H

#include "maze.h"
#include <vector>
#include <utility>

class BFSSolver {
public:
    static std::vector<std::pair<int, int>> solveBFS(Maze& maze,
        int startX, int startY,
        int endX, int endY);

    static void displaySolution(const Maze& maze,
        const std::vector<std::pair<int, int>>& path);

    static void analyzeSolution(const std::vector<std::pair<int, int>>& path);
};

#endif