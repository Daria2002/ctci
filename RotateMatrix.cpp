#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

bool initalize_marix(const std::string&, std::vector<std::vector<int>>&);
void rotate_matrix(std::vector<std::vector<int>>&);
bool write_matrix_to_file(const std::string&, const std::vector<std::vector<int>>&);
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
    
    if(check_dimensions(matrix) == false) {
        std::cout << "Matrix dimensions should be NxN." << std::endl;
        return 0;
    }

    rotate_matrix(matrix);

    if(write_matrix_to_file(file_name, matrix) == false) {
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

bool split(const std::string& line, const char delimiter, std::vector<int>& elements) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream ss(line);
    std::string tmp;
    int number;
    while(std::getline(ss, tmp, delimiter)) {
        try {
            number = std::stoi(tmp);
        } catch(const std::exception& e) {
            return false;
        }
        elements.push_back(number);
    }
    return true;
}

bool initalize_marix(const std::string& file_name, std::vector<std::vector<int>>& matrix) {
    std::ifstream file;
    file.open(file_name);
    if(file.is_open() == false) {
        return false;
    }
    std::vector<int> row_elements;
    std::string line;
    while(std::getline(file, line)) {
        if(split(line, ',', row_elements) == false) {
            return false;
        }
        matrix.push_back(row_elements);
        row_elements.clear();
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

bool write_matrix_to_file(const std::string& file_name, const std::vector<std::vector<int>>& matrix) {
    std::ofstream file(file_name);
    if(!file.is_open()) {
        return false;
    }
    const int n = matrix.size();
    std::string row;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            row.append(std::to_string(matrix[i][j]));
            if(j != n - 1) {
                row.append(",");
            }
        }
        file << row << std::endl;
        row.clear();
    }
    file.close();
    return true;
}