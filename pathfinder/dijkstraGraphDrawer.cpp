#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>
#include "dijkstraGraphDrawer.h"

// Create a Graphviz diagram showing Dijkstra's solution
void DijkstraGraphDrawer::drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
    const std::vector<std::vector<int>>& mazeGrid) {

    std::ofstream graph("dijkstraGraph.gv");
    if (!graph.is_open()) {
        throw std::runtime_error("Failed to create Dijkstra graph visualization file");
    }

    // Set up the graph style
    graph << "digraph dijkstra_maze_solution {\n"
        << "rankdir = TB;\n"  // Vertical layout works better for mazes
        << "node [shape = box, style = filled];\n"
        << "graph [nodesep = 0.5, ranksep = 0.5];\n\n";

    int height = mazeGrid.size();
    if (height == 0) throw std::invalid_argument("Empty maze grid provided");
    int width = mazeGrid[0].size();

    // Create each row of the maze
    for (int y = 0; y < height; y++) {
        graph << "{ rank = same; ";  // Keep row cells aligned
        for (int x = 0; x < width; x++) {
            std::string nodeName = "node_" + std::to_string(x) + "_" + std::to_string(y);
            std::string label = "(" + std::to_string(x) + "," + std::to_string(y) + ")";

            std::string color = "white";
            if (mazeGrid[y][x] == 0) {
                color = "black";  // Walls
            }
            else {
                // Color nodes based on their role in the path
                for (size_t i = 0; i < path.size(); i++) {
                    if (path[i].first == x && path[i].second == y) {
                        if (i == 0) color = "green";        // Start
                        else if (i == path.size() - 1) color = "red";  // End
                        else color = "orange";             // Middle of path
                        break;
                    }
                }
            }

            // Make text readable against the background color
            std::string fontcolor = (color == "black") ? "white" : "black";
            graph << nodeName << " [label=\"" << label << "\", fillcolor=\"" << color
                << "\", fontcolor=\"" << fontcolor << "\"]; ";
        }
        graph << "}\n";
    }

    graph << "\n";

    // Draw the solution path with thick orange lines
    if (!path.empty()) {
        graph << "edge [color=\"orange\", penwidth=3.0, dir=\"forward\"];\n";
        for (size_t i = 0; i < path.size() - 1; i++) {
            graph << "node_" << path[i].first << "_" << path[i].second
                << " -> node_" << path[i + 1].first << "_" << path[i + 1].second << ";\n";
        }
    }

    // Show maze connectivity with subtle gray lines
    graph << "edge [color=\"lightgray\", penwidth=0.5, dir=\"none\"];\n";

    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    // Connect adjacent walkable cells to show the maze structure
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (mazeGrid[y][x] == 1) {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    // Only connect to valid, walkable neighbors
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && mazeGrid[ny][nx] == 1) {
                        graph << "node_" << x << "_" << y << " -> node_" << nx << "_" << ny << ";\n";
                    }
                }
            }
        }
    }

    graph << "}";
}