#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, int> name_freq_bf(
    std::unordered_map<std::string, int> name_freq, 
    std::vector<std::pair<std::string, std::string>> synonyms)
{
    std::unordered_map<std::string, int> map;
    // todo
    return map;
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
}