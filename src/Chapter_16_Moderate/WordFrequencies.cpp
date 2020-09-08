#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cstdio>
#include <vector>
#include <regex>
#include <unordered_map>

std::vector<std::string> str_to_vector_and_lower_case(const std::string& s, const std::regex& re) {
    std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
    std::sregex_token_iterator reg_end;
    std::vector<std::string> words;
    std::string tmp;
    for (; it != reg_end; ++it) {
        tmp = it -> str();
        // convert to lower case
        std::transform(tmp.begin(), tmp.end(), tmp.begin(), 
        [](unsigned char c) -> unsigned char { return std::tolower(c); });
        words.push_back(tmp);
    }
    return words;
}

std::vector<std::string> get_book() {
    std::string text = "This is a book about books. It will elaborate the main purpose of reading and "
    "scrutinize why it's better to read a book than listen a podcast.";
    std::regex re("[\\s,.]+");
    return str_to_vector_and_lower_case(text, re);
}

// The time complexity of this function is O(n) and the best conceivable runtime is O(n). 
// We can't do better than that because we must look at every word in the book
int get_frequency_single_query(const std::string& word, const std::vector<std::string>& book) {
    int count = 0;
    for(std::string str : book) if(str == word) count++;
    return count;
}

std::unordered_map<std::string, int> do_preprocessing(const std::vector<std::string>& book) {
    std::unordered_map<std::string, int> hash_table;
    for(std::string word : book) {
        if(hash_table.find(word) == hash_table.end()) {
            hash_table[word] = 0;
        }
        hash_table[word]++;
    }
    return hash_table;
}

// this approach is better if we're doing the operation repeatedly beacuse than it makes
// sense to do some preprocessing where we would use hashmap to store a words as a key and 
// a frequency as a value. The frequency of any word can be easily looked up in O(1) time.
void get_frequency_repetitive_query(const std::vector<std::string>& book, const int& number_of_queries) {
    std::unordered_map<std::string, int> hash_table = do_preprocessing(book);
    std::string word;
    for(int i = 0; i < number_of_queries; i++)
    {
        std::cout << "Enter a query word:\n", std::cin >> word;
        if(hash_table.find(word) != hash_table.end()) {
            std::cout << "The frequency of word " << word << " is " << hash_table[word] << '\n';
            continue;
        }
        std::cout << word << " has never appeared in the book.\n";
    }
}

/**
 * Word Frequencies: Design a method to find the frequency of occurrences of any given word
 * in a book. What if we were running this algorithm multiple times.
 */
int main() {
    std::vector<std::string> book = get_book();
    std::cout << "Enter 1 if you want to execute a single Query or any other number for\n"
    "executing repetitive queries.\n";
    if(std::string method; std::getline(std::cin, method) && method == "1") {
        std::string word;
        std::cout << "Enter a word to be searched:\n", std::cin >> word;
        std::cout << "The frequency of word " << word << " is " << get_frequency_single_query(word, book) << '\n';
        return 0;
    }
    int number_of_queries;
    std::cout << "Enter a number of queries:\n", std::cin >> number_of_queries;
    get_frequency_repetitive_query(book, number_of_queries);
}
