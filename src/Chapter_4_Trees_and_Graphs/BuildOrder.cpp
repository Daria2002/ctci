#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#include <algorithm>
#include <sstream>

class Project {
    public:
        Project() {}
        Project(std::string _name) : name(_name) {}
        std::string name;
        void add_child(const Project& project) {
            children.push_back(project);
            dependencies_to_be_build++;
        }
        std::vector<Project> children;
        int dependencies_to_be_build = 0;
};

class Graph {
    public:
        std::vector<Project> nodes;
        std::map<std::string, Project> map_nodes;
        void add_node(const Project project) {
            nodes.push_back(project);
            map_nodes[project.name] = project;
        }
        Project get_node(const std::string& node_name) {
            return map_nodes[node_name];
        }
};

std::vector<std::string> separate_string(std::string str, const std::string& regex) {
    std::vector<std::string> values;
    std::size_t pos = 0;
    std::string token;
    while ((pos = str.find(regex)) != std::string::npos) {
        token = str.substr(0, pos);
        values.push_back(token);
        str = str.substr(pos + regex.length());
    }
    values.push_back(str); // last element
    return values;
}

std::vector<std::pair<std::string, std::string>> make_dependency_pairs(std::vector<std::string> dependencies) {
    std::vector<std::pair<std::string, std::string>> pairs;
    std::for_each(dependencies.begin(), dependencies.end(), [&](auto el) {
        std::vector<std::string> values = separate_string(el, ", ");
        pairs.push_back(std::make_pair(values[0], values[1]));
    });
    return pairs;
}

bool get_child(std::vector<std::pair<std::string, std::string>> dependency_pairs, const std::string& parent, std::string& child) {
    auto it = std::find_if(dependency_pairs.begin(), dependency_pairs.end(), 
    [&](const std::pair<std::string, std::string>& pair) {
        if(pair.first == parent) {
            child = pair.second;
            return true;
        }
    });
    return it != dependency_pairs.end();
}

Graph build_graph(std::string project_names, std::string project_dependencies) {
    Graph graph;
    std::vector<std::string> names = separate_string(project_names, ", ");
    std::vector<std::string> dependencies = separate_string(project_dependencies.substr(1, project_dependencies.size() - 2), "), (");
    std::vector<std::pair<std::string, std::string>> dependency_pairs = make_dependency_pairs(dependencies);
    
    std::for_each(names.begin(), names.end(), [&](std::string name) {
        Project project(name);
        graph.add_node(project);
    });

    std::for_each(graph.nodes.begin(), graph.nodes.end(), [&](auto& project) {
        if(std::string child; get_child(dependency_pairs, project.name, child)) {
            project.add_child(graph.map_nodes[child]);
        }
    });

    return graph;
}

Graph get_graph(const std::string& input_file) {
    std::ifstream file(input_file);
    std::string project_names;
    std::string project_dependencies;
    std::getline(file, project_names);
    std::getline(file, project_dependencies);
    return build_graph(project_names, project_dependencies);
}

std::vector<Project> get_build_order(const Graph& graph) {
    std::vector<Project> build_order;

    return build_order;
}

void print_build_order(const std::vector<Project>& build_order) {
    std::cout << "build order:\n";
    for(int i = 0; i < build_order.size(); i++) {
        std::cout << build_order[i].name;
        if(i != build_order.size() - 1) {
            std::cout << ", ";
        } else {
            std::cout << '\n';
        }
    }
}

/**
 * You are given a list of projects and a list of dependencies (which is a list of pairs of projects, 
 * where the second project is dependent on the first project). All of a project's dependencies must be
 * built before the project is. Find a build order that will allow the projects to be built. If there is
 * no valid build order, return error.
 * EXAMPLE:
 * Input:
 *  projects: a, b, c, d, e, f
 *  dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
 * Output: f, e, a, b, d, c
 */
int main(int argc, char** argv) {
    Graph graph = get_graph(argv[1]);
    std::vector<Project> build_order = get_build_order(graph);
    print_build_order(build_order);
}