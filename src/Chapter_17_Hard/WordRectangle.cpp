#include <iostream>
#include <vector>
#include "trie/Trie.hpp"

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

bool make_rectangle(Rectangle rectangle, int i, int j)
{
    // todo
}

Rectangle maxRectangle(const int maxWordLength)
{
    int maxSize = maxWordLength * maxWordLength;
    Rectangle rectangle;
    for(int z = maxSize; z > 0; z--)
    {
        for(int i = 1; i <= maxWordLength; i++)
        {
            if(z % i) continue;
            int j = z / i;
            if(j <= maxWordLength)
            {
                if(make_rectangle(rectangle, i, j)) return rectangle;
            }
        }
    }
}

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