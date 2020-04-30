#include <iostream>
#include <vector>
#include <queue>

class Node {
    public:
        Node() {}
        Node(std::string _name) : name(_name) {
            std::cout << "node " << name << " created\n";
            visited = false;
        }
        void add_child(const Node& node) {
            std::cout << "node " << node.name << " is added to " << "node " << name << '\n';
            children.push_back(node);
        }
        std::vector<Node> children;
        std::string name;
        bool visited;
};

class Graph {
    public:
        std::vector<Node> nodes;
        void add_node(const Node& node) {
            nodes.push_back(node);
        }
        bool get_node(const std::string& name, Node& node) {
            for(int i = 0; i < nodes.size(); i++) {
                if(nodes[i].name == name) {
                    node = nodes[i];
                    return true;
                }
            }
            return false;
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
    nodeC.add_child(nodeB);
    nodeD.add_child(nodeB);
    nodeD.add_child(nodeC);
    nodeF.add_child(nodeG);
    nodeG.add_child(nodeH);
    nodeH.add_child(nodeF);
    graph.add_node(nodeA);
    graph.add_node(nodeB);
    graph.add_node(nodeC);
    graph.add_node(nodeD);
    graph.add_node(nodeF);
    graph.add_node(nodeG);
    graph.add_node(nodeH);
    return graph;
}

bool operator==(const Node& node1, const Node& node2) {
    if(node1.name != node2.name) {
        return false;
    }
    for(int i = 0; i < node1.children.size(); i++) {
        if(&node1.children[i] != &node2.children[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Node& node1, const Node& node2) {
    return !(node1 == node2);
}

bool has_route(Node& start, Node& end) {
    if(start == end) {
        return true;
    }
    std::queue<Node> q;
    q.push(start);
    start.visited = true;
    while(!q.empty()) {
        Node tmp = q.front();
        q.pop();
        if(tmp == end) {
            return true;
        }
        for(Node child : tmp.children) {
            if(child.visited) {
                continue;
            }
            if(child == end) {
                return true;
            }
            child.visited = true;
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
    std::cout << "graph has been successfully created\n";
    Node start;
    Node end;
    if(graph.get_node("A", start) && graph.get_node("H", end)) {
        std::cout << "has route = " << has_route(start, end) << '\n';
    } else {
        std::cout << "Start and end nodes doesn't exist.\n";
    }
}