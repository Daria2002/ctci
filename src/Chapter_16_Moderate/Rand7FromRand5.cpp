#include <iostream>
#include <ctime>
#include <cstdlib>

int rand5()
{
    return rand() % 5;
}

int rand7_nondeterministic_num_of_calls()
{
    while(true)
    {
        int num = 5 * rand5() + rand5(); // 2 digit base 5 num
        // num = [0, 25].num < 7 would eliminate a lot of nums and loop would have a 
        // lot of iterations to get rand num < 7.21 is choosen because it's closest to 
        // the end of the range and also it's divided by 7
        if(num < 21) return num % 7;
    }
}

int rand7_fixed_num_of_calls()
{
    std::cout << "Code with fixed number of calls is not good because it\n"
    "will not generate the values with equal probability.\n";
    return (rand5() + rand5()) % 7;
}

/**
 * Rand7 from Rand5: Implement a method rand7() given rand5(). That is, given a method that
 * generates a random integer between 0 and 4 (inclusive), write a method that generates a
 * random integer breween 0 and 6 (inclusive).
 */
int main()
{
    std::cout << "Enter 1 to solve using fixed number of calls or any other number to solve\n"
    "using nondeterministic number of calls:\n";
    int method;
    std::cin >> method;
    int rand7;
    srand(time(NULL));
    if(method == 1) rand7 = rand7_fixed_num_of_calls();
    else rand7 = rand7_nondeterministic_num_of_calls();
    std::cout << "Rand7 = " << rand7 << '\n';
}