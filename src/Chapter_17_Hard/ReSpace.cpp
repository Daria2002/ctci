#include <iostream>
#include <unordered_set>
#include <limits>

class Result
{
    public:
        Result() = default;
        Result(int n, std::string p) : parsed(p), num_of_wrong_chars(n) {}
        int num_of_wrong_chars = std::numeric_limits<int>::max();
        std::string parsed = " ";
};

std::string parse_bf(std::unordered_set<std::string> words, std::string sentence)
{

    return "";
}

std::string parse_optimized(std::unordered_set<std::string> words, std::string sentence)
{
    return "";
}

/**
 * Re-Space: Oh, no! You have accidentally removed all spaces, punctuation, and capitalization in a lengthy document.
 * A sentence like "I reset the computor. It still didn't boot!" became "iresetthecomputeritstilldidntboot". You'll
 * deal with the punctation and capitalization later; right now you need to re-insert the spaces. Most of the words are
 * in a dictionary but a few are not. Given a dictionary (a list of strings) and the document (a string), design an algorithm
 * to unconcatenate the document in a way that minimizes the number of the unrecognized characters.
 * EXAMPLE:
 * Input: jesslookedjustliketimherbrotheer
 * Output: jess* looked just like tim* her brother (7 unrecognized characters)
 */
int main()
{
    int method;
    std::cout << "Enter 1 to use brute force approach or any other number for optimized approach:\n";
    std::cin >> method;
    // set contains only few words needed for testing
    std::unordered_set<std::string> words = {"looked", "like", "brother", "her", "just", "look", "liked"};
    std::string sentence = "jesslookedjustliketimherbrotheer";
    std::cout << (method == 1 ? parse_bf(words, sentence) : parse_optimized(words, sentence)) << '\n';
}