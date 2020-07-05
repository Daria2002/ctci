#include <iostream>
#include <unordered_map>
#include <algorithm>

bool string_to_bool(std::string str) {
    return str == "1" ? true : false;
}

int count_eval_bf(std::string expression, bool result) {
    if(expression.size() == 0) return 0;
    if(expression.size() == 1) return string_to_bool(expression) == result ? 1 : 0;

    int ways = 0;
    for(int i = 1; i < expression.size(); i += 2) { // split with operator
        char op = expression[i];
        std::string left = expression.substr(0, i);
        std::string right = expression.substr(i + 1);
        int left_true = count_eval_bf(left, true);
        int left_false = count_eval_bf(left, false);
        int right_true = count_eval_bf(right, true);
        int right_false = count_eval_bf(right, false);
        int total = (left_false + left_true) * (right_false + right_true);
        int total_true = 0;
        switch (op)
        {
        case '^':
            total_true = left_true * right_false + left_false * right_true;
            break;
        case '&':
            total_true = left_true * right_true;
            break;
        default: // | (OR)
            total_true = left_true * right_false + left_false * right_true + 
                         left_true * right_true;
            break;
        }
        int count = result ? total_true : total - total_true;
        ways += count;
    }

    return ways;
}

int count_eval_optimal(std::string expression, bool result, std::unordered_map<std::string, int>& hash_map) {
    if(expression.size() == 0) return 0;
    if(expression.size() == 1) return string_to_bool(expression) == result ? 1 : 0;

    std::string key = (result == true ? "t" : "f") + expression;
    std::unordered_map<std::string, int>::const_iterator got = hash_map.find(key);
    if (got != hash_map.end()) return got -> second; // already int hash_map

    int ways = 0;
    for(int i = 1; i < expression.size(); i += 2) {
        std::string left = expression.substr(0, i);
        std::string right = expression.substr(i + 1);
        int left_true = count_eval_optimal(left, true, hash_map);
        int left_false = count_eval_optimal(left, false, hash_map);
        int right_true = count_eval_optimal(right, true, hash_map);
        int right_false = count_eval_optimal(right, false, hash_map);
        int total = (left_true + left_false) * (right_true + right_false);
        int total_true = 0;
        char op = expression[i];
        switch (op)
        {
        case '^': // XOR
            total_true = (left_true * right_false) + (left_false * right_true);
            break;
        case '&': // AND 
            total_true = left_true * right_true;
            break;
        default: // OR operation
            total_true = left_true * right_true + left_true * right_false + left_false * right_true;
            break;
        }
        ways += (result ? total_true : total - total_true); // if result == true take total_true, otherwise total_false
    }
    hash_map[key] = ways;
    return ways;
}

int count_eval_optimal(std::string expression, bool result) {
    std::unordered_map<std::string, int> hash_map;
    return count_eval_optimal(expression, result, hash_map);
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