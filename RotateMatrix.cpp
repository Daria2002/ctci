#include <iostream>
#include <vector>

bool initalize_marix(const std::string&, std::vector<std::vector<int>>&);
bool rotate_matrix(std::vector<std::vector<int>>&);
bool write_matrix_to_file(const std::string&, const std::vector<std::vector<int>>&);

/**
 * Given an image represented by an NxN matrix, where each pixel in the image 
 * is represented by an integer, write a method to rotate the image by 90 degrees.
 * Can you do this in place?
 * This pro
 * 
 * @param fileName file where user wrote matrix NxN. After executing program matrix 
 * will be modified. New matrix is input matrix rotated by 90 degrees.
 */
int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Please provide one parameter in program. Parameter should be file path." << std::endl;
        return 0;
    }
    std::vector<std::vector<int>> matrix;
    const std::string file_name = argv[1];
    if(initalize_marix(file_name, matrix) == false) {
        std::cout << "Matrix is not initailized." << std::endl;
        return 0;
    }
    if(rotate_matrix(matrix) == false) {
        std::cout << "Error while rotating matrix." << std::endl;
    }
    if(write_matrix_to_file(file_name, matrix) == false) {
        std::cout << "Error while writing matrix to file." << std::endl;
    }
}

bool initalize_marix(const std::string& file_name, std::vector<std::vector<int>>& matrix) {

}

bool rotate_matrix(std::vector<std::vector<int>>& matrix) {

}

bool write_matrix_to_file(const std::string& file_name, const std::vector<std::vector<int>>& matrix) {

}
