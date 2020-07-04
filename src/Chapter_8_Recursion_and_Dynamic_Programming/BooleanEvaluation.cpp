#include <iostream>

int count_eval_bf(std::string expression, bool result) {
    // TODO
    return 0;
}

int count_eval_optimal(std::string expression, bool result) {
    // TODO
    return 0;
}


/**
 * Given a boolean expression consisting of the symbols 0 (false), 1 (true), & (AND), | (OR), and ^(XOR), 
 * and a desired boolean result value result, implement a function to count the number of ways of parenthesizing 
 * the expression such that it evaluates to result. The expression should be fully parenthesized (e.g., (0)^(1))
 * but not extraneously (e.g., (((0) ^ (1))))
 * EXAMPLE:
 * countEval("1^0|0|1", false) -> 2
 * countEval("0&0&0&1^1|0", true) -> 10
 */
int main() {
    std::cout << "Enter boolean expression\n";
    std::string expression;
    std::cin >> expression;
    std::cout << "Enter result for the boolean expression\n";
    std::string result_string;
    std::cin >> result_string;
    bool result = (result_string == "true" ? true : false);
    std::cout << "Enter 1 to solve using brute force solution or any other number to solve using optimal solution\n";
    int method; 
    std::cin >> method;
    int number_of_ways;
    switch (method)
    {
    case 1:
        number_of_ways = count_eval_bf(expression, result);
        break;
    default:
        number_of_ways = count_eval_optimal(expression, result);
        break;
    }
    std::cout << "Number of ways of parenthesizing the expression such that it evaluates to result = " << number_of_ways << '\n';
}