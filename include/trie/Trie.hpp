#include <iostream>

#define CHAR_SIZE 128

class Trie
{
    public:
        bool is_leaf;
        Trie* character[CHAR_SIZE];

        Trie()
        {
            this -> is_leaf = false;
            for(int i = 0; i < CHAR_SIZE; i++)
            {
                this -> character[i] = nullptr;
            }
        }

        Trie(std::vector<std::string> words)
        {
            for(std::string word : words) insert(word);
        }

        void insert(std::string);
        bool search(std::string);
        bool have_children(Trie const*);
        Trie* get_child(char letter);
};

void Trie::insert(std::string key)
{
    Trie* curr = this;
    for(int i = 0; i < key.length(); i++)
    {
        if(curr -> character[key[i]] == nullptr)
        {
            curr -> character[key[i]] = new Trie();
        }
        curr = curr -> character[key[i]];
    }
    curr -> is_leaf = true;
}

bool Trie::search(std::string key)
{
    if(this == nullptr) return false;
    Trie* curr = this;
    for(int i = 0; i < key.length(); i++)
    {
        curr = curr -> character[key[i]];
        if(curr == nullptr) return false;
    }
    return curr -> is_leaf;
}

bool Trie::have_children(Trie const* curr)
{   
    for(int i = 0; i < CHAR_SIZE; i++)
    {
        if(curr -> character[i]) return true;
    }
    return false;
}

Trie* Trie::get_child(char letter)
{
    return character[letter];
}