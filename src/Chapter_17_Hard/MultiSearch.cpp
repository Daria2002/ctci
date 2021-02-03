#include <iostream>
#include <unordered_map>
#include <vector>

inline bool is_substr_at_index(const std::string& big, const std::string& small, const int index)
{
    return (big.substr(index, small.size()) == small);
}

std::vector<int> get_indices(const std::string& str, const std::string& word)
{
    std::vector<int> indices;
    for(int index = 0; index < str.size() - word.size() + 1; index++)
    {
        if(is_substr_at_index(str, word, index)) indices.push_back(index);
    }
    return indices;
}

std::unordered_map<std::string, std::vector<int>> multi_search1(const std::string& big_word, const std::vector<std::string>& small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    for(const std::string small_word : small_words) map[small_word] = get_indices(big_word, small_word);
    return map;
}

class TrieNode
{
    public:
        std::unordered_map<char, TrieNode*> children;
        std::vector<int> indices;

        TrieNode() = default;

        std::vector<int> search(std::string str)
        {
            if(str.empty()) return indices;
            char first = str[0];
            if(children.find(first) != children.end())
            {
                std::string rem = str.substr(1);
                return children[first]->search(rem);
            }
            return std::vector<int>();
        }

        void insert(const std::string& str, const int index)
        {
            indices.push_back(index);
            if(str.size() > 0)
            {
                char val = str.at(0);
                TrieNode* child = new TrieNode();
                if(children.find(val) != children.end())
                {
                    child = children[val];
                }
                else
                {
                    children.emplace(val, child);
                }
                std::string rem = str.substr(1);
                child -> insert(rem, index + 1);
            }
            else 
            {
                children['\0'] = nullptr;
            }
        }
};

class Trie 
{
    public:
        TrieNode root;

        Trie() = default;

        std::vector<int> search(std::string str)
        {
            return root.search(str);
        }

        Trie(const std::string& str) 
        {
            insert(str, 0);
        }

        void insert(std::string str, int index)
        {
            root.insert(str, index);   
        }
};

Trie create_trie_from_string(const std::string& str)
{
    Trie t;
    for(int i = 0; i < str.size(); i++) t.insert(str.substr(i), i);
    return t;
}

void adjust_index_start(std::vector<int>& indices, const int delta)
{
    for(int i = 0; i < indices.size(); i++) indices[i] = indices[i] - delta;
}

std::unordered_map<std::string, std::vector<int>> multi_search2(const std::string& str, const std::vector<std::string>& small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    Trie t = create_trie_from_string(str);
    for(std::string small_word : small_words)
    {
        std::vector<int> indices = t.search(small_word); 
        // search function returns index of the \0 so indices need to be substracted with small word size 
        adjust_index_start(indices, small_word.size());
        map[small_word] = indices; 
    }
    return map;
}

Trie create_trie_from_small_words(const std::vector<std::string>& small_words, const int max_len)
{
    Trie t;
    for(int i = 0; i < small_words.size(); i++) 
    {
        if(small_words[i].size() <= max_len) t.insert(small_words[i], i);
    }
    return t;
}

std::vector<std::string> find_strings_at_loc(TrieNode root, std::string str, const int start)
{
    std::vector<std::string> strings;
    int i = 1;
    TrieNode* tmp = root.children[str[start]];
    while (i < str.size())
    {
        if(tmp == nullptr) break;
        if(tmp->children.find('\0') != tmp->children.end()) strings.push_back(str.substr(start, i));
        tmp = tmp -> children[str[start + i]];
        i++;
    }
    return strings;
}

void insert_into_map(const std::vector<std::string> strings, std::unordered_map<std::string, std::vector<int>>& map, const int i)
{
    for(auto str : strings) map[str].push_back(i);
}

std::unordered_map<std::string, std::vector<int>> multi_search3(const std::string& str, const std::vector<std::string>& small_words)
{
    std::unordered_map<std::string, std::vector<int>> map;
    Trie t = create_trie_from_small_words(small_words, str.size());
    TrieNode root = t.root;
    for(int i = 0; i < str.size(); i++)
    {
        std::vector<std::string> strings = find_strings_at_loc(root, str, i);
        insert_into_map(strings, map, i);
    }
    return map;
}

/**
 * Multi Search: Given a string b and an array of smaller strings T, design a method to search
 * b for each small string in T. Return a mapping of each string to a list of its locations.
 */
int main()
{
    int method;
    std::cout << "Enter 1 for solution #1, 2 for solution #2 or any other number for solution #3:\n";
    std::cin >> method; // todo: uncomment this line and delete the next one
    std::string str = "mississippi";
    std::vector<std::string> small_words = {"is", "ppi", "hi", "sis", "i", "ssippi"};
    std::unordered_map<std::string, std::vector<int>> str_location;
    if(method == 1)
    {
        str_location = multi_search1(str, small_words);
    }
    else if(method == 2)
    {
        str_location = multi_search2(str, small_words);
    }
    else
    {
        str_location = multi_search3(str, small_words);
    }
    for(auto pair : str_location) 
    {
        std::cout << pair.first << ": ";
        std::vector<int> indices = pair.second;
        for(int index : indices) std::cout << index << ", ";
    }
    std::cout << '\n';
}