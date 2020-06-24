#include <iostream>
#include <vector>
#include <ctime>
#include <random>

class Point {
    public:
        Point() = default;
        Point(int _row, int _col) : row(_row), col(_col) {}
        int row, col;
};

bool find_a_path(std::vector<Point>& points, int r, int c, std::vector<std::vector<bool>> maze) {
    if(r < 0 || c < 0 || !maze[r][c]) {
        return false;
    }
    bool is_at_start = (r == 0) && (c == 0);
    if(is_at_start || find_a_path(points, r - 1, c, maze) || find_a_path(points, r, c - 1, maze)) {
        points.push_back(Point(r, c));
        return true;
    }
    return false;
}

std::vector<Point> find_a_path(std::vector<std::vector<bool>> maze) {
    std::vector<Point> points;
    if(maze.empty() || maze.size() == 0) return points;
    std::cout << "Path is " << (find_a_path(points, maze.size() - 1, maze[0].size() - 1, maze) ? "" : "not ") << "found.\n";
    return points;
}

bool find_a_path_dp(std::vector<Point>& points, int r, int c, std::vector<std::vector<bool>> maze) {
    
}

std::vector<Point> find_a_path_dp(std::vector<std::vector<bool>> maze) {
    std::vector<Point> points;
    if(maze.empty() || maze.size() == 0) return points;
    std::cout << "Path is " << (find_a_path_dp(points, maze.size() - 1, maze[0].size() - 1, maze) ? "" : "not ") << "found.\n";
    return points;
}

std::vector<std::vector<bool>> generate_maze(int row, int col) {
    std::vector<std::vector<bool>> maze;
    srand(time(0));
    std::cout << "Generated maze:\n  ";
    for(int i = 0; i < col; i++) {
        std::cout << "__";
    }
    for(int i = 0; i < row; i++) {
        std::cout << "\n| ";
        std::vector<bool> r;
        for(int j = 0; j < col; j++) {
            bool off_limits = rand() % 2;
            if(off_limits) off_limits = rand() % 2; // reduce off_limits
            // special case for start and stop position
            if((i == j && i == 0) || (i == row - 1 && j == col - 1)) {
                off_limits = false;
            }
            r.push_back(off_limits ? false : true);
            std::cout << (off_limits ? "X " : "  ");
        }
        maze.push_back(r);
        std::cout << "|";
    }
    std::cout << "\n  ";
    for(int i = 0; i < col; i++) {
        std::cout << "__";
    }
    std::cout << "\n";
    return maze;
}

bool is_path(std::vector<Point> points, int row, int col) {
    for(Point p : points) {
        if(p.row == row && p.col == col) return true;
    }
    return false;
}

void show_path(std::vector<Point> points, int row, int col, const std::vector<std::vector<bool>> maze) {
    std::cout << "  ";
    for(int i = 0; i < col; i++) {
        std::cout << "__";
    }
    for(int i = 0; i < row; i++) {
        std::cout << "\n| ";
        std::vector<bool> r;
        for(int j = 0; j < col; j++) {
            if(!maze[i][j]) {
                std::cout << "X ";
            } else if(is_path(points, i, j)) {
                std::cout << "P ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "|";
    }
    std::cout << "\n  ";
    for(int i = 0; i < col; i++) {
        std::cout << "__";
    }
    std::cout << "\n";
}

/**
 * Imagine a robot sitting on the upper left corner of grid with r rows and c columns.
 * The robot can only move in two directions, right and down, but certain cells are 
 * "off limits" such that the robot cannot step on them. Design an algorithm to find a 
 * path for the robot from top left to bottom right.
 */ 
int main() {
    std::cout << "===============\nRobot in a grid\n===============\n";
    constexpr int row = 4;
    constexpr int col = 5;
    std::vector<std::vector<bool>> maze = generate_maze(row, col);
    std::cout << "Enter 1 to solve problem using dynamic programming, otherwise it will be solved using brute force.\n";
    int method;
    std::cin >> method;
    std::vector<Point> points;
    if(method == 1) {
        points = find_a_path_dp(maze);
    } else {
        points = find_a_path(maze); // complexity O(2^(r+c)) because there are 2 options for every point
    }
    show_path(points, row, col, maze);
}
