#include <iostream>
#include <vector>

class Bottle {
    public:
        Bottle() = default;
        Bottle(int i) : id(i) {}
        int id;
        bool poisoned = false;
};

class Test_Strip {
    public:
        Test_Strip() = default;
        Test_Strip(int i) : id(i) {}
        int id;
        const static int days_for_result = 7;
        // add drop from bottle on this test strip on specific day
        void add_drop_on_day(const Bottle& bottle, const int day) {
            if(drops_by_day.size() < day) {
                drops_by_day.resize(day + 1);
            }
            drops_by_day[day].push_back(bottle);
        }
    private:
        // this test stripe can be used multiple times
        // drops_by_day is vector of days where each day is represented as
        // a vector of bottles tested on that day
        std::vector<std::vector<Bottle>> drops_by_day;
};

void naive_find_poisoned_bottle() {

}

void optimized_find_poisoned_bottle() {
    
}

void optimal_find_poisoned_bottle() {
    
}

/**
 * You have 1000 bottles of soda, and exactly one is poisoned. You have 10 test strips which 
 * can be used to detect poison. A single drop of poison will turn the test strip positive 
 * permanently. You can put any number of drops on a test strip at once and you can reuse a test 
 * strip as many times as you'd like (as long as the results are negative). However, you can only 
 * run tests once per day and it takes seven days to return a result. How would you figure out the 
 * poisoned bottle in as few days as possible? 
 * Follow up: Write code to simulate your approach.
 */
int main() {
    std::cout << "===========================================\n"
                 "Program for testing content in 1000 bottles\n"
                 "===========================================\n";
    int method;
    std::cout << "Choose a method for finding poisoned bottle:\n"
                 "1 - Naive Approach (28 days)\n"
                 "2 - Optimized Approach (10 days)\n"
                 "3 - Optimal Approach (7 days)\n";
    std::cin >> method;
    switch (method) {
    case 1:
        naive_find_poisoned_bottle();
        break;
    case 2:
        optimized_find_poisoned_bottle();
        break;
    case 3:
        optimal_find_poisoned_bottle();
        break;
    default:
        std::cout << "None of the proposed methods have not been choosen.\n";
        return;
    }
}
