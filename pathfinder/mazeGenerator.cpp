#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <utility>
#include <algorithm>
#include <iomanip>

using namespace std;

void display(int height, int width, std::vector<std::vector<int>> grid) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == 0) 
                std::cout << "88"; 
            else 
                cout << "  ";
        }
        std::cout << "\n";
    }
}

class Maze {
private:
    int width, height;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<bool>> visited;
    //UP, RIGHT, DOWN, LEFT
    const int dx[4] = { 0, 1, 0, -1 };
    const int dy[4] = { -1, 0, 1, 0 };
public:
    Maze(int w, int h) : width(w), height(h) {
        // Инициализация сетки стенами (0)
        grid.resize(height, std::vector<int>(width, 0));
        visited.resize(height, std::vector<bool>(width, false));
    }

    // Проверка валидности координат
    bool isValid(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    // Генерация лабиринта с помощью Recursive Backtracker
    void generateMaze(int startX = 1, int startY = 1) {
        // Убедимся, что начальная точка валидна и нечетна
        startX = std::max(1, startX);
        startY = std::max(1, startY);
        if (startX % 2 == 0) startX--;
        if (startY % 2 == 0) startY--;

        std::stack<std::pair<int, int>> stack;
        grid[startY][startX] = 1; // Начальная точка - путь
        stack.push({ startX, startY });

        // Инициализация генератора случайных чисел
        std::random_device rd;
        std::mt19937 gen(rd());

        while (!stack.empty()) {
            int x = stack.top().first;
            int y = stack.top().second;

            // Получаем все возможные направления
            std::vector<int> directions = { 0, 1, 2, 3 };
            std::shuffle(directions.begin(), directions.end(), gen);

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

            if (!found) {
                stack.pop();
            }
        }

        // Создаем вход и выход
        grid[1][0] = 1; // Вход
        grid[height - 2][width - 1] = 1; // Выход
        display(height, width, grid);
    }
};



    int main() {
        std::cout << "=== Maze Generator and Solver ===\n";
        // Размеры лабиринта (должны быть нечетными для правильной работы)
        int width = 21;
        int height = 21;

        Maze maze(width, height);

        std::cout << "\nGenerating maze...\n";
        maze.generateMaze();

        std::cout << "\nGenerated maze:\n";
        return 0;
    }