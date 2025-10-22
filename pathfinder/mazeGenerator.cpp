#include "maze.h"
#include "bfs.h"
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include <utility>
#include "bfsGraphDrawer.h"
#include "dijkstraGraphDrawer.h"
#include "dijkstra.h"

Maze::Maze(int w, int h) : width(w), height(h) {
    // Start with everything as walls
    grid.resize(height, std::vector<int>(width, 0));
    visited.resize(height, std::vector<bool>(width, false));
}

bool Maze::isValid(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Maze::generateMaze(int startX, int startY) {
    // Make sure start is inside maze and on odd coordinates
    startX = std::max(1, startX);
    startY = std::max(1, startY);
    if (startX % 2 == 0) startX--;
    if (startY % 2 == 0) startY--;

    std::stack<std::pair<int, int>> stack;
    grid[startY][startX] = 1;
    stack.push({ startX, startY });

    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;

        // Try directions in random order
        std::vector<int> directions = { 0, 1, 2, 3 };
        std::shuffle(directions.begin(), directions.end(), gen);

        bool found = false;
        for (int dir : directions) {
            int nx = x + dx[dir] * 2;
            int ny = y + dy[dir] * 2;

            // If the cell two steps away is a wall, we can carve a path
            if (isValid(nx, ny) && grid[ny][nx] == 0) {
                // Remove wall between current cell and new cell
                grid[y + dy[dir]][x + dx[dir]] = 1;
                grid[ny][nx] = 1;

                stack.push({ nx, ny });
                found = true;
                break;
            }
        }

        // Backtrack if no new paths found
        if (!found) {
            stack.pop();
        }
    }

    // Create entrance and exit
    grid[1][0] = 1;
    grid[height - 2][width - 1] = 1;
}

void Maze::display() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0) {
                std::cout << "88";  // Wall
            }
            else {
                std::cout << "  ";  // Path
            }
        }
        std::cout << "\n";
    }
}

void Maze::resetVisited() {
    for (auto& row : visited) {
        std::fill(row.begin(), row.end(), false);
    }
}

void demo::runBFSDemo() {
    // Create and solve a maze with BFS
    std::cout << "\nBFS\n\n";
    Maze maze(21, 21);
    maze.generateMaze();
    maze.display();
    std::cout << "\n";
    auto start = maze.getStart();
    auto end = maze.getEnd();

    auto path = BFSSolver::solveBFS(maze, start.first, start.second, end.first, end.second);
    GraphDrawer::drawGraphWithMaze(path, maze.getGrid());
    // Show results
    if (!path.empty()) { BFSSolver::displaySolution(maze, path); BFSSolver::analyzeSolution(path); }
    else std::cout << "No path found!\n";
}

void demo::runDijkstraDemo() {
    // Create and solve the same maze with Dijkstra
    std::cout << "\nDijkstra\n\n";
    Maze maze(21, 21);
    maze.generateMaze();
    maze.display();
    std::cout << "\n";
    auto start = maze.getStart();
    auto end = maze.getEnd();
    auto path = DijkstraSolver::solveDijkstra(maze, start.first, start.second, end.first, end.second);

    // Show results
    DijkstraGraphDrawer::drawGraphWithMaze(path, maze.getGrid());
    if (!path.empty()) {
        DijkstraSolver::displaySolution(maze, path);
        DijkstraSolver::analyzeSolution(path);
    }
    else std::cout << "Dijkstra: No path found!\n";
}