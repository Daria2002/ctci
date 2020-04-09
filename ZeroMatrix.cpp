#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "MatrixHelper.hpp"

void zero_matrix(std::vector<std::vector<int>>&);

/**
 * Write an algorithm such that if an element in MxN matrix is 0,
 * its entire row and column are set to 0.
 */
int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Please provide one parameter in program. Parameter should be file path." << std::endl;
        return 0;
    }

    std::string file_name = argv[1];
    std::vector<std::vector<int>> matrix;
    MatrixFile::MatrixManager::initalize_matrix(file_name, matrix);
    zero_matrix(matrix);
    if(MatrixFile::MatrixManager::write_matrix_to_file(file_name, matrix)) {
        std::cout << "Modified matrix is saved to file." << std::endl;
    }
    return 0;
}

void nullify_row(const int& row, std::vector<std::vector<int>>& matrix, const int& number_of_columns) {
    for(int column = 0; column < number_of_columns; column++) {
        matrix[row][column] = 0;
    }
}

void nullify_column(const int& column, std::vector<std::vector<int>>& matrix, const int& number_of_rows) {
    for(int row = 0; row < number_of_rows; row++) {
        matrix[row][column] = 0;
    }
}

void zero_matrix(std::vector<std::vector<int>>& matrix) {
    bool firstRowIsZero = false;
    bool firstColumnIsZero = false;
    const int number_of_rows = matrix.size();
    const int number_of_columns = matrix[0].size(); 

    // check if first row has element equal to 0
    for(int column = 0; column < number_of_columns; column++) {
        if(matrix[0][column] == 0) {
            firstRowIsZero = true;
        }
    }

    // check if first column has element equal to 0
    for(int row = 0; row < number_of_rows; row++) {
        if(matrix[row][0] == 0) {
            firstColumnIsZero = true;
        }
    }

    // set elements in first column and first row to zero if there is an
    // element equal to 0 
    for(int row = 0; row < number_of_rows; row++) {
        for(int column = 0; column < number_of_columns; column++) {
            if(matrix[row][column] == 0) {
                matrix[0][column] = 0;
                matrix[row][column] = 0;
            }
        }
    }

    for(int row = 1; row < number_of_rows; row++) {
        if(matrix[row][0] != 0) continue;
        nullify_row(row, matrix, number_of_columns);
    }

    for(int column = 1; column < number_of_columns; column++) {
        if(matrix[0][column] != 0) continue;
        nullify_column(column, matrix, number_of_rows);
    }

    if(firstRowIsZero) {
        nullify_row(0, matrix, number_of_columns);
    }

    if(firstColumnIsZero) {
        nullify_column(0, matrix, number_of_rows);
    }
}