#include "dijkstra.h"
#include "maze.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <chrono>

// Dijkstra's algorithm - finds shortest path by always expanding the closest node
std::vector<std::pair<int, int>> DijkstraSolver::solveDijkstra(Maze& maze,
    int startX, int startY, int endX, int endY) {

    auto startTime = std::chrono::high_resolution_clock::now();

    // Basic sanity check first
    if (!maze.isValid(startX, startY) || !maze.isValid(endX, endY)) {
        throw std::invalid_argument("Dijkstra: Invalid start or end coordinates");
    }

    maze.resetVisited();
    auto& visited = maze.getVisited();
    const auto& grid = maze.getGrid();

    int width = maze.getWidth();
    int height = maze.getHeight();

    // Neighbor directions
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    // Track shortest distance to each cell
    std::vector<std::vector<int>> distance(height, std::vector<int>(width, INT_MAX));
    // Remember how we got to each cell
    std::vector<std::vector<std::pair<int, int>>> parent(
        height, std::vector<std::pair<int, int>>(width, std::make_pair(-1, -1)));

    // Min-heap to always get the closest unvisited node
    using Node = std::pair<int, std::pair<int, int>>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> minHeap;

    distance[startY][startX] = 0;
    minHeap.push(std::make_pair(0, std::make_pair(startX, startY)));

    // Keep going until we've checked everything reachable
    while (!minHeap.empty()) {
        Node current = minHeap.top();
        int currentDist = current.first;
        int x = current.second.first;
        int y = current.second.second;
        minHeap.pop();

        // Skip if we already found a better way here
        if (visited[y][x]) continue;
        visited[y][x] = true;

        // Found our destination!
        if (x == endX && y == endY) {
            // Reconstruct the path by following parent links
            std::vector<std::pair<int, int>> path;
            int curX = x, curY = y;

            while (curX != -1 && curY != -1) {
                path.push_back(std::make_pair(curX, curY));
                int px = parent[curY][curX].first;
                int py = parent[curY][curX].second;
                curX = px;
                curY = py;
            }

            std::reverse(path.begin(), path.end());

            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
            std::cout << "Dijkstra execution time: " << duration.count() << " microseconds\n";

            return path;
        }

        // Check all neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (maze.isValid(nx, ny) && grid[ny][nx] == 1) {
                int newDist = currentDist + 1; // All moves cost the same in this maze

                // If we found a shorter route, update everything
                if (newDist < distance[ny][nx]) {
                    distance[ny][nx] = newDist;
                    parent[ny][nx] = std::make_pair(x, y);
                    minHeap.push(std::make_pair(newDist, std::make_pair(nx, ny)));
                }
            }
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Dijkstra execution time: " << duration.count() << " microseconds\n";

    return std::vector<std::pair<int, int>>(); // No path found
}

// Display the maze with solution overlay
void DijkstraSolver::displaySolution(const Maze& maze,
    const std::vector<std::pair<int, int>>& path) {

    const auto& grid = maze.getGrid();
    int width = maze.getWidth();
    int height = maze.getHeight();

    // Build a character grid for display
    std::vector<std::vector<char>> displayGrid(height, std::vector<char>(width, ' '));

    // Fill in walls and paths
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            displayGrid[y][x] = (grid[y][x] == 0) ? '#' : ' ';
        }
    }

    // Mark the solution path
    for (const auto& point : path) {
        displayGrid[point.second][point.first] = '.';
    }

    // Highlight start and end
    if (!path.empty()) {
        displayGrid[path.front().second][path.front().first] = 'S';
        displayGrid[path.back().second][path.back().first] = 'E';
    }

    // Print the result
    std::cout << "Legend: # = Wall, . = Path, S = Start, E = End\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {std::cout << displayGrid[y][x] << ' ';}
        std::cout << "\n";
    }
}

// Analyze how good our solution is
void DijkstraSolver::analyzeSolution(const std::vector<std::pair<int, int>>& path) {
    if (path.empty()) {
        std::cout << "Dijkstra Analysis: No valid path discovered\n";
        return;
    }
    std::cout << "* Total path length: " << path.size() << " units\n";
}