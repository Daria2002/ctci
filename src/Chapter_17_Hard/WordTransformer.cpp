#include <iostream>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
    
std::unordered_set<std::string> set_up_dict(std::vector<std::string> words)
{
    std::unordered_set<std::string> dict;
    for(std::string word : words) dict.emplace(word);
    return dict;
}

std::vector<std::string> words_one_away(std::string word)
{
    std::vector<std::string> words;
    for(int i = 0; i < word.size(); i++)
    {
        for(char c = 'A'; c <= 'Z'; c++)
        {
            std::string w = word.substr(0, i) + c + word.substr(i + 1);
            words.push_back(w);
        }
    }
    return words;
}

std::vector<std::string> transform(std::unordered_set<std::string> visited, std::string start, 
std::string end, std::unordered_set<std::string> dict)
{
    std::vector<std::string> path;
    if(start == end)
    {
        path.push_back(start);
        return path;
    }
    else if(visited.find(start) != visited.end() || dict.find(start) == dict.end())
    {
        return path; // empty
    }
    visited.emplace(start);
    std::vector<std::string> words = words_one_away(start);
    for(std::string word : words)
    {
        std::vector<std::string> path = transform(visited, word, end, dict);
        if(!path.empty())
        {
            path.push_back(start);
            return path;
        }
    }
    return path;
}

std::vector<std::string> transform_bf(std::string start, std::string end, std::vector<std::string> words)
{
    std::unordered_set<std::string> dict = set_up_dict(words);
    std::unordered_set<std::string> visited;
    return transform(visited, start, end, dict);
}

std::vector<std::string> get_wild_card_roots(std::string w)
{
    std::vector<std::string> words;
    for(int i = 0; i < w.size(); i++)
    {
        std::string word = w.substr(0, i) + "_" + w.substr(i + 1);
        words.push_back(word);
    }
    return words;
}

std::unordered_map<std::string, std::vector<std::string>> words_to_map(std::vector<std::string> words)
{
    std::unordered_map<std::string, std::vector<std::string>> word_map;
    for(std::string word : words)
    {
        std::vector<std::string> linked = get_wild_card_roots(word);
        for(std::string linked_word : linked)
        {
            word_map[linked_word].push_back(word);
        }
    }
    return word_map;
}

std::vector<std::string> get_valid_linked_words(std::string word, 
std::unordered_map<std::string, std::vector<std::string>> wild_card_to_word_vector)
{
    std::vector<std::string> wild_cards = get_wild_card_roots(word);
    std::vector<std::string> linked_words;
    for(std::string wild_card : wild_cards)
    {
        std::vector<std::string> words = wild_card_to_word_vector[wild_card];
        for(std::string linked_word : words)
        {
            if(linked_word != word) linked_words.push_back(linked_word);
        }
    }
    return linked_words;
}

std::vector<std::string> transform_optimized(std::unordered_set<std::string> visited, std::string start, 
std::string end, std::unordered_map<std::string, std::vector<std::string>> wild_card_to_word_vector)
{
    std::vector<std::string> path;
    if(start == end)
    {
        path.push_back(start);
        return path;
    }
    else if(visited.find(start) != visited.end())
    {
        return path;
    }
    visited.emplace(start);
    std::vector<std::string> words = get_valid_linked_words(start, wild_card_to_word_vector);
    for(std::string word : words)
    {
        path = transform_optimized(visited, word, end, wild_card_to_word_vector);
        if(!path.empty())
        {
            path.push_back(start);
            return path;
        }
    }
    return path;
}

std::vector<std::string> transform_optimized(std::string start, std::string end, std::vector<std::string> dict)
{
    std::unordered_map<std::string, std::vector<std::string>> wild_card_to_word_vector = words_to_map(dict);
    std::unordered_set<std::string> visited;
    return transform_optimized(visited, start, end, wild_card_to_word_vector);
}

class PathNode
{
    public:
        std::string word = "";
        PathNode* previous_node = nullptr;
        PathNode(std::string w, PathNode* previous)
        {
            word = w;
            previous_node = previous;
        }
        std::string get_word()
        {
            return word;
        }
        std::vector<std::string> collapse(bool starts_with_root)
        {
            std::vector<std::string> path;
            PathNode* node = this;
            while (node != nullptr)
            {
                if(starts_with_root)
                {
                    path.push_back(node->word);
                }
                else 
                {
                    node = node->previous_node;
                }
            }
            return path;
        }
};

class BFSData
{
    public:
        std::queue<PathNode> to_visit;
        std::unordered_map<std::string, PathNode> visited;
        BFSData() = default;
        BFSData(std::string root)
        {
            PathNode source_path(root, nullptr);
            to_visit.push(source_path);
            visited[root] = source_path;
        }
        bool is_finished()
        {
            return to_visit.empty();
        }
};

std::string search_level(std::unordered_map<std::string, std::vector<std::string>> 
wild_card_to_word_list, BFSData source_data, BFSData dest_data)
{
    // todo
}

std::vector<std::string> merge_paths(BFSData source_data, BFSData dest_data, std::string collision)
{
    PathNode end1 = source_data.visited[collision];
    PathNode end2 = dest_data.visited[collision];
    std::vector<std::string> path_one = end1.collapse(false); // forward
    std::vector<std::string> path_two = end2.collapse(true); // reverse
    std::copy(path_two.begin() + 1, path_two.end(), std::back_inserter(path_one));
    return path_one;
}

std::vector<std::string> transform_optimal(std::string start, std::string end, std::vector<std::string> dict)
{
    std::unordered_map<std::string, std::vector<std::string>> wild_card_to_word_list = words_to_map(dict);
    BFSData source_data(start);
    BFSData dest_data(end);
    while (!source_data.is_finished() && !dest_data.is_finished())
    {
        std::string collision = search_level(wild_card_to_word_list, source_data, dest_data);
        if(!collision.empty())
        {
            return merge_paths(source_data, dest_data, collision);
        }
        collision = search_level(wild_card_to_word_list, dest_data, source_data);
        if(!collision.empty())
        {
            return merge_paths(source_data, dest_data, collision);
        }
    }
    return std::vector<std::string>();
}

/**
 * Given two words of equal length that are in a dictionary, write a method to tranfsorm one word into another word
 * by changing only one letter at a time. The new word you get in each step must be in the dictionary.
 * EXAMPLE
 * Input: DAMP, LIKE
 * Output: DAMP -> LAMP -> LIMP -> LIME -> LIKE
 */
int main()
{
    std::cout << "Enter 1 to solve using bf approach, 2 to solve using optimized approach or any other number\n"
    "to solve using optimized approach:\n";
    int method;
    std::cin >> method;
    const std::string start = "DAMP";
    const std::string end = "LIKE";
    std::vector<std::string> dict = {"DAMP", "LIKE", "LAMP", "LIMP", "LIME", "LIKE", "DOOR", "LOOK", "LEFT", "LIPS", "TAKE"};
    std::vector<std::string> result;
    if(method == 1)
    {
        result = transform_bf(start, end, dict);
    }
    else if(method == 2)
    {
        result = transform_optimized(start, end, dict);
    }
    else 
    {
        result = transform_optimal(start, end, dict);
    }
    for(int i = result.size() - 1; i >= 0; i--) std::cout << result[i] << (i == 0 ? "" : " -> ");
    std::cout << '\n';
}