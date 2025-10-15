#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include "graphDrawer.h"

void GraphDrawer::drawGraph(const std::vector<std::pair<int, int>>& path) {
    std::ofstream graph("graphDrawer.gv");
    if (graph.is_open()) {
        graph << "digraph path {\n"
            << "rankdir = LR;\n"
            << "node [shape = circle, style = filled];\n\n";

        // Add all nodes from path
        for (size_t i = 0; i < path.size(); ++i) {
            int x = path[i].first;
            int y = path[i].second;
            std::string nodeName = "node_" + std::to_string(i);
            std::string label = "(" + std::to_string(x) + "," + std::to_string(y) + ")";

            // Set node color
            std::string color;
            if (i == 0) color = "green";           // START
            else if (i == path.size() - 1) color = "red";  // END
            else color = "lightblue";              // Path node

            graph << nodeName << " [label=\"" << label << "\", fillcolor=\"" << color << "\"];\n";
        }

        graph << "\n";

        // Add connections between nodes
        for (size_t i = 0; i < path.size() - 1; ++i) {
            std::string fromNode = "node_" + std::to_string(i);
            std::string toNode = "node_" + std::to_string(i + 1);
            graph << fromNode << " -> " << toNode << " [color=\"blue\", penwidth=2.0];\n";
        }

        graph << "}";
        graph.close();
    }
}

void GraphDrawer::drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
    const std::vector<std::vector<int>>& mazeGrid) {
    std::ofstream graph("graphDrawer.gv");
    if (graph.is_open()) {
        graph << "digraph path {\n"
            << "rankdir = TB;\n"
            << "node [shape = box, style = filled];\n"
            << "graph [nodesep = 0.5, ranksep = 0.5];\n\n";

        int height = mazeGrid.size();
        int width = mazeGrid[0].size();

        // Create maze grid nodes
        for (int y = 0; y < height; y++) {
            graph << "{ rank = same; ";
            for (int x = 0; x < width; x++) {
                std::string nodeName = "node_" + std::to_string(x) + "_" + std::to_string(y);
                std::string label = "(" + std::to_string(x) + "," + std::to_string(y) + ")";

                // Determine node color
                std::string color;
                bool isInPath = false;

                // Check if cell is in path
                for (const auto& point : path) {
                    if (point.first == x && point.second == y) {
                        isInPath = true;
                        break;
                    }
                }

                if (mazeGrid[y][x] == 0) {
                    color = "black"; // Wall
                }
                else if (isInPath) {
                    // Find position in path for special styling
                    for (size_t i = 0; i < path.size(); i++) {
                        if (path[i].first == x && path[i].second == y) {
                            if (i == 0) color = "green";           // START
                            else if (i == path.size() - 1) color = "red";  // END
                            else color = "gold";                   // Path
                            break;
                        }
                    }
                }
                else {
                    color = "white"; // Free cell
                }

                std::string fontcolor = (color == "black") ? "white" : "black";
                graph << nodeName << " [label=\"" << label << "\", fillcolor=\"" << color
                    << "\", fontcolor=\"" << fontcolor << "\"]; ";
            }
            graph << "}\n";
        }

        graph << "\n";

        // Add path connections (BFS path)
        if (!path.empty()) {
            graph << "edge [color=\"darkgreen\", penwidth=3.0, dir=\"forward\"];\n";

            for (size_t i = 0; i < path.size() - 1; i++) {
                int x1 = path[i].first;
                int y1 = path[i].second;
                int x2 = path[i + 1].first;
                int y2 = path[i + 1].second;

                std::string fromNode = "node_" + std::to_string(x1) + "_" + std::to_string(y1);
                std::string toNode = "node_" + std::to_string(x2) + "_" + std::to_string(y2);

                graph << fromNode << " -> " << toNode << ";\n";
            }
        }

        // Add maze structure (light gray grid)
        graph << "edge [color=\"lightgray\", penwidth=0.5, dir=\"none\"];\n";

        const int dx[4] = { 0, 1, 0, -1 };
        const int dy[4] = { -1, 0, 1, 0 };

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (mazeGrid[y][x] == 1) { // Only for passable cells
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];

                        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                            mazeGrid[ny][nx] == 1) {
                            std::string fromNode = "node_" + std::to_string(x) + "_" + std::to_string(y);
                            std::string toNode = "node_" + std::to_string(nx) + "_" + std::to_string(ny);
                            graph << fromNode << " -> " << toNode << ";\n";
                        }
                    }
                }
            }
        }

        graph << "}";
        graph.close();
    }
}