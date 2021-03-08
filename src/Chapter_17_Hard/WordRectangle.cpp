#include <iostream>
#include <vector>
#include "trie/Trie.hpp"
#include <algorithm>
#include <unordered_map>

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

class Rectangle
{
    public:
        int height = 0, length;
        bool initialized = false;
        std::vector<std::vector<char>> matrix;
        Rectangle() = default;
        Rectangle(int l): length(l) 
        {
            initialized = true;
        }
        Rectangle(int l, int h, std::vector<std::vector<char>> letters) : length(l), height(h), matrix(letters) 
        {
            initialized = true;
        }
        char get_letter(int i, int j) { return matrix[i][j]; }

        bool is_partial_OK(int l, Trie trie)
        {
            if(height == 0) return true;
            for(int i = 0; i < l; i++)
            {
                std::string col = get_col(i);
                if(!trie.search(col)) return false;
            }
            return true;
        }

        /**
         * Create a new rectangle by taking the rows of the current rectangle and appending s
         */
        Rectangle append(std::string s)
        {
            // todo
        }

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

Rectangle make_partial_rectangle(const int l, const int h, Rectangle rectangle, std::vector<WordGroup> group_list, std::vector<Trie>& trie_list)
{
    if(rectangle.height == h) // check if complete rectangle
    {
        if(rectangle.is_complete(l, h, group_list[h - 1])) return rectangle;
        return Rectangle();
    }
    // compare columns to trie to see if potentially valid rectangle
    if(!rectangle.is_partial_OK(l, trie_list[h - 1])) return Rectangle();
    // go through all words of the right len. Add each one to the curr partial rect, and attempt to build a rect recursively
    for(int i = 0; i < group_list[l - 1].len(); i++)
    {
        Rectangle orgPlus = rectangle.append(group_list[l - 1].get_word(i));
        // try to build a rectangle with this new, partial rectangle
        Rectangle rect = make_partial_rectangle(l, h, orgPlus, group_list, trie_list);
        if(rect.initialized)
        {
            return rect;
        }
    }
    return Rectangle();
}

/**
 * This function returns true (and changes Rectangle object) if it's possible to 
 * create rectangle of specific height and length, otherwise false.
 */
bool make_rectangle(const std::vector<WordGroup>& group_list, Rectangle& rectangle, std::vector<Trie>& trie_list, const int l, const int h)
{
    if(group_list[l - 1].len() == 0 || group_list[h - 1].len() == 0) return false;
    if(trie_list[h - 1].is_leaf)
    {
        std::vector<std::string> words = group_list[h - 1].get_words();
        trie_list[h - 1] = Trie(words);
    }
    rectangle = make_partial_rectangle(l, h, Rectangle(l), group_list, trie_list);
    return true;
}

Rectangle maxRectangle(const std::vector<WordGroup>& group_list, std::vector<Trie>& trie_list, const int maxWordLength)
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
                if(make_rectangle(group_list, rectangle, trie_list, i, j)) return rectangle;
            }
        }
    }
    return Rectangle();
}

std::vector<std::string> generate_words()
{
    std::vector<std::string> words;
    words.push_back("abc");
    words.push_back("ab");
    words.push_back("bc");
    words.push_back("cd");
    words.push_back("abcd");
    words.push_back("bcda");
    words.push_back("cdab");
    words.push_back("dabc");
    words.push_back("aaa");
    words.push_back("bbbbbbb");
    words.push_back("ccccc");
    words.push_back("d");
    words.push_back("cdcdcdcd");
    words.push_back("adbaba");
    words.push_back("ada");
    words.push_back("bab");
    return words;
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
