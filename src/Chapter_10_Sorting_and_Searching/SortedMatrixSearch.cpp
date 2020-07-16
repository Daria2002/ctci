#include <iostream>
#include <vector>

class Result {
    public:
        Result() = default;
        Result(bool f, int c, int r) : found(f), col(c), row(r) {}
        bool found; // true if element found, otherwise false
        int col, row;
};

Result find_el_bin_search(std::vector<std::vector<int>> matrix, int num) {
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

Result find_el_rectangle_search(std::vector<std::vector<int>> matrix, int num) {
    // TODO
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
    std::cout << "Enter 1 to find a number in a matrix using binary search or"
                 "any other number to find a number using rectangle search.\n";
    int method;
    std:: cin >> method;
    Result result;
    switch (method) {
    case 1:
        result = find_el_bin_search(matrix, num);
        break;
    default:
        result = find_el_rectangle_search(matrix, num);
        break;
    }
    std::cout << "Number " << num << " is " << (result.found ? "" : "not ") << "found.\n" << '\n';
    if(result.found) {
        std::cout << "Row = " << result.row << ", col = " << result.col << ".\n";
    }
}
