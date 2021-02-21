#include <iostream>
#include <vector>

class SubMatrix
{
    public:
        SubMatrix() = default;
        SubMatrix(int r1, int c1, int r2, int c2) : row1(r1), col1(c1), row2(r2), col2(c2) {}
        int row1, col1, row2, col2;
};

SubMatrix max_submatrix_bf(std::vector<std::vector<int>> matrix)
{
    // todo
}

SubMatrix max_submatrix_dp(std::vector<std::vector<int>> matrix)
{
    // todo
}

SubMatrix max_submatrix_optimized(std::vector<std::vector<int>> matrix)
{
    // todo
}

/**
 * Max Submatrix: Given an NxN matrix of positive and negative integers, write code to find the
 * submatrix with the largest possible sum
 */
int main()
{
    int method;
    std::cout << "Enter 1 to solve using bf solution, 2 to solve using dynamic programming or any\n"
    "other number to solve using optimized solution:\n";
    std::cin >> method;
    SubMatrix max_submatrix;
    std::vector<std::vector<int>> matrix = {{1, 4, 5, 2, -3, -7}, {-1, 5, 1, 2, 0, 1}, {2, 4, 2, -8, -1, -1}, 
    {-1, -2, 2, 3, 1, 4}, {1, 4, 2, 7, -10, 9}, {7, 4, -8, 8, -4, 1}};
    if(method == 1)
    {
        max_submatrix = max_submatrix_bf(matrix);
    }
    else if(method == 2)
    {
        max_submatrix = max_submatrix_dp(matrix);
    }
    else 
    {
        max_submatrix = max_submatrix_optimized(matrix);
    }
    std::cout << "Max submatrix: (" << max_submatrix.row1 << ", " << max_submatrix.col1 << "), (" <<
    max_submatrix.row2 << ", " << max_submatrix.col2 << ")\n";
}