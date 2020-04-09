#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "MatrixHelper.h"

void rotate_matrix(std::vector<std::vector<int>>&);
bool check_dimensions(const std::vector<std::vector<int>>&);

/**
 * Given an image represented by an NxN matrix, where each pixel in the image 
 * is represented by an integer, write a method to rotate the image by 90 degrees.
 * Can you do this in place?
 * 
 * @param fileName file where user wrote matrix NxN. After executing program matrix 
 * will be modified. New matrix is input matrix rotated by 90 degrees.
 * Input matrix should separate elements with ,
 */
int main(int argc, char** argv) {
    MatrixFile::MatrixManager mm;
    if(argc != 2) {
        std::cout << "Please provide one parameter in program. Parameter should be file path." << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> matrix;
    const std::string file_name = argv[1];
    if(mm.initalize_matrix(file_name, matrix) == false) {
        std::cout << "Matrix is not initailized." << std::endl;
        return 0;
    }
    
    if(check_dimensions(matrix) == false) {
        std::cout << "Matrix dimensions should be NxN." << std::endl;
        return 0;
    }

    rotate_matrix(matrix);

    if(mm.write_matrix_to_file(file_name, matrix) == false) {
         std::cout << "Error while writing matrix to file." << std::endl;
    }
    std::cout << "Rotated matrix is written to " << file_name << std::endl;
}

bool check_dimensions(const std::vector<std::vector<int>>& matrix) {
    int row_size = matrix.size();
    for(const auto& column : matrix) {
        if(column.size() != row_size) {
            return false;
        }
    }
    return true;
}

// matrix[y][x]
void rotate_matrix(std::vector<std::vector<int>>& matrix) {
    const int n = matrix.size();
    for(int layer = 0; layer < n/2; layer++) {

        int first = layer;
        int last = n - 1 - layer;
        int top;

        for(int i = first; i < last; i++) {
            int offset = i - first;
            top = matrix[i][first]; // save top 
            matrix[i][first] = matrix[first][last - offset]; // right -> top
            matrix[first][last - offset] = matrix[last - offset][last]; // down -> right
            matrix[last - offset][last] = matrix[last][i]; // left -> down
            matrix[last][i] = top; // top -> left
        }
    }
}