#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include "bfsGraphDrawer.h"

void GraphDrawer::drawGraph(const std::vector<std::pair<int, int>>& path) {
    std::ofstream graph("bfsGraph.gv");
    if (!graph.is_open()) return;

    graph << "digraph path {\n"
        << "rankdir = LR;\n"
        << "node [shape = circle, style = filled];\n\n";

    // Add all nodes from path
    for (size_t i = 0; i < path.size(); ++i) {
        std::string color = (i == 0) ? "green" :
            (i == path.size() - 1) ? "red" : "lightblue";

        graph << "node_" << i << " [label=\"(" << path[i].first << "," << path[i].second
            << ")\", fillcolor=\"" << color << "\"];\n";
    }

    graph << "\n";

    // Add connections between nodes
    for (size_t i = 0; i < path.size() - 1; ++i) {
        graph << "node_" << i << " -> node_" << i + 1 << " [color=\"blue\", penwidth=2.0];\n";
    }

    graph << "}";
}

void GraphDrawer::drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
    const std::vector<std::vector<int>>& mazeGrid) {
    std::ofstream graph("bfsGraph.gv");
    if (!graph.is_open()) return;

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
            std::string color = "white";
            if (mazeGrid[y][x] == 0) color = "black";
            else {
                // Check if cell is in path
                for (size_t i = 0; i < path.size(); i++) {
                    if (path[i].first == x && path[i].second == y) {
                        if (i == 0) color = "green";
                        else if (i == path.size() - 1) color = "red";
                        else color = "gold";
                        break;
                    }
                }
            }

            std::string fontcolor = (color == "black") ? "white" : "black";
            graph << "node_" << x << "_" << y << " [label=\"(" << x << "," << y
                << ")\", fillcolor=\"" << color << "\", fontcolor=\"" << fontcolor << "\"]; ";
        }
        graph << "}\n";
    }

    graph << "\n";

    // Add path connections
    if (!path.empty()) {
        graph << "edge [color=\"darkgreen\", penwidth=3.0, dir=\"forward\"];\n";
        for (size_t i = 0; i < path.size() - 1; i++) {
            graph << "node_" << path[i].first << "_" << path[i].second
                << " -> node_" << path[i + 1].first << "_" << path[i + 1].second << ";\n";
        }
    }

    // Add maze structure
    graph << "edge [color=\"lightgray\", penwidth=0.5, dir=\"none\"];\n";

    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (mazeGrid[y][x] == 1) {
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height && mazeGrid[ny][nx] == 1) {
                        graph << "node_" << x << "_" << y << " -> node_" << nx << "_" << ny << ";\n";
                    }
                }
            }
        }
    }

    graph << "}";
}