#include <iostream>
#include <vector>
#include <array>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#define NUMBER_OF_BOTTLES 1000
#define NUMBER_OF_TEST_STRIPES 10
#define TESTING_PERIOD 7
#define MAX_NUM_OF_DIGITS 3 // [0, 999]

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
        bool usable = true;
        const static int days_for_result = 7;
        // add drop from bottle on this test strip on specific day
        void add_drop_on_day(const Bottle& bottle, const int day) {
            if(drops_by_day.size() <= day) {
                drops_by_day.resize(day + 1);
            }
            drops_by_day[day].push_back(bottle);
        }
        bool is_positive_on_day(int day) {
            int test_start_day = day - TESTING_PERIOD;
            if(test_start_day < 0 || test_start_day >= drops_by_day.size()) {
                return false;
            }
            for(int i = 0; i <= test_start_day; i++) {
                std::vector<Bottle> bottles = drops_by_day[i];
                if(has_poison(bottles)) {
                    usable = false;
                    return true;
                }
            }
            return false;
        }
        std::vector<Bottle> get_last_weeks_bottles(int day) {
            std::vector<Bottle> bottles;
            if(day < TESTING_PERIOD) {
                return bottles;
            }
            return drops_by_day[day - TESTING_PERIOD];
        }
    private:
        // this test stripe can be used multiple times
        // drops_by_day is vector of days where each day is represented as
        // a vector of bottles tested on that day
        std::vector<std::vector<Bottle>> drops_by_day;
        bool has_poison(std::vector<Bottle> bottles) {
            for(Bottle b : bottles) {
                if(b.poisoned) {
                    return true;
                }
            }
            return false;
        }
};

void drop_content_on_stripes(std::vector<Bottle>& bottles, std::vector<Test_Strip>& test_stripes, int day) {
    int index = 0;
    for(Bottle b : bottles) {
        test_stripes[index].add_drop_on_day(b, day);
        index = (index + 1) % NUMBER_OF_TEST_STRIPES;
    }
}

void remove_positive_stripes(std::vector<Bottle>& bottles, std::vector<Test_Strip>& test_stripes, int today) {
    int i;
    for(i = 0; i < test_stripes.size(); i++) {
        if(test_stripes[i].is_positive_on_day(today)) { // if test_stripes[i] was ever positive
            bottles = test_stripes[i].get_last_weeks_bottles(today);
            break;
        }
    }
    // new_test_stripes vector doesn't contain positive test stripe
    // it contains only the ones that can be reused
    test_stripes.erase(test_stripes.begin() + i);
}

int naive_find_poisoned_bottle(std::vector<Bottle> bottles, std::vector<Test_Strip> test_stripes) {
    int today = 0;
    while (bottles.size() > 0 && test_stripes.size() > 0) {
        drop_content_on_stripes(bottles, test_stripes, today);
        today += TESTING_PERIOD;
        remove_positive_stripes(bottles, test_stripes, today);
    }
    return bottles.size() == 1 ? bottles[0].id : -1;
}

int get_index(Bottle bottle, int day) {
    int id = bottle.id;
    switch (day)
    {
    case 0:
        return id/100;
    case 1:
        return (id%100)/10;
    case 2:
        return (id%10);
    case 3:
        return (id%10+1)%NUMBER_OF_TEST_STRIPES;
    default:
        return -1;
    }
}

void drop_content_on_strips_optimized(const std::vector<Bottle> bottles, std::vector<Test_Strip>& test_stripes, int day) {
    if(day > 3) return; 
    for(Bottle b : bottles) {
        int index = get_index(b, day);
        test_stripes[index].add_drop_on_day(b, day);
    }
}

int get_positive_on_day(std::vector<Test_Strip>& test_stripes, int result_day) {
    for(Test_Strip& s : test_stripes) {
        int id = s.id;
        if(s.usable && s.is_positive_on_day(result_day)) {
            return s.id;
        }
    }
    return -1;
}

