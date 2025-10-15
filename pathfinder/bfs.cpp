#include "bfs.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

std::vector<std::pair<int, int>> BFSSolver::solveBFS(Maze& maze,
    int startX, int startY, int endX, int endY) {
    // Reset visited array
    maze.resetVisited();
    auto& visited = maze.getVisited();
    const auto& grid = maze.getGrid();

    int width = maze.getWidth();
    int height = maze.getHeight();
    // Directions: UP, RIGHT, DOWN, LEFT
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<std::pair<int, int>>> parent(
        height, std::vector<std::pair<int, int>>(width, { -1, -1 }));

    q.push({ startX, startY });
    visited[startY][startX] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // If reached the exit
        if (x == endX && y == endY) {
            // Reconstruct path
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

        // Check all neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (maze.isValid(nx, ny) && grid[ny][nx] == 1 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                parent[ny][nx] = { x, y };
                q.push({ nx, ny });
            }
        }
    }

    return {}; // No path found
}

void BFSSolver::displaySolution(const Maze& maze,
    const std::vector<std::pair<int, int>>& path) {
    const auto& grid = maze.getGrid();
    int width = maze.getWidth();
    int height = maze.getHeight();

    // Create display grid
    std::vector<std::vector<char>> displayGrid(height, std::vector<char>(width, ' '));

    // Fill display grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            displayGrid[y][x] = (grid[y][x] == 0) ? '#' : ' ';
        }
    }

    // Mark path
    for (const auto& point : path) {
        displayGrid[point.second][point.first] = '.';
    }

    // Mark start and end
    if (!path.empty()) {
        displayGrid[path.front().second][path.front().first] = '-';
        displayGrid[path.back().second][path.back().first] = '+';
    }

    // Display
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << displayGrid[y][x] << ' ';
        }
        std::cout << "\n";
    }
}

void BFSSolver::analyzeSolution(const std::vector<std::pair<int, int>>& path) 
{if (path.empty()) {std::cout << "No solution found!\n";}}