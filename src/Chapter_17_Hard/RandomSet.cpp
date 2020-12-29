#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

std::vector<int> get_original_set(const int n)
{
    std::vector<int> set;
    for(int i = 0; i < n; i++) set.push_back(i);
    return set; 
}

std::vector<int> random_set_recursively(std::vector<int> original_set, int m, int n)
{
    // todo
    return original_set;
}

std::vector<int> random_set_iteratively(std::vector<int> original_set, int m, int n)
{
    // todo
    return original_set;
}

/**
 * Random Set: Write a method to randomly generate a set of m integers from an
 * array of size n. Each element must have equal probability of being choosen.
 */
int main()
{
    int method;
    std::cout << "Enter 1 to solve recursively or any other number to solve iteratively:\n";
    std::cin >> method;
    srand(time(NULL));
    constexpr int n = 5;
    std::vector<int> original_set = get_original_set(n);
    constexpr int m = 3;
    std::vector<int> random_set = (method == 1 ? random_set_recursively(original_set, m, n) : random_set_iteratively(original_set, m, n));
    std::cout << "Random set: ";
    for(int number : random_set) std::cout << number << ", ";
    std::cout << '\n';
}