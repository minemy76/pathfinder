#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include "bfsGraphDrawer.h"

// Create a simple graph showing just the path
void GraphDrawer::drawGraph(const std::vector<std::pair<int, int>>& path) {
    std::ofstream graph("bfsGraph.gv");
    if (!graph.is_open()) {
        throw std::runtime_error("Failed to create BFS graph visualization file");
    }

    // Set up the graph basics
    graph << "digraph bfs_path {\n"
        << "rankdir = LR;\n"  // Left to right looks more natural for paths
        << "node [shape = circle, style = filled];\n\n";

    // Create nodes for each point in our path
    for (size_t i = 0; i < path.size(); ++i) {
        std::string color = (i == 0) ? "green" :  // Start is green
            (i == path.size() - 1) ? "red" : "lightblue";  // End is red, others blue

        graph << "node_" << i << " [label=\"(" << path[i].first << "," << path[i].second
            << ")\", fillcolor=\"" << color << "\"];\n";
    }

    graph << "\n";

    // Connect the dots in order
    for (size_t i = 0; i < path.size() - 1; ++i) {
        graph << "node_" << i << " -> node_" << i + 1 << " [color=\"blue\", penwidth=2.0];\n";
    }

    graph << "}";
}

// Create a detailed visualization that shows the maze AND the path
void GraphDrawer::drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
    const std::vector<std::vector<int>>& mazeGrid) {

    std::ofstream graph("bfsGraph.gv");
    if (!graph.is_open()) {
        throw std::runtime_error("Cannot create BFS maze visualization file");
    }

    // Top-down layout works better for mazes
    graph << "digraph bfs_maze_path {\n"
        << "rankdir = TB;\n"  // Top to bottom for natural maze view
        << "node [shape = box, style = filled];\n"
        << "graph [nodesep = 0.5, ranksep = 0.5];\n\n";

    int height = mazeGrid.size();
    if (height == 0) throw std::invalid_argument("Empty maze grid provided");
    int width = mazeGrid[0].size();

    // Organize nodes by row to keep the maze structure
    for (int y = 0; y < height; y++) {
        graph << "{ rank = same; ";  // Keep each row aligned
        for (int x = 0; x < width; x++) {
            std::string color = "white";
            if (mazeGrid[y][x] == 0) {
                color = "black";  // Walls are black
            }
            else {
                // Color code the path points
                for (size_t i = 0; i < path.size(); i++) {
                    if (path[i].first == x && path[i].second == y) {
                        if (i == 0) color = "green";        // Start
                        else if (i == path.size() - 1) color = "red";  // End
                        else color = "gold";               // Path points
                        break;
                    }
                }
            }

            // Make sure text is readable against background
            std::string fontcolor = (color == "black") ? "white" : "black";
            graph << "node_" << x << "_" << y << " [label=\"(" << x << "," << y
                << ")\", fillcolor=\"" << color << "\", fontcolor=\"" << fontcolor << "\"]; ";
        }
        graph << "}\n";
    }

    graph << "\n";

    // Draw the actual solution path
    if (!path.empty()) {
        graph << "edge [color=\"darkgreen\", penwidth=3.0, dir=\"forward\"];\n";
        for (size_t i = 0; i < path.size() - 1; i++) {
            graph << "node_" << path[i].first << "_" << path[i].second
                << " -> node_" << path[i + 1].first << "_" << path[i + 1].second << ";\n";
        }
    }

    // Show all possible moves as light gray background
    graph << "edge [color=\"lightgray\", penwidth=0.5, dir=\"none\"];\n";

    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    // Connect adjacent walkable cells to show maze structure
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (mazeGrid[y][x] == 1) {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    // Only connect to valid walkable neighbors
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && mazeGrid[ny][nx] == 1) {
                        graph << "node_" << x << "_" << y << " -> node_" << nx << "_" << ny << ";\n";
                    }
                }
            }
        }
    }

    graph << "}";
}