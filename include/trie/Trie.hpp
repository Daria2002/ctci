#include <iostream>

#define ALPHABET_SIZE 26

class Trie
{
    public:
        bool is_leaf;
        bool is_ini = false;
        Trie* character[ALPHABET_SIZE];

        Trie()
        {
            is_leaf = false;
            for(int i = 0; i < ALPHABET_SIZE; i++)
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
        static Trie* get_node();
};

Trie* Trie::get_node()
{
    Trie* t = new Trie;
    t->is_leaf = false;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        t->character[i] = nullptr;
    }
    return t;
}

void Trie::insert(std::string key)
{
    Trie* curr = this;
    for(int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if(curr -> character[index] == nullptr)
        {
            curr -> character[index] = get_node();
        }
        curr = curr -> character[index];
    }
    if(curr == nullptr)
    {
        std::cout << "curr = nullptr\n"; 
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
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(curr -> character[i]) return true;
    }
    return false;
}

Trie* Trie::get_child(char letter)
{
    return character[letter];
}