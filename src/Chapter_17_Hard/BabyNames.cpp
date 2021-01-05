#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

class NameSet
{
    public:
        NameSet() = default;
        NameSet(std::string root, int frequency) : root_name(root), freq(frequency) 
        {
            names.insert(root);
        }

        std::string get_root_name() const
        {
            return root_name;
        }

        int get_freq() const
        {
            return freq;
        }  

        int size() const
        {
            return names.size();
        }

        std::unordered_set<std::string> get_names() const
        {
            return names;
        }

        void copy_names_with_freq(std::unordered_set<std::string> other_names, int frequency)
        {
            freq += frequency;
            names.insert(other_names.begin(), other_names.end());
        }
    private:
        std::unordered_set<std::string> names;
        int freq = 0;
        std::string root_name; 
};

inline bool operator==(const NameSet& set1, const NameSet& set2) { 
    return set1.get_root_name() == set2.get_root_name();
}

inline bool operator!=(const NameSet& set1, const NameSet& set2) { 
    return !(set1 == set2);
}

std::unordered_map<std::string, int> convertToMap(
    const std::unordered_map<std::string, NameSet>& groups)
{
    std::unordered_map<std::string, int> list;
    for(const auto pair : groups)
    {
        NameSet group = pair.second;
        list[group.get_root_name()] = group.get_freq(); 
    }
    return list;
}

std::unordered_map<std::string, NameSet> construct_groups(
    const std::unordered_map<std::string, int>& name_freq)
{
    std::unordered_map<std::string, NameSet> groups;
    for(const auto pair : name_freq)
    {
        std::string name = pair.first;
        int freq = pair.second;
        NameSet group(name, freq);
        groups[name] = group;
    }
    return groups;
}

void mergeClasses(
    std::unordered_map<std::string, NameSet>& groups, 
    const std::vector<std::pair<std::string, std::string>>& synonyms)
{
    for(auto group : groups)
    {
        std::cout << "group name = " << group.first << '\n';
        std::cout << "group size = " << group.second.size() << '\n';
    }
    for(std::pair<std::string, std::string> synonym : synonyms)
    {
        std::string name1 = synonym.first;
        std::cout << "name1 = " << name1 << '\n';
        std::string name2 = synonym.second;
        std::cout << "name2 = " << name2 << '\n';
        NameSet set1 = (groups.count(name1) ? groups.at(name1) : NameSet());
        NameSet set2 = (groups.count(name2) ? groups.at(name2) : NameSet());
        if(set1 != set2 && set1.size() > 0 && set2.size() > 0)
        {
            std::cout << "merge\n";
            // merge smaller set into the bigger one
            NameSet smaller = (set2.size() < set1.size() ? set2 : set1);
            NameSet bigger = (set2.size() < set1.size() ? set1 : set2);
            // merge lists
            std::unordered_set<std::string> other_names = smaller.get_names();
            int freq = smaller.get_freq();
            bigger.copy_names_with_freq(other_names, freq);
            // update mapping
            for(std::string name : other_names)
            {
                groups[name] = bigger;
            }
        }
        else 
        {
            std::cout << "cannot merge\n";
        }
    }
    std::cout << "after\n";
    for(auto group : groups)
    {
        std::cout << "group name = " << group.first << '\n';
        std::cout << "group size = " << group.second.size() << '\n';
    }
}

std::unordered_map<std::string, int> name_freq_bf(
    std::unordered_map<std::string, int> name_freq, 
    std::vector<std::pair<std::string, std::string>> synonyms)
{
    std::unordered_map<std::string, NameSet> groups = construct_groups(name_freq);
    mergeClasses(groups, synonyms);
    return convertToMap(groups);
}

std::unordered_map<std::string, int> name_freq_improved(
    std::unordered_map<std::string, int> name_freq, 
    std::vector<std::pair<std::string, std::string>> synonyms)
{
    std::unordered_map<std::string, int> map;
    // todo
    return map;
}

std::unordered_map<std::string, int> get_names_freq()
{
    std::unordered_map<std::string, int> map;
    map["John"] = 15;
    map["Jon"] = 12; 
    map["Chris"] = 13;
    map["Kris"] = 4; 
    map["Christopher"] = 19;
    return map;
}

std::vector<std::pair<std::string, std::string>> get_synonyms()
{
    std::vector<std::pair<std::string, std::string>> synonyms = 
    {
        std::make_pair("Jon", "John"),
        std::make_pair("John", "Johnny"),
        std::make_pair("Chris", "Kris"),
        std::make_pair("Chris", "Christopher")
    };
    return synonyms;
}

/**
 * Baby Names: Each year, the government releases a list of the 10,000 most common baby names
 * and their frequencies (the number of babies with that name). The only problem with this is that 
 * same names have multiple spellings. For example, "John" and "Jon" are essentially the same name
 * but would be listed separately in the list. Given two lists, one of names/frequencies and the other
 * of pairs equivalent names, write an algorithm to print a new list of the true frequency of each
 * name. Note that if John and Jon are synonyms, and Jon and Johnny are synonyms, then John and 
 * Johnny are synonyms. (It is both transative and symmetric). In the final list, any name can be used
 * at the "real" name.
 * EXAMPLE:
 * Input:
 *  Names: John(15), Jon(12), Chris(13), Kris(4), Christopher(19)
 *  Synonyms: (Jon, John), (John, Johnny), (Chris, Kris), (Chris, Christopher)
 * Output: John(27), Kris(36) 
 */
int main()
{
    std::cout << "Enter 1 to solve using brute force or any other number for improved approach:\n";
    int method;
    std::cin >> method;
    std::unordered_map<std::string, int> name_freq = get_names_freq();
    std::vector<std::pair<std::string, std::string>> synonyms = get_synonyms();
    std::unordered_map<std::string, int> true_name_freq = 
    (method == 1 ? name_freq_bf(name_freq, synonyms) : name_freq_improved(name_freq, synonyms));
    for(auto pair : true_name_freq)
    {
        std::cout << pair.first << " = " << pair.second << '\n';
    }
}