int optimized_find_poisoned_bottle(std::vector<Bottle> bottles, std::vector<Test_Strip>& test_stripes) {
    int today = 0, iter = 0, index = 0;
    std::array<int, MAX_NUM_OF_DIGITS + 1> digits;
    
    // every day is used for testing one digit + one extra
    for(int day = 0; day < MAX_NUM_OF_DIGITS + 1; day++) {
        drop_content_on_strips_optimized(bottles, test_stripes, day);
    }
    for(int day = 0; day < MAX_NUM_OF_DIGITS + 1; day++) {
        int result_day = day + TESTING_PERIOD;
        digits[day] = get_positive_on_day(test_stripes, result_day);
    }

    if(digits[1] == -1) {
        digits[1] = digits[0];
    }

    if(digits[2] == -1) { // digits[2] is same as digits[1] or digits[0]
        if(digits[3] == -1) {
            // in this case digits[2] is same as digits[1] or digits[0], but digit[0] + 1 == digit[1]
            // because even after shifting test there is an overlap, so second digit is calculated using this:
            digits[2] = (digits[0] + 1) % NUMBER_OF_TEST_STRIPES == digits[1] ? digits[0] : digits[1];
        } else {
            digits[2] = (digits[3] - 1 + NUMBER_OF_TEST_STRIPES) % NUMBER_OF_TEST_STRIPES;
        }
    }
    return digits[0] * 100 + digits[1] * 10 + digits[2];
}

int optimal_find_poisoned_bottle(std::vector<Bottle> bottles, std::vector<Test_Strip> test_stripes) {
    int day = 0, result = 0;
    // go throw binary representation of the bottle.id and if bit = 1 put bottle drop on test strip with id equal to bit index
    for(const Bottle bottle : bottles) {
        int id = bottle.id;
        int index = 0;
        while (id != 0) {
            if((id & 1) == 1) {
                test_stripes[index].add_drop_on_day(bottle, day);
            }
            id >>= 1;
            index++;
        }
    }
    day += TESTING_PERIOD;
    // go through all test strips and if a test strip is positive we know that bottle id has bit 1 on position test_strip.id 
    for(int test_index = 0; test_index < test_stripes.size(); test_index++) {
        if(test_stripes[test_index].is_positive_on_day(day)) {
            result = result + (1 << test_index);
        }
    }
    return result;
}

std::vector<Bottle> set_bottles() {
    std::vector<Bottle> bottles;
    srand(time(NULL));
    int poisoned_id = rand() % NUMBER_OF_BOTTLES;
    std::cout << "Randomly selected poison bottle id = " << poisoned_id << '\n';
    for(int i = 0; i < NUMBER_OF_BOTTLES; i++) {
        Bottle b(i);
        if(poisoned_id == i) b.poisoned = true;
        bottles.push_back(b);
    }
    return bottles;
}

std::vector<Test_Strip> set_test_stripes() {
    std::vector<Test_Strip> stripes;
    for(int i = 0; i < NUMBER_OF_TEST_STRIPES; i++) {
        Test_Strip s(i);
        stripes.push_back(s);
    }
    return stripes;
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
    std::vector<Bottle> bottles = set_bottles();
    std::vector<Test_Strip> test_stripes = set_test_stripes();
    int poisoned_bottle;
    switch (method) {
    case 1:
        poisoned_bottle = naive_find_poisoned_bottle(bottles, test_stripes);
        break;
    case 2:
        poisoned_bottle = optimized_find_poisoned_bottle(bottles, test_stripes);
        break;
    case 3:
        poisoned_bottle = optimal_find_poisoned_bottle(bottles, test_stripes);
        break;
    default:
        std::cout << "None of the proposed methods have not been choosen.\n";
        return 0;
    }
    std::cout << "Poisoned bottle = " << poisoned_bottle << '\n';
    return 0;
}
