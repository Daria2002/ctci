#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

class LocationPair
{
    public:
        LocationPair() = default;
        LocationPair(int l1, int l2) { set_locations(l1, l2); }
        int location1, location2;
        int distance()
        {
            if(location1 == -1 || location2 == -1) return std::numeric_limits<int>::max();
            return std::abs(location1 - location2);
        }
        inline void set_locations(int loc1, int loc2)
        {
            location1 = loc1;
            location2 = loc2;
        }
        inline void set_locations(LocationPair pair)
        {
            set_locations(pair.location1, pair.location2);
        }
        void update(LocationPair pair)
        {
            if(pair.is_valid() && pair.distance() < distance()) set_locations(pair);

        }
        bool is_valid()
        {
            return location1 >= 0 && location2 >= 0;
        }
};

LocationPair find_closest_bf(std::vector<std::string> words, std::string word1, std::string word2)
{
    LocationPair best(-1, -1);
    LocationPair curr(-1, -1);
    for(int i = 0; i < words.size(); i++)
    {
        if(words[i] == word1)
        {
            curr.location1 = i;
            best.update(curr);
        }
        else if(words[i] == word2)
        {
            curr.location2 = i;
            best.update(curr);
        }
    }
    return best;
}

LocationPair find_min_distance_pair(const std::vector<int>& locations1, const std::vector<int>& locations2)
{
    int index1(0), index2(0);
    LocationPair best(-1, -1);
    LocationPair curr(-1, -1);
    while (index1 < locations1.size() && index2 < locations2.size())
    {
        curr.set_locations(locations1[index1], locations2[index2]);
        best.update(curr);
        // move smaller one because the bigger one can only increase diff between two locations
        index1 += (locations1[index1] < locations2[index2] ? 1 : 0);
        index2 += (locations1[index1] > locations2[index2] ? 1 : 0);
    }
    return best;
}

bool precomputated = false;
std::unordered_map<std::string, std::vector<int>> map_locations;

std::vector<int> get_locations(std::vector<std::string> words, const std::string& word)
{
    if(precomputated) return map_locations[word];
    for(int i = 0; i < words.size(); i++) map_locations[words[i]].push_back(i);
    precomputated = true;
    return map_locations[word];
}

LocationPair find_closest_with_precomputation(const std::vector<std::string>& words, 
const std::string& word1, const std::string& word2)
{
    std::vector<int> locations1 = get_locations(words, word1);
    std::vector<int> locations2 = get_locations(words, word2);
    return find_min_distance_pair(locations1, locations2);
}

/**
 * Word Distance: You have a large text file containing words. Given any two words, find the shortest
 * distance (in terms of number of words) between them in file. If the operation will be repeated many
 * times for the same file (but different pairs of words), can you optimize your solution?
 */
int main()
{
    std::vector<std::string> words = 
    {"hello", "love", "zoo", "life", "sea", "sun", "sea", "love", "pencil", "apple", "coffee", "water"};
    const std::string word1 = "sea";
    const std::string word2 = "love";
    std::cout << "Enter 1 to solve using brute force approach or\n"
    "any other number to solve using approach with precomputation:\n";
    int method;
    std::cin >> method;
    LocationPair closest_pair = 
    (method == 1 ? find_closest_bf(words, word1, word2) : find_closest_with_precomputation(words, word1, word2));
    if(closest_pair.is_valid())
    {
        std::cout << "Shortest difference between " << word1 << " and " << word2 << " is " << closest_pair.distance() << ".\n";
        return 0;
    }
    std::cout << "One of the words is not found.\n";
}