#include <iostream>
#include <vector>

class Rectangle
{
    public:
        int height = 0, length;
        std::vector<std::vector<char>> matrix;
        Rectangle() = default;
        Rectangle(int l): length(l) {}
        Rectangle(int l, int h, std::vector<std::vector<char>> letters) : length(l), height(h), matrix(letters) {}
        char get_letter(int i, int j) { return matrix[i][j]; }
};

class WordGroup
{
    public:
        static std::vector<WordGroup> create_word_groups(std::vector<std::string> words)
        {
            // todo
        }
};

class Trie
{
    public:
        Trie() = default;
        Trie(int l) : len(l) {}
        int len;
};

/**
 * Word Rectangle: Given a list of millions of words, design an algorithm to create the largest possible
 * rectangle of letters such that every row forms a word (reading left to right) and every column forms 
 * a word (reading top to bottom). The words need not be choosen consecutively from the list, but all rows
 * must be the same length and all columns must be the same height.
 */
int main()
{
    std::vector<std::string> words;
    std::vector<WordGroup> groupList = WordGroup::create_word_groups(words);
    int maxWordLen = groupList.size();
    std::vector<Trie> tries(maxWordLen);
    // todo
}