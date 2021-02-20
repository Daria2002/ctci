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

bool find_square(const std::vector<std::vector<int>>& matrix, const int size, Subsquare& s)
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

class SquareCell 
{
    public:
        SquareCell() = default;
        SquareCell(int zr, int zb) : zeros_right(zr), zeros_below(zb) {}
        int zeros_right, zeros_below;
};

bool is_square2(std::vector<std::vector<SquareCell>> processed, const int row, const int col, const int size)
{
    SquareCell top_left = processed[row][col];
    SquareCell top_right = processed[row][col + size - 1];
    SquareCell bottom_left = processed[row + size - 1][col];
    if(top_left.zeros_right < size || top_left.zeros_below < size || top_right.zeros_below < size ||
    bottom_left.zeros_right < size) return false;
    return true;
}

bool find_square2(std::vector<std::vector<SquareCell>> processed, const int size, Subsquare& s)
{
    int count = processed.size() - size + 1;
    for(int row = 0; row < count; row++)
    {
        for(int col = 0; col < count; col++)
        {
            if(is_square2(processed, row, col, size))
            {
                s = Subsquare(row, col, size);
                return true;
            }
        }
    }
    return false;
}

std::vector<std::vector<SquareCell>> process_square(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<SquareCell>> processed;
    for(int i = 0; i < matrix.size(); i++)
    {
        std::vector<SquareCell> v;
        for(int j = 0; j < matrix.size(); j++) v.push_back(SquareCell());
        processed.push_back(v);
    }
    for(int r = matrix.size() - 1; r >= 0; r--)
    {
        for(int c = matrix.size() - 1; c >= 0; c--)
        {
            int right_zeros = 0;
            int below_zeros = 0;
            if(matrix[r][c] == 1)
            {
                right_zeros++;
                below_zeros++;
                if(c + 1 < matrix.size())
                {
                    SquareCell prev = processed[r][c + 1];
                    right_zeros += prev.zeros_right;
                }
                if(r + 1 < matrix.size())
                {
                    SquareCell prev = processed[r + 1][c];
                    below_zeros += prev.zeros_below;
                }
            }
            processed[r][c] = SquareCell(right_zeros, below_zeros);
        }
    }
    return processed;
}

Subsquare find_max_square_preprocessing(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<SquareCell>> processed = process_square(matrix);
    Subsquare s;
    for(int i = matrix.size() - 1; i >= 0 ; i--)
    {
        if(find_square2(processed, i, s)) return s;
    }
    return s;
}

Subsquare find_max_square_simple(const std::vector<std::vector<int>>& matrix)
{
    Subsquare s;
    for(int size = matrix.size(); size >= 1; size--)
    {
        if(find_square(matrix, size, s)) return s;
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