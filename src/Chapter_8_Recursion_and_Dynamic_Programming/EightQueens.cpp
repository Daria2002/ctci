#include <iostream>
#include <vector>
#include <string>
#include <cmath>

/**
 * This function checks column and diagonal. Returns true if place is available, otherwise false.
 */
bool check_position(std::vector<int> columns, const int row, const int column) {
    for(int row_tmp = 0; row_tmp < row; row_tmp++) {
        // check if a queen is already arranged in the same column
        if(columns[row_tmp] == column) return false;
        // check if a queen is alreay arranged in the same diagonal
        // queen is in the same diagonal if delta_row = delta_column
        int delta_row = row - row_tmp;
        int delta_col = std::abs(column - columns[row_tmp]);
        if(delta_row == delta_col) return false;
    }
    return true;
}

void arrange_queens(std::vector<int> columns, std::vector<std::vector<int>>& boards, const int row) {
    if(row == columns.size()) {
        boards.push_back(columns);
    } else {
        for(int column = 0; column < columns.size(); column++) {
            if(check_position(columns, row, column)) { 
                columns[row] = column;
                arrange_queens(columns, boards, row + 1);
            }
        }
    }
}

template<typename Char, typename Traits, typename Allocator>
std::basic_string<Char, Traits, Allocator> operator *
(const std::basic_string<Char, Traits, Allocator>& s, size_t n) {
    std::basic_string<Char, Traits, Allocator> tmp = "";
    for(int i = 0; i < n; i++) {
        tmp += s; 
    }
    return tmp;
}

template<typename Char, typename Traits, typename Allocator>
std::basic_string<Char, Traits, Allocator> operator *
(size_t n, const std::basic_string<Char, Traits, Allocator>& s) {
    return s * n;
}

void print_board(const std::vector<std::vector<int>>& boards) {
    const std::string empty_field = "[ ] ";
    const std::string queen_field = "[Q] ";
    int count = 0;
    for(std::vector<int> board : boards) {
        count++;
        for(int row = 0; row < board.size(); row++) {
            int col = board[row];
            std::cout << empty_field * col << queen_field << empty_field * (board.size() - col - 1) << '\n';
        }
        std::cout << "_______________________________\n";
    }
    std::cout << "Total number of ways to arrange eight queens = " << count << '\n';
}

/**
 * This function initialize elements in columns to -1
 * @param columns index represent row and value is a column index where queen is arranged
 * for that row
 * @param size number of rows/columns
 */
void initialize_board(std::vector<int>& columns, int size) {
    for(int row = 0; row < size; row++) {
        columns[row] = -1;
    }
}

/**
 * Write an algorithm to print all ways of arranging eight queens on an 8x8 chess board
 * so that none of them share the same row, column, or diagonal. In this case, "diagonal"
 * means all diagonals, not just the two that bisect the board
 */
int main() {
    // columns[0] contains column where queen is placed in row 0
    // columns[1] contains column where queen is placed in row 1
    constexpr int size = 8;
    std::vector<int> columns(size); 
    std::vector<std::vector<int>> boards;
    initialize_board(columns, size);
    arrange_queens(columns, boards, 0);
    std::cout << "All possible ways of arranging eight queens on an 8x8 chess board:\n";
    print_board(boards);
}
