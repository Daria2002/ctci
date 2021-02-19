#include <iostream>
#include <vector>

class Subsquare
{
    public:
        Subsquare() = default;
        Subsquare(int r, int c, int s) : row(r), col(c), size(s) {}
        int row = -1, col = -1, size = -1;
};

bool is_square(const std::vector<std::vector<int>>& matrix, const int row, const int col, const int size)
{
    // check top and bottom border
    for(int j = 0; j < size; j++)
    {
        if(matrix[row][col + j] == 0) return false;
        if(matrix[row + size - 1][col + j] == 0) return false;
    }
    // check left and right border
    for(int j = 0; j < size; j++)
    {
        if(matrix[row + j][col] == 0) return false;
        if(matrix[row + j][col + size - 1] == 0) return false;
    }
    return true;
}

bool find_sequence(const std::vector<std::vector<int>>& matrix, const int size, Subsquare& s)
{
    int count = matrix.size() - size + 1;
    for(int row = 0; row < count; row++)
    {
        for(int col = 0; col < count; col++)
        {
            if(is_square(matrix, row, col, size))
            {
                s = Subsquare(row, col, size);
                return true;
            }
        }
    }
    return false;
}

Subsquare find_max_square_preprocessing(const std::vector<std::vector<int>>& matrix)
{
    Subsquare s;
    // todo
    return s;   
}

Subsquare find_max_square_simple(const std::vector<std::vector<int>>& matrix)
{
    Subsquare s;
    for(int size = matrix.size(); size >= 1; size--)
    {
        if(find_sequence(matrix, size, s)) return s;
    }
    return s;
}

std::vector<std::vector<int>> generate_matrix()
{
    std::vector<std::vector<int>> v = 
    {
        {0, 0, 1, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 1, 1, 1},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };
    return v;
}

/**
 * Max Black Square: Imagine you have a square matrix, where each cell (pixel) is either black
 * or white. Design an algorithm to find the maximum subsquare such that all four borders are 
 * filled with black pixels.
 */
int main()
{
    std::cout << "Enter 1 to solve using simple solution or any other number to solve using pre-processing:\n";
    int method;
    std::cin >> method;
    std::vector<std::vector<int>> matrix = generate_matrix();
    Subsquare s;
    if(method == 1)
    {
        s = find_max_square_simple(matrix);
    }
    else 
    {
        s = find_max_square_preprocessing(matrix);
    }
    std::cout << "Maximum subsquare has left top at (" << s.row << ", " << s.col << ") and size = " << s.size << '\n';
}