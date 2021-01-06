#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
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

std::map<std::string, int> convertToMap(
    const std::map<std::string, NameSet>& groups)
{
    std::map<std::string, int> list;
    for(const auto pair : groups)
    {
        NameSet group = pair.second;
        list[group.get_root_name()] = group.get_freq(); 
    }
    return list;
}

std::map<std::string, NameSet> construct_groups(
    const std::map<std::string, int>& name_freq)
{
    std::map<std::string, NameSet> groups;
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
    std::map<std::string, NameSet>& groups, 
    const std::vector<std::pair<std::string, std::string>>& synonyms)
{
    for(std::pair<std::string, std::string> synonym : synonyms)
    {
        std::string name1 = synonym.first;
        std::string name2 = synonym.second;
        NameSet set1 = (groups.count(name1) ? groups.at(name1) : NameSet());
        NameSet set2 = (groups.count(name2) ? groups.at(name2) : NameSet());
        if(set1 != set2 && set1.size() > 0 && set2.size() > 0)
        {
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
            // update other names that are in the same set
            for(auto& group : groups)
            {
                if(other_names.find(group.first) == other_names.end() && 
                group.second.get_root_name() == bigger.get_root_name())
                {
                    groups[group.first] = bigger;
                }
            }
        }
    }
}

std::map<std::string, int> name_freq_bf(
    std::map<std::string, int> name_freq, 
    std::vector<std::pair<std::string, std::string>> synonyms)
{
    std::map<std::string, NameSet> groups = construct_groups(name_freq);
    mergeClasses(groups, synonyms);
    return convertToMap(groups);
}

class Node
{
    public:
        Node() = default;
        Node(std::string n, int f) : name(n), freq(f) {}
        int freq;
        std::string name;
        bool visited = false;
        std::vector<Node> neighbours;
};

inline bool operator==(const Node& n1, const Node& n2)
{
    return n1.name == n2.name;
}

class Graph
{
    public:
        Graph() = default;

        void create_node(std::string name, int freq)
        {
            nodes.push_back(Node(name, freq));
        }

        void add_edge(std::string name1, std::string name2)
        {
            int i1 = -1;
            int i2 = -1;
            for(int i = 0; i < nodes.size(); i++)
            {
                if(nodes[i].name != name1 && nodes[i].name != name2) continue;
                if(i1 == -1) i1 = i;
                else 
                {
                    i2 = i;
                    break;
                }
            }
            if(i1 == -1 || i2 == -1) return;
            Node& node1 = nodes[i1];
            Node& node2 = nodes[i2];
            if(std::find(node1.neighbours.begin(), node1.neighbours.end(), node2) == node1.neighbours.end())
            {
                node1.neighbours.push_back(node2);
            }
            if(std::find(node2.neighbours.begin(), node2.neighbours.end(), node1) == node2.neighbours.end())
            {
                node2.neighbours.push_back(node1);
            }
        }

        std::vector<Node> nodes;
};

Graph construct_graph(const std::map<std::string, int>& name_freq)
{
    Graph graph;
    for(const auto entry: name_freq)
    {
        std::string name = entry.first;
        int freq = entry.second;
        graph.create_node(name, freq);
    }
    return graph;
}

void connect_edges(Graph& graph, const std::vector<std::pair<std::string, std::string>>& synonyms)
{   
    for(const auto entry : synonyms)
    {
        graph.add_edge(entry.first, entry.second);
    }
}

void update_graph(Graph& graph, const std::string& node_name)
{
    for(int i = 0; i < graph.nodes.size(); i++)
    {
        if(graph.nodes[i].name == node_name)
        {
            graph.nodes[i].visited = true;
        }
    }
}

// depth-first search to calculate total freq
// mark all nodes of this component as visited 
int get_component_freq(Node& node, Graph& graph)
{
    if(node.visited) return 0; 
    node.visited = true;
    int sum = node.freq;
    for(int i = 0; i < node.neighbours.size(); i++)
    {
        sum += node.neighbours[i].freq;
        node.neighbours[i].visited = true;
        update_graph(graph, node.neighbours[i].name);
    }
    return sum;
}

std::map<std::string, int> get_true_freq(Graph graph)
{
    std::map<std::string, int> map;
    for(Node& node : graph.nodes)
    {
        if(!node.visited)
        {
            map[node.name] = get_component_freq(node, graph);
        }
    }
    return map;
}

std::map<std::string, int> name_freq_improved(
    std::map<std::string, int> name_freq, 
    std::vector<std::pair<std::string, std::string>> synonyms)
{
    Graph graph = construct_graph(name_freq);
    connect_edges(graph, synonyms);
    std::map<std::string, int> map = get_true_freq(graph);
    return map;
}

std::map<std::string, int> get_names_freq()
{
    std::map<std::string, int> map;
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
    std::map<std::string, int> name_freq = get_names_freq();
    std::vector<std::pair<std::string, std::string>> synonyms = get_synonyms();
    std::map<std::string, int> true_name_freq = 
    (method == 1 ? name_freq_bf(name_freq, synonyms) : name_freq_improved(name_freq, synonyms));
    for(auto pair : true_name_freq)
    {
        std::cout << pair.first << " = " << pair.second << '\n';
    }
}