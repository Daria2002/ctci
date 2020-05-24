#include <iostream>
#include <cmath>

/**
 * Ants won't collide if they are moving in the same direction (clockwise or counterclockwise).
 * So, p = 1 - p_clockwise - p_counterclockwise
 * p - probability to collide
 * p_clockwise - probability that all ants move clockwise
 * p_counterclockwise - probability that all ants move counterclockwise
 * there are two possible directions, so the probability for choosing one of them is 1/2
 * For n ants, probability for choosing certain direction = (1/2)^n
 * p = 1 - p_clockwise - p_counterclockwise = 1 - (1 / 2) ^ n - (1 / 2) ^ n = 1 - 2 * (1 / 2) ^ n = 1 - (1 / 2) ^ (n - 1) 
 */
double collision_probability(const int n) {
    return 1 - std::pow(1./2, n - 1);
}

/**
 * There are three ants on different vertices of a triangle. What is the probability of
 * collision (between any two or all of them) if they start walking on the sides of the triangle?
 * Assume that each ant randomly picks a direction, with either direction being equally likely to 
 * be chosen, and that they walk at the same speed.
 * Similary, find the probability of collision with n ants on an n-vertex polygon.
 */
int main() {
    std::cout << "=======================================================================================\n"
                 "Program for calculating the probability of collision with n ants on an n-vertex polygon\n"
                 "=======================================================================================\n";
    int n;
    std::cout << "Enter n:\n";
    std::cin >> n;
    std::cout << "Probability of collision = " << collision_probability(n) << '\n';
}