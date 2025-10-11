#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <iomanip>

using namespace std;

void display(int height, int width, vector<vector<int>> grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0) 
                cout << "88"; 
            else 
                cout << "  ";
        }
        cout << "\n";
    }
}

class Maze {
private:
    int width, height;
     vector<vector<int>> grid;
     vector<vector<bool>> visited;
    //UP, RIGHT, DOWN, LEFT
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };
public:
    Maze(int w, int h) : width(w), height(h) {
        //Initialising
        grid.resize(height,vector<int>(width, 0));
        visited.resize(height,vector<bool>(width, false));
    }
    //Valid checker
    bool isValid(int x, int y) {return x >= 0 && x < width && y >= 0 && y < height;}
    // Maze generation with Recursive Backtracker
    void generateMaze(int startX = 1, int startY = 1) {
        startX = max(1, startX);
        startY = max(1, startY);
        if (startX % 2 == 0) startX--;
        if (startY % 2 == 0) startY--;
        stack<pair<int, int>> stack;
        grid[startY][startX] = 1; // Start point
        stack.push({ startX, startY });
        // Rand numbers init
         random_device rd;
         mt19937 gen(rd());

        while (!stack.empty()) {
            int x = stack.top().first;
            int y = stack.top().second;

            // Получаем все возможные направления
             vector<int> directions = { 0, 1, 2, 3 };
             shuffle(directions.begin(), directions.end(), gen);

            bool found = false;
            for (int dir : directions) {
                int nx = x + dx[dir] * 2;
                int ny = y + dy[dir] * 2;

                if (isValid(nx, ny) && grid[ny][nx] == 0) {
                    // Пробиваем стену между текущей и новой клеткой
                    grid[y + dy[dir]][x + dx[dir]] = 1;
                    grid[ny][nx] = 1;

                    stack.push({ nx, ny });
                    found = true;
                    break;
                }
            }
            if (!found)
                stack.pop();
        }
        grid[1][0] = 1;
        grid[height - 2][width - 1] = 1;
        display(height, width, grid);
    }
};

    int main() {
        int width = 51;
        int height = 51;
        Maze maze(width, height);
        maze.generateMaze();
        return 0;
    }