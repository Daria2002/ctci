#include <iostream>
#include <algorithm>
#include <vector>

class Result {
    public:
        Result() = default;
        Result(bool f, int c, int r) : found(f), col(c), row(r) {}
        bool found; // true if element found, otherwise false
        int col, row;
        void set_result(bool f, int c, int r) {
            found = f;
            col = c;
            row = r;
        }
};

Result find_el_naive(std::vector<std::vector<int>> matrix, int num) {
    int row = 0; 
    int col = matrix[0].size() - 1;
    // iterate from top left element to the bottom right element
    while (row < matrix.size() && col >= 0) {
        if(matrix[row][col] == num) {
            return Result(true, row, col); // num found
        } else if(matrix[row][col] > num) {
            col--;
        } else {
            row++;
        }
    }
    return Result(false, -1, -1); // num not found
}

class Coordinate {
    public:
        int row, col;
        bool initialized = false;
        Coordinate(int r, int c) : row(r), col(c) {
            initialized = true;
        }
        Coordinate() = default;
        bool in_bounds(std::vector<std::vector<int>> matrix) {
            return row >= 0 && col >= 0 && row < matrix.size() && col < matrix[0].size();
        }
        bool is_before(Coordinate p) {
            return row <= p.row && col <= p.col;
        }
        void set_to_average(Coordinate min, Coordinate max) {
            row = (min.row + max.row) / 2;
            col = (min.col + max.col) / 2;
        }
};

Coordinate find_el_bin_search(std::vector<std::vector<int>>, Coordinate, Coordinate, int);

Coordinate partition_and_search(std::vector<std::vector<int>> matrix, Coordinate origin, 
                                Coordinate dest, Coordinate pivot, int num) {
    Coordinate lower_left_origin(pivot.row, origin.col);  // define start coordinate of lower left rectangle
    Coordinate lower_left_dest(dest.row, pivot.col - 1); // define end coordinate of lower left rectangle
    Coordinate upper_right_origin(origin.row, pivot.col); // define start coordinate of upper right rectangle
    Coordinate upper_right_dest(pivot.row - 1, dest.col); // define end coordinate of upper right rectangle
    Coordinate lower_left = find_el_bin_search(matrix, lower_left_origin, lower_left_dest, num);
    if(!lower_left.initialized) {
        return find_el_bin_search(matrix, upper_right_origin, upper_right_dest, num);
    }
    return lower_left;
}

Coordinate find_el_bin_search(std::vector<std::vector<int>> matrix, Coordinate origin, Coordinate dest, int num) {
    if(!origin.in_bounds(matrix) || !dest.in_bounds(matrix)) return Coordinate(); // if origin or dest out of bounds return non-ini coordinate
    if(matrix[origin.row][origin.col] == num) return origin;
    else if(!origin.is_before(dest)) return Coordinate(); // if origin > dest return non-ini coordinate
    Coordinate start(origin.row, origin.col);
    int delta_row = dest.row - origin.row;
    int delta_col = dest.col - origin.col;
    int min_delta = std::min(delta_row, delta_col);
    Coordinate end(origin.row + min_delta, origin.col + min_delta);

    Coordinate tmp(0, 0);

    // binary search, find the first element > 0
    while (start.is_before(end))
    {
        tmp.set_to_average(start, end);
        if(num > matrix[tmp.row][tmp.col]) {
            start.row = tmp.row + 1;
            start.col = tmp.col + 1;
        } else {
            end.row = tmp.row - 1;
            end.col = tmp.col - 1;
        }   
    }
    // search bottom left and top right
    return partition_and_search(matrix, origin, dest, start, num);
}

Coordinate find_el_bin_search(std::vector<std::vector<int>> matrix, int num) {
    Coordinate origin(0, 0);
    Coordinate dest(matrix.size() - 1, matrix[0].size() - 1);
    return find_el_bin_search(matrix, origin, dest, num);
}

std::vector<std::vector<int>> generate_matrix() {
    std::vector<int> first_row = {15, 20, 40, 85};
    std::vector<int> second_row = {20, 35, 80, 95};
    std::vector<int> third_row = {30, 55, 95, 105};
    std::vector<int> forth_row = {40, 80, 100, 120};
    std::vector<std::vector<int>> matrix = {first_row, second_row, third_row, forth_row};
    return matrix;
}

void print_matrix(std::vector<std::vector<int>> matrix) {
    std::cout << "_______________\n";
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "_______________\n";
}

/**
 * Given an M x N matrix in which each row and each column is sorted in
 * ascending order, write a method to find an element. 
 */
int main() {
    std::vector<std::vector<int>> matrix = generate_matrix();
    print_matrix(matrix);
    int num = 55;
    std::cout << "Enter 1 to find a number in a matrix using naive solution or"
                 "any other number to find a number using binary search.\n";
    int method = 2;
    // std:: cin >> method;
    Result result;
    switch (method) {
    case 1:
        result = find_el_naive(matrix, num);
        break;
    default:
        Coordinate result_coordinate = find_el_bin_search(matrix, num);
        result.set_result(true, result_coordinate.col, result_coordinate.row);
        break;
    }
    std::cout << "Number " << num << " is " << (result.found ? "" : "not ") << "found.\n" << '\n';
    if(result.found) {
        std::cout << "Row = " << result.row << ", col = " << result.col << ".\n";
    }
}
