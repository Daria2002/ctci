#include <iostream>
#include <vector>

enum Money {
    Quarters = 25, 
    Dimes = 10, 
    Nickles = 5, 
    Pennies = 1, 
};

int number_of_ways(int n, std::vector<Money> money, int index) {
    int num_of_ways = 0;
    int val = money[index];
    if(index == money.size() - 1) {
        return (n % val == 0 ? 1 : 0);
    }
    for(int i = 0; i <= n; i += val) {
        num_of_ways += number_of_ways(n - i, money, index + 1);
    }
    return num_of_ways;
}

int number_of_ways(int n, std::vector<Money> money) {
    return number_of_ways(n, money, 0);
}

int number_of_ways_optimal(int n, std::vector<Money> money, int index) {
    // TODO
}

int number_of_ways_optimal(int n, std::vector<Money> money) {
    return number_of_ways_optimal(n, money, 0);
}

/**
 * Given an infinite number of quarters (25 cents), dimes (10 cents), nickles (5 cents), and
 * pennies (1 cent), write code to calculate the number of ways of representing n cents.
 */
int main() {
    int n, num_of_ways, method;
    std::cout << "Enter n:\n";
    std::cin >> n;
    std::cout << "Enter 1 to solve the problem using optimal algorithm, otherwise any other number:\n";
    std::cin >> method;
    std::vector<Money> money = { Quarters, Dimes, Nickles, Pennies };
    std::cout << "There are " << (method == 1 ? number_of_ways_optimal(n, money) : number_of_ways(n, money)) 
    << " ways of representing " << n << " cents.\n";
}
