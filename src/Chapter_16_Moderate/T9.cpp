#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

std::vector<std::vector<char>> t9_letters = {{}, {'a', 'b', 'c'}, {'d', 'e', 'f'},
                                            {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'},
                                            {'p', 'q', 'r', 's'}, {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}};
std::vector<std::string> word_set = {"life", "live", "home", "have", "must", "four", "five", "miss", "note",
"nine", "zero", "teen", "they", "want", "train", "film", "free", "used", "back", "into", "word", "team", "size",
"feel", "this", "that", "cars", "need", "auto", "flow", "swim", "sing", "work", "your", "code", "milk", "says",
"lets", "sees", "give", "puts", "pull", "down", "gets", "gets", "acts", "love", "flat", "firm", "apps", "mode",
"eats", "elfs", "moms", "dads", "wife", "sons", "sins", "cake", "king", "kill", "cope", "still", "hour", "blue",
"pink", "ping", "poke", "look", "rope", "gins", "hard", "hope", "pies", "like", "slip", "goes", "girl", "boys",
"dead", "deep", "lips", "eyes", "nail", "head", "hand", "shoe", "hair", "bags", "seat", "sits", "slim", "runs",
"keys", "door", "sofa", "dear", "best", "more", "many", "mock", "opts", "pens", "rise", "rose", "path", "file"};
                                            
std::vector<std::string> get_valid_words_brute_force(std::string number, int index, std::string prefix, std::vector<std::string> valid_words)
{
    std::vector<std::string> valid_words;
    // todo: recursion
    return valid_words;
}

std::vector<std::string> get_valid_words_brute_force(std::string number)
{
    std::vector<std::string> valid_words;
    get_valid_words_brute_force(number, 0, "", valid_words);
    return valid_words;
}

std::string get_random_str()
{
    constexpr int str_size = 4;
    constexpr int numbers = 9;
    std::string str = "";
    for(int i = 0; i < str_size; i++)
    {
        str += ('1' + rand() % numbers);
    }
    return str;
}

/**
 * T9: On old cell phones, users typed on a numeric keypad and the phone would provide a list of words
 * that matched these numbers. Each digit mapped to a set of 0-4 letters. Implement an algorithm
 * to return a list of matching words, given a sequence of digits. You are provided a list of valid words
 * (provided in whatever data structure you'd like). The mapping is shown in the diagram below:
 *   1  |  2  |  3
 *      | abc | def
 * -----------------
 *   4  |  5  |  6
 *  ghi | jkl | mno
 * -----------------
 *   7  |  8  |  9    
 *  pqrs| tuv | wxyz
 * -----------------
 *      |  0  |
 * EXAMPLE:
 * Input: 8733
 * Output: tree, used
 */
int main()
{
    srand(time(NULL));
    std::string test_numbers;
    for(int i = 0; i < 100; i++)
    {
        test_numbers = get_random_str();
        get_valid_words_brute_force(test_numbers);
    }
}