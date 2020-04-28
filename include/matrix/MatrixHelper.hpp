#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace MatrixFile 
{
    class MatrixManager
    {
        public:
            static bool initalize_matrix(const std::string& file_name, std::vector<std::vector<int>>& matrix) {
                std::ifstream file;
                file.open(file_name);
                if(file.is_open() == false) {
                    return false;
                }
                std::vector<int> row_elements;
                std::string line;
                while(std::getline(file, line)) {
                    if(MatrixFile::MatrixManager::split(line, ',', row_elements) == false) {
                        return false;
                    }
                    matrix.push_back(row_elements);
                    row_elements.clear();
                }
                return true;
            }

            static bool write_matrix_to_file(const std::string& file_name, const std::vector<std::vector<int>>& matrix) {
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
        private:
            static bool split(const std::string& line, const char delimiter, std::vector<int>& elements) {
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
    };
}