#ifndef DIJKSTRAGRAPHDRAWER_H
#define DIJKSTRAGRAPHDRAWER_H

#include <vector>
#include <utility>

class DijkstraGraphDrawer {
public:
    static void drawGraphWithMaze(const std::vector<std::pair<int, int>>& path,
        const std::vector<std::vector<int>>& mazeGrid);
};

#endif