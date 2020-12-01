#include <iostream>
#include <vector>
#include <cstdlib> // rand, srand
#include <ctime> // time

std::vector<std::vector<int>> get_land(int rows, int cols) 
{
    std::vector<std::vector<int>> land;
    for(int i = 0; i < rows; i++)
    {
        std::vector<int> v;
        for(int j = 0; j < cols; j++)
        {
            v.push_back(rand() % 2);
        }
        land.push_back(v);
    }
    return land;
}

int compute_size(std::vector<std::vector<int>> plot_of_land, std::vector<std::vector<bool>>& visited, int row, int column)
{
    if(row >= plot_of_land.size() || row < 0 || column >= plot_of_land[0].size() || column < 0 || plot_of_land[row][column] != 0 || visited[row][column]) return 0;
    int size = 1;
    visited[row][column] = true;
    for(int delta_row = -1; delta_row <= 1; delta_row++) 
    {
        for(int delta_column = -1; delta_column <= 1; delta_column++)
        {
            size += compute_size(plot_of_land, visited, row + delta_row, column + delta_column);
        }
    }
    return size;
}

std::vector<int> compute_sizes(std::vector<std::vector<int>> plot_of_land)
{
    std::vector<int> sizes;
    std::vector<std::vector<bool>> visited;
    // initialize visited matrix
    for(int r = 0; r < plot_of_land.size(); r++) 
    {
        std::vector<bool> v;
        for(int c = 0; c < plot_of_land[0].size(); c++)
        {
            v.push_back(false);
        }
        visited.push_back(v);
    }
    for(int r = 0; r < plot_of_land.size(); r++)
    {
        for(int c = 0; c < plot_of_land[0].size(); c++)
        {
            int size = compute_size(plot_of_land, visited, r, c);
            if(size > 0) sizes.push_back(size);
        }
    }
    return sizes;
}

std::ostream& operator<<(std::ostream& os, std::vector<int> v)
{
    for(int el : v)
    {
        os << el << '\n';
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<std::vector<int>> matrix) 
{
    for(std::vector<int> row : matrix)
    {
        for(int element : row)
        {
            os << element << ' ';
        }
        os << '\n';
    }
    return os;
}

/**
 * Pond Sizes: You have an integer matrix representing a plot of land, 
 * where the value at that location represents the height above sea level.
 * A value of zero indicates water. A pond is the total number of connected 
 * water cells. Write a method to compute the sizes of all ponds in the matrix.
 */
int main()
{
    srand(time(NULL));
    constexpr int rows = 5;
    constexpr int cols = 5;
    std::vector<std::vector<int>> plot_of_land = get_land(rows, cols);
    std::cout << "Land: \n" << plot_of_land;
    std::vector<int> pond_sizes = compute_sizes(plot_of_land);
    std::cout << "Pond sizes: \n" << pond_sizes;
}