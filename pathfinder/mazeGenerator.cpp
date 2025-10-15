#include "maze.h"
#include "bfs.h"
#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include <algorithm>
#include <utility>

Maze::Maze(int w, int h) : width(w), height(h) {
    // Initialize grid with walls (0)
    grid.resize(height, std::vector<int>(width, 0));
    visited.resize(height, std::vector<bool>(width, false));
}

bool Maze::isValid(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Maze::generateMaze(int startX, int startY) {
    // Ensure starting point is valid and odd
    startX = std::max(1, startX);
    startY = std::max(1, startY);
    if (startX % 2 == 0) startX--;
    if (startY % 2 == 0) startY--;

    std::stack<std::pair<int, int>> stack;
    grid[startY][startX] = 1; // Mark as path
    stack.push({ startX, startY });

    // Random numbers initialization
    std::random_device rd;
    std::mt19937 gen(rd());

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;

        // Get all possible directions and shuffle them
        std::vector<int> directions = { 0, 1, 2, 3 };
        std::shuffle(directions.begin(), directions.end(), gen);

        bool found = false;
        for (int dir : directions) {
            int nx = x + dx[dir] * 2;
            int ny = y + dy[dir] * 2;

            if (isValid(nx, ny) && grid[ny][nx] == 0) {
                // Carve passage between current and new cell
                grid[y + dy[dir]][x + dx[dir]] = 1;
                grid[ny][nx] = 1;

                stack.push({ nx, ny });
                found = true;
                break;
            }
        }

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
                std::cout << "88";
            }
            else {
                std::cout << "  ";
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

void demo::runDemo() {
    // Create and generate maze
    Maze maze(51, 51);
    maze.generateMaze();
    maze.display();
    // Solve with BFS
    std::cout << "\n";
    auto start = maze.getStart();
    auto end = maze.getEnd();

    auto path = BFSSolver::solveBFS(maze, start.first, start.second, end.first, end.second);
    graph::drawGraph();
    // Display results
    if (!path.empty()) {BFSSolver::displaySolution(maze, path);BFSSolver::analyzeSolution(path);}
    else std::cout << "No path found!\n";
}