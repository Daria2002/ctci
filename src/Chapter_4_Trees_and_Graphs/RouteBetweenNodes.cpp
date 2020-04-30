#include <iostream>
#include <vector>
#include <queue>
#include <map>

class Node {
    public:
        Node() {}
        Node(const std::string _name) : name(_name) {
            visited = false;
        }
        void add_child(Node node) {
            children.push_back(node);
        }
        template <class ...Nodes>
        void add_children(Nodes... nodes) {
            (add_child(nodes), ...);
        }
        std::vector<Node> children;
        std::string name;
        bool visited;
};

class Graph {
    public:
        std::map<std::string, Node> nodes;
        void add_node(Node node) {
            nodes[node.name] = node;
        }
        template <class ...Nodes>
        void add_nodes(Nodes... nodes) {
            (add_node(nodes), ...);
        }
        bool get_node(const std::string& name, Node& node) const {
            if(nodes.find(name) != nodes.end()) {
                node = nodes.at(name);
                return true;
            }
            return false;
        }
        void visit(const Node& node) {
            if(nodes.find(node.name) != nodes.end()) {
                nodes[node.name].visited = true;
            }
        }

        bool is_visited(const Node& node) const {
            return nodes.at(node.name).visited;
        }
};

/**
 *  A ->  B   -> F -> G
 *       ^  ^    ^    |
 *       |   \    \   ˇ
 *       C <- D      H 
 */
Graph create_graph() {
    Graph graph;
    Node nodeA("A");
    Node nodeB("B");
    Node nodeC("C");
    Node nodeD("D");
    Node nodeF("F");
    Node nodeG("G");
    Node nodeH("H");
    nodeA.add_child(nodeB);
    nodeB.add_child(nodeF);
    nodeC.add_children(nodeA, nodeB);
    nodeD.add_children(nodeB, nodeC);
    nodeF.add_child(nodeG);
    nodeG.add_child(nodeH);
    nodeH.add_child(nodeF);
    graph.add_nodes(nodeA, nodeB, nodeC, nodeD, nodeF, nodeG, nodeH);
    return graph;
}

bool operator==(const Node& node1, const Node& node2) {
    return node1.name == node2.name;
}

bool operator!=(const Node& node1, const Node& node2) {
    return !(node1 == node2);
}

bool has_route(Graph& graph, Node& start, Node& end) {
    if(start == end) {
        return true;
    }
    std::queue<Node> q;
    q.push(start);
    start.visited = true;
    while(!q.empty()) {
        Node tmp;
        graph.get_node(q.front().name, tmp);
        q.pop();
        if(tmp == end) {
            return true;
        }
        for(Node& child : tmp.children) {
            if(graph.is_visited(child)) {
                continue;
            }
            if(child == end) {
                return true;
            }
            graph.visit(child.name);
            q.push(child);
        }
    }
    return false;
}

/**
 * Given a directed graph and two nodes (S and E), design an algorithm to find out whether
 * there is a route from S to E.
 */
int main() {
    std::cout << "===================================================\n"
                 "Program to check if there is a route between nodes.\n"
                 "===================================================\n";
    Graph graph = create_graph();

    std::cout << "Created graph:\n"
                 "A ->  B   -> F -> G\n"
                 "^  ^         ^    |\n"
                 "|   \\         \\   ˇ\n"
                 "C <- D            H\n";

    Node start, end;
    std::string start_name, end_name;

    std::cout << "Enter start node name:\n";
    std::cin >> start_name;
    std::cout << "Enter end node name:\n";
    std::cin >> end_name;

    bool start_exists = graph.get_node(start_name, start);
    bool end_exists = graph.get_node(end_name, end);

    if(start_exists && end_exists) {
        std::cout << "There is " << (has_route(graph, start, end) ? "a " : "no ")
         << "root between " << start.name << " and " << end.name << ".\n";
    } else {
        std::cout << ((start_exists == false) ? "start" : "end") << "doesn't exist.\n";
    }
}