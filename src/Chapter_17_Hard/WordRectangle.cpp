#include <iostream>
#include <vector>
#include "trie/Trie.hpp"
#include <algorithm>
#include <unordered_map>

class Rectangle
{
    public:
        int height = 0, length;
        std::vector<std::vector<char>> matrix;
        Rectangle() = default;
        Rectangle(int l): length(l) {}
        Rectangle(int l, int h, std::vector<std::vector<char>> letters) : length(l), height(h), matrix(letters) {}
        char get_letter(int i, int j) { return matrix[i][j]; }

        std::string get_col(const int col_num)
        {
            std::string col = "";
            for(int i = 0; i < height; i++)
            {
                col += matrix[i][col_num];
            }
            return col;
        }

        // check if all columns are valid. All rows are already known to be valid since they were added from the dict.
        bool is_complete(int l, int h, WordGroup group_list)
        {
            if(height == h)
            {
                for(int i = 0; i < l; i++)
                {
                    std::string col = get_col(i);
                    if(!group_list.contains_word(col)) return false;
                }
                return true;
            }
            return false;
        }
};

class WordGroup
{
    public:
        std::unordered_map<std::string, bool> lookup;
        std::vector<std::string> group;
        bool contains_word(std::string s) const
        {
            return lookup.find(s) != lookup.end();
        }
        int len() const
        {
            return group.size();
        }
        std::string get_word(const int i) const
        {
            return group[i];
        }
        std::vector<std::string> get_words() const
        {
            return group;
        }
        void add_word(const std::string s)
        {
            group.push_back(s);
            lookup[s] = true;
        }
        static std::vector<WordGroup> create_word_groups(std::vector<std::string> words)
        {
            int max_word_len = 0;
            // find the length of the longest word
            for(int i = 0; i < words.size(); i++)
            {
                if(words[i].size() > max_word_len)
                {
                    max_word_len = words[i].size();
                }
            }
            std::vector<WordGroup> group_list(max_word_len);
            // group the words in the dictionary into lists of words of the same length
            for(int i = 0; i < words.size(); i++)
            {
                int word_len = words[i].size() - 1; // word len is index for a word with some len
                group_list[word_len].add_word(words[i]);
            }
            return group_list;
        }
};

/**
 * This function returns true (and changes Rectangle object) if it's possible to 
 * create rectangle of specific height and length, otherwise false.
 */
bool make_rectangle(const std::vector<WordGroup>& group_list, Rectangle& rectangle, const int i, const int j)
{
    // todo
}

Rectangle maxRectangle(const std::vector<WordGroup>& group_list, const int maxWordLength)
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
                if(make_rectangle(group_list, rectangle, i, j)) return rectangle;
            }
        }
    }
}

std::vector<std::string> generate_words()
{
    // todo
}

/**
 * Word Rectangle: Given a list of millions of words, design an algorithm to create the largest possible
 * rectangle of letters such that every row forms a word (reading left to right) and every column forms 
 * a word (reading top to bottom). The words need not be choosen consecutively from the list, but all rows
 * must be the same length and all columns must be the same height.
 */
int main()
{
    std::vector<std::string> words = generate_words();
    std::vector<WordGroup> groupList = WordGroup::create_word_groups(words);
    int maxWordLen = groupList.size();
    std::vector<Trie> tries(maxWordLen);
    // todo
}