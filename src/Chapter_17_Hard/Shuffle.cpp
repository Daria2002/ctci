#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

std::vector<int> shuffle_recursively(std::vector<int>& cards, int i)
{
    if(i == 0) return cards;
    shuffle_recursively(cards, i - 1);
    int k = rand() % i; // k is number in range [0, i - 1]
    int tmp = cards[k];
    cards[k] = cards[i];
    cards[i] = tmp;
    return cards;
}

std::vector<int> shuffle_recursively(std::vector<int> cards)
{
    shuffle_recursively(cards, cards.size() - 1);
    return cards;
}

std::vector<int> shuffle_iteratively(std::vector<int> cards)
{
    for(int i = 0; i < cards.size(); i++)
    {
        int k = rand() % (i + 1); // k is element in range [0, i]
        int tmp = cards[k];
        cards[k] = cards[i];
        cards[i] = tmp;
    }
    return cards;
}

std::vector<int> get_cards()
{
    std::vector<int> cards;
    constexpr int number_of_cards = 52;
    for(int i = 1; i <= number_of_cards; i++) cards.push_back(i);
    return cards;
}

/**
 * Shuffle: Write a method to shuffle a deck of cards. It must be a perfect 
 * suffle - in other words, each of the 52! permutations of the deck has to 
 * be equally likely. Assume that you are given a random number generator
 * which is perfect.
 */
int main()
{
    srand(time(NULL));
    std::cout << "Enter 1 to solve recursively or any other number to solve iteratively:\n";
    int method;
    std::cin >> method;
    std::vector<int> cards = get_cards();
    std::vector<int> numbers = (method == 1 ? shuffle_recursively(cards) : shuffle_iteratively(cards));
    std::cout << "Numbers: ";
    for(int number : numbers) std::cout << number << ", ";
    std::cout << '\n';
}