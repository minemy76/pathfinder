#include "bfs.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <stdexcept>

// BFS maze solver - explores level by level like ripples in water
std::vector<std::pair<int, int>> BFSSolver::solveBFS(Maze& maze,
    int startX, int startY, int endX, int endY) {

    // Make sure we're not starting in a wall or outside the maze
    if (!maze.isValid(startX, startY) || !maze.isValid(endX, endY)) {
        throw std::invalid_argument("BFS: Start or end coordinates are outside maze boundaries");
    }

    // Clear previous search data for a fresh run
    maze.resetVisited();
    auto& visited = maze.getVisited();
    const auto& grid = maze.getGrid();

    int width = maze.getWidth();
    int height = maze.getHeight();

    // Directions: up, right, down, left
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    std::queue<std::pair<int, int>> frontier;
    // Keep track of where we came from to rebuild the path later
    std::vector<std::vector<std::pair<int, int>>> parent(
        height, std::vector<std::pair<int, int>>(width, { -1, -1 }));

    frontier.push({ startX, startY });
    visited[startY][startX] = true;

    // Keep exploring until we run out of places to check
    while (!frontier.empty()) {
        int x = frontier.front().first;
        int y = frontier.front().second;
        frontier.pop();

        // Sweet! Found the exit
        if (x == endX && y == endY) {
            // Walk backwards from exit to start using parent pointers
            std::vector<std::pair<int, int>> path;
            int curX = x, curY = y;

            while (curX != -1 && curY != -1) {
                path.push_back({ curX, curY });
                int px = parent[curY][curX].first;
                int py = parent[curY][curX].second;
                curX = px;
                curY = py;
            }

            std::reverse(path.begin(), path.end());
            return path;
        }

        // Check all four directions from current position
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Only move if it's a valid empty cell we haven't seen before
            if (maze.isValid(nx, ny) && grid[ny][nx] == 1 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                parent[ny][nx] = { x, y };
                frontier.push({ nx, ny });
            }
        }
    }

    return {}; // Dead end - no path exists
}

// Show the maze solution as ASCII art
void BFSSolver::displaySolution(const Maze& maze,
    const std::vector<std::pair<int, int>>& path) {

    const auto& grid = maze.getGrid();
    int width = maze.getWidth();
    int height = maze.getHeight();

    // Create a character grid for display
    std::vector<std::vector<char>> displayGrid(height, std::vector<char>(width, ' '));

    // Convert 1s and 0s to visual characters
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            displayGrid[y][x] = (grid[y][x] == 0) ? '#' : ' ';
        }
    }

    // Mark the solution path
    for (const auto& point : path) {
        displayGrid[point.second][point.first] = '.';
    }

    // Make start and end stand out
    if (!path.empty()) {
        displayGrid[path.front().second][path.front().first] = 'S';
        displayGrid[path.back().second][path.back().first] = 'E';
    }

    // Print the final maze
    std::cout << "BFS Solution Path:\n";
    std::cout << "Legend: # = Wall, . = Path, S = Start, E = End\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << displayGrid[y][x] << ' ';
        }
        std::cout << "\n";
    }
}

// Give some stats about the solution we found
void BFSSolver::analyzeSolution(const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) {
        std::cout << "BFS Analysis: No viable path discovered\n";
        return;
    }

    std::cout << "\nBFS Path Analysis Report:\n";
    std::cout << "• Total path length: " << path.size() << " steps\n";
    std::cout << "• Path coordinates: " << path.size() << " waypoints\n";

    // How far apart start and end are (ignoring walls)
    int manhattanDist = abs(path.back().first - path.front().first) +
        abs(path.back().second - path.front().second);
    std::cout << "• Optimal distance: " << manhattanDist << " (Manhattan)\n";
    std::cout << "• Path efficiency ratio: " << std::fixed << std::setprecision(2)
        << (static_cast<double>(manhattanDist) / path.size()) << "\n";
}