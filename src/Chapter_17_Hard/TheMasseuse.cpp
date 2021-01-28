#include <iostream>
#include <vector>

int max_minutes_recursion(const std::vector<int>& requests, const int index)
{
    if(index >= requests.size()) return 0;
    int with = requests[index] + max_minutes_recursion(requests, index + 2);
    int without = max_minutes_recursion(requests, index + 1);
    return (with > without ? with : without);
}

int max_minutes_recursion(const std::vector<int>& requests)
{
    return max_minutes_recursion(requests, 0);
}

int max_minutes_recursion_memo(std::vector<int> requests)
{
    // todo
    return 0;
}

int max_minutes_iterative(std::vector<int> requests)
{
    // todo
    return 0;
}

int max_minutes_iterative_optimal(std::vector<int> requests)
{
    // todo
    return 0;
}

/**
 * The Masseuse: A popular masseuse receives a sequence of back-to-back appointment requests
 * and is debating which ones to accept. She needs a 15-minute break between appointments and
 * therefore she cannot accept any adjecent requests. Given a sequence of back-to-back appointment
 * requests (all multiples of 15 minutes, non overlap, and none can be moved), find the optimal
 * (highest total booked minutes) set the masseuse can honor.
 * EXAMPLE:
 * Input: {30, 15, 60, 75, 45, 15, 15, 45}
 * Output: 180 minutes ({30, 60, 45, 45})
 */
int main()
{
    std::cout << "Select method: 1 - recursion, 2 - recursion + memoization, 3 - iterative,\n"
    "any other number - iterative with optimal time and space:\n";
    int method;
    std::cin >> method;
    int max_minutes;
    std::vector<int> requests = {30, 15, 60, 75, 45, 15, 15, 45};
    if (method == 1)
    {
        max_minutes = max_minutes_recursion(requests);
    }
    else if (method == 2)
    {
        max_minutes = max_minutes_recursion_memo(requests);
    }
    else if (method == 3)
    {
        max_minutes = max_minutes_iterative(requests);
    }
    else 
    {
        max_minutes = max_minutes_iterative_optimal(requests);
    }
    std::cout << "Max minutes = " << max_minutes << '\n';
}