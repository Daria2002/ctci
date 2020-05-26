#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> get_opened_lockers(const int num_of_lockers) {
    /* 
        every number has factors (at least itself and 1)
        num = 5, factors = 1, 5
        num = 6, factors = 1, 2, 3, 6
        prime numbers have factors = {pair}, pair = (1, itself)
        non-prime numbers have factors = {pairs}
        pairs? i.e. num = 20, pairs = {(1, itself), (2, 10), (4, 5)}
        one pair member opens and other closes the locker
        so, what numbers don't have open/close pairs or what numbers have odd number of factors?
        answer: the one that have pair where 1st and 2nd pair member are the same number
        i.e. it contains pairs : (1, 1), (2, 2), (3, 3)... there is only one pass in the hallway
        while the pair (1, 4) has two passes in the hallway
        perfect square numbers contain pairs with two same integer values
    */ 
    int root = std::sqrt(num_of_lockers); 
    std::vector<int> perfect_square_numbers;
    for(int i = 1; i <= root; i++) {
        perfect_square_numbers.push_back(i * i);
    }
    return perfect_square_numbers;
}

/**
 * There are 100 closed lockers in a hallway. A man begins by opening all 100 lockers. 
 * Next, he closes every second locker. Then, on his third pass, he toggles every third 
 * locker (closes it if it is open or opens it if it is closed). This process continues 
 * for 100 passes, such that on each pass i, the man toggles every ith locker. After his 
 * 100th pass in the hallway, in which he toggles only locker #100, how many lockers are open?
 */
int main() {
    std::cout << "==============================================\n"
                 "Program to calculate how many lockers are open\n"
                 "==============================================\n";
    std::cout << "Enter the number of lockers:\n";
    int num_of_lockers = 0;
    std::cin >> num_of_lockers;
    std::vector<int> opened_lockers = get_opened_lockers(num_of_lockers);
    std::cout << "Opened lockers:\n";
    for(int i : opened_lockers) {
        std::cout << i << '\n';
    }
}
