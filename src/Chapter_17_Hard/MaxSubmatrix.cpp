#include <iostream>
#include <vector>

class SubMatrix
{
    public:
        SubMatrix() = default;
        SubMatrix(int r1, int c1, int r2, int c2, int s) : row1(r1), col1(c1), row2(r2), col2(c2), sum(s) 
        {
            initialized = true;
        }
        int row1, col1, row2, col2, sum;
        bool initialized = false;
};

int sum_submatrix(const std::vector<std::vector<int>>& matrix, const int row1, const int col1, const int row2, const int col2)
{
    int sum = 0; 
    for(int r = row1; r <= row2; r++)
    {
        for(int c = col1; c <= col2; c++)
        {
            sum += matrix[r][c];
        }
    }
    return sum;
}

SubMatrix max_submatrix_bf(const std::vector<std::vector<int>>& matrix)
{
    int count = matrix.size();
    SubMatrix best;
    for(int row1 = 0; row1 < count; row1++)
    {
        for(int row2 = 0; row2 < count; row2++)
        {
            for(int col1 = 0; col1 < count; col1++)
            {
                for(int col2 = 0; col2 < count; col2++)
                {
                    int sum = sum_submatrix(matrix, row1, col1, row2, col2);
                    if(!best.initialized || best.sum < sum)
                    {
                        best = SubMatrix(row1, col1, row2, col2, sum);
                    }   
                }
            }
        }
    }
    return best;
}

std::vector<std::vector<int>> precompute_sums(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>> sums = matrix; // initialize to matrix, just because of the space initialization
    for(int r = 0; r < matrix.size(); r++)
    {
        for(int c = 0; c < matrix[0].size(); c++)
        {
            int left = c > 0 ? sums[r][c - 1] : 0;
            int top = r > 0 ? sums[r - 1][c] : 0;
            int overlap = r > 0 && c > 0 ? sums[r - 1][c - 1] : 0;
            sums[r][c] = left + top - overlap + matrix[r][c];
        }
    }
    return sums;
}

int sum_area(std::vector<std::vector<int>> sum_through, int r1, int c1, int r2, int c2)
{
    int top_left = r1 > 0 && c1 > 0 ? sum_through[r1 - 1][c1 - 1] : 0;
    int full = sum_through[r2][c2];
    int left = c1 > 0 ? sum_through[r2][c1 - 1] : 0;
    int top = r1 > 0 ? sum_through[r1 - 1][c2] : 0;
    return full - left - top + top_left;
}

SubMatrix max_submatrix_dp(const std::vector<std::vector<int>>& matrix)
{
    SubMatrix best;
    int row_count = matrix.size();
    int col_count = matrix[0].size();
    std::vector<std::vector<int>> sum_through = precompute_sums(matrix);
    for(int row1 = 0; row1 < row_count; row1++)
    {
        for(int row2 = 0; row2 < row_count; row2++)
        {
            for(int col1 = 0; col1 < col_count; col1++)
            {
                for(int col2 = 0; col2 < col_count; col2++)
                {
                    int sum = sum_area(sum_through, row1, col1, row2, col2);
                    if(!best.initialized || best.sum < sum)
                    {
                        best = SubMatrix(row1, col1, row2, col2, sum);
                    }
                }
            }
        }
    }
    return best;
}

class Range
{
    public:
        Range() = default;
        Range(int s, int e, int range_sum) : start(s), end(e), sum(range_sum) 
        {
            initialized = true;
        }
        int start, end, sum;
        bool initialized = false;
};

std::ostream& operator<<(std::ostream& os, const Range& r) {
    os << "[" << r.start << ", " << r.end << "]";
    return os;
}

Range max_subarray(const std::vector<int>& arr)
{
    Range best;
    int start = 0; 
    int sum = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        if(!best.initialized || sum > best.sum)
        {
            best = Range(start, i, sum);
        }
        if(sum < 0)
        {
            start = i + 1;
            sum = 0;
        }
    }
    return best;
}

SubMatrix max_submatrix_optimized(std::vector<std::vector<int>> matrix)
{
    const int row_count = matrix.size();
    const int col_count = matrix[0].size();
    SubMatrix best;
    for(int row_start = 0; row_start < row_count; row_start++)
    {
        std::vector<int> partial_sum(col_count);
        for(int row_end = row_start; row_end < row_count; row_end++)
        {
            for(int i = 0; i < col_count; i++)
            {
                partial_sum[i] += matrix[row_end][i];
            }
            Range best_range = max_subarray(partial_sum);
            if(!best.initialized || best.sum < best_range.sum)
            {
                best = SubMatrix(row_start, best_range.start, row_end, best_range.end, best_range.sum);
            }
        }
    }
    return best;
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
    std::vector<std::vector<int>> matrix = {
        {1, 4, 5, 2, -3, -7}, 
        {-1, 5, 1, 2, 0, 1}, 
        {2, 4, 2, -8, -1, -1}, 
        {-1, -2, 2, 3, 1, 4}, 
        {1, 4, 2, 7, -10, 9}, 
        {7, 4, -8, 8, -4, 1}};
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