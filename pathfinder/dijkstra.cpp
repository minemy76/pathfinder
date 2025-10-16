#include "dijkstra.h"
#include "maze.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>

std::vector<std::pair<int, int>> DijkstraSolver::solveDijkstra(Maze& maze,
    int startX, int startY, int endX, int endY) {

    maze.resetVisited();
    auto& visited = maze.getVisited();
    const auto& grid = maze.getGrid();

    int width = maze.getWidth();
    int height = maze.getHeight();

    // Directions: UP, RIGHT, DOWN, LEFT
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    // Distance matrix - stores shortest distance to each cell
    std::vector<std::vector<int>> distance(height, std::vector<int>(width, INT_MAX));
    std::vector<std::vector<std::pair<int, int>>> parent(
        height, std::vector<std::pair<int, int>>(width, std::make_pair(-1, -1)));

    // Priority queue: (distance, (x, y))
    typedef std::pair<int, std::pair<int, int>> Node;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    distance[startY][startX] = 0;
    pq.push(std::make_pair(0, std::make_pair(startX, startY)));

    while (!pq.empty()) {
        Node current = pq.top();
        int currentDist = current.first;
        int x = current.second.first;
        int y = current.second.second;
        pq.pop();

        if (visited[y][x]) continue;
        visited[y][x] = true;

        // If reached the exit
        if (x == endX && y == endY) {
            // Reconstruct path
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
            return path;
        }

        // Check all neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (maze.isValid(nx, ny) && grid[ny][nx] == 1) {
                int newDist = currentDist + 1; // All edges have weight 1

                if (newDist < distance[ny][nx]) {
                    distance[ny][nx] = newDist;
                    parent[ny][nx] = std::make_pair(x, y);
                    pq.push(std::make_pair(newDist, std::make_pair(nx, ny)));
                }
            }
        }
    }

    return std::vector<std::pair<int, int>>(); // No path found
}

void DijkstraSolver::displaySolution(const Maze& maze,
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
        displayGrid[path.front().second][path.front().first] = 'S';
        displayGrid[path.back().second][path.back().first] = 'E';
    }

    // Display
    std::cout << "\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << displayGrid[y][x] << ' ';
        }
        std::cout << "\n";
    }
}

void DijkstraSolver::analyzeSolution(const std::vector<std::pair<int, int>>& path) 
{if (path.empty()) std::cout << "Dijkstra: No solution found!\n";}