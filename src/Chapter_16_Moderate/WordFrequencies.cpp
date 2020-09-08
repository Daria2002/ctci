#include <iostream>
#include <sstream>
#include <string>

std::string get_book() {
    return "This is a book about books. It will elaborate the main purpose of reading and "
    "scrutinize why it's better to read a book than listen a podcast.";
}

int get_frequency_single_query(std::string word, std::string book) {
    // TODO
    return 1;
}

int get_frequency_repetitive_query(std::string word, std::string book) {
    // TODO
    return 2;
}

/**
 * Word Frequencies: Design a method to find the frequency of occurrences of any given word
 * in a book. What if we were running this algorithm multiple times.
 */
int main() {
    std::cout << "Enter 1 to solve this problem using Single Query or any other number for\n"
    "Repetitive Queries approach.\n";
    std::cout << "Enter a word to be searched\n";
    std::string word;
    std::string book = get_book();
    int freq;
    std::cin >> word;
    if(std::string method; std::getline(std::cin, method) && method == "1") {
        freq = get_frequency_single_query(word, book);
    } else {
        freq = get_frequency_repetitive_query(word, book);
    }
    std::cout << "The frequency of word " << word << " is " << freq << '\n';
}