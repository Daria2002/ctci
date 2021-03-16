#include <iostream>

#define CHAR_SIZE 128

class Trie
{
    public:
        bool is_leaf;
        bool is_ini = false;
        Trie* character[CHAR_SIZE];

        Trie()
        {
            is_leaf = false;
            for(int i = 0; i < CHAR_SIZE; i++)
            {
                character[i] = nullptr;
            }
        }

        Trie(std::vector<std::string> words)
        {
            Trie();
            for(std::string word : words) insert(word);
            is_ini = true;
        }

        void insert(std::string);
        bool search(std::string);
        bool have_children(Trie const*);
        Trie* get_child(char letter);
};

void Trie::insert(std::string key)
{
    Trie* curr = new Trie();
    curr = this;
    for(int i = 0; i < key.length(); i++)
    {
        if(curr -> character[key[i]] == nullptr)
        {
            curr -> character[key[i]] = new Trie();
        }
        curr = curr -> character[key[i]];
    }
    curr -> is_leaf = true;
    delete curr;
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