#ifndef GRAPHDRAWER_H
#define GRAPHDRAWER_H

#include <vector>
#include <utility>
#include <string>

class GraphDrawer {
public:
    static void drawGraph(const std::vector<std::pair<int, int>>& path);
    static void drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
        const std::vector<std::vector<int>>& mazeGrid);
};

#endif