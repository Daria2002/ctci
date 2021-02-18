#include <iostream>
#include <vector>

class Subsquare
{
    public:
        Subsquare() = default;
        Subsquare(int r, int c, int s) : row(r), col(c), size(s) {}
        int row, col, size;
};

Subsquare find_max_square_preprocessing(std::vector<std::vector<int>> matrix)
{
    
}

Subsquare find_max_square_simple(std::vector<std::vector<int>> matrix)
{
    
}

std::vector<std::vector<int>> generate_matrix()
{

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