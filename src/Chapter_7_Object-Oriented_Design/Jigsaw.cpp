#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

// every edge has orientation
// i.e. puzzle has 4 edges and each one of those has different orientation
// one is on the left, one on top, one on right and the last one on bottom
enum Orientation {
    LEFT, TOP, RIGHT, BOTTOM
};

Orientation get_opposite(const Orientation& orientation) {
    switch (orientation)
    {
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
        case TOP: return BOTTOM;
        case BOTTOM: return TOP;
    }
    return TOP;
}

enum Shape {
    INNER, OUTER, FLAT
};

Shape get_opposite(const Shape& shape) {
    switch (shape)
    {
        case INNER: return OUTER;
        case OUTER: return INNER;
    }
    return INNER;
}

class Puzzle;
class Piece;
class Edge;

class Puzzle {
    public:
        Puzzle(int n, std::list<std::shared_ptr<Piece>> pieces) : size(n), unsorted_pieces(pieces) {
            initialize_solution_matrix();
        }
        // put piece in the solution, turn it appropriately, and remove from list
        void set_edge_in_solution(std::shared_ptr<Edge> edge, int row, int column, Orientation orientation) {
            return;
        }
    private:
        void initialize_solution_matrix() {
            for(int i = 0; i < size; i++) {
                solution.push_back(std::vector<std::shared_ptr<Piece>>());
            }
        }
        std::vector<std::vector<std::shared_ptr<Piece>>> solution;
        int size;
        std::list<std::shared_ptr<Piece>> unsorted_pieces;
};

struct KeyHash {
    std::size_t operator()(const Orientation& k) const
    {
        std::string str;
        switch (k)
        {
        case BOTTOM:
            str = "bottom";
            break;
        case TOP:
            str = "top";
            break;
        case LEFT:
            str = "left";
            break;
        case RIGHT:
            str = "right";
            break;
        default:
            str = "ini";
            break;
        }
        return std::hash<std::string>()(str);
    }
};
 
struct KeyEqual {
    bool operator()(const Orientation& lhs, const Orientation& rhs) const
    {
        return lhs == rhs;
    }
};


class Edge {
    public:
        Edge(Shape s, std::string c) : shape(s), code(c) {}
        std::string get_code() const {
            return code;
        }
        Edge create_matching_edge() {
            return Edge(get_opposite(shape), get_code());
        }
        bool fits_with(Edge edge) const {
            return edge.get_code() == get_code();
        }
        void set_parent_piece(std::shared_ptr<Piece> parent) {
            parent_piece = parent;
        }
        std::shared_ptr<Piece> get_parent_piece() const {
            return parent_piece;
        }
        Shape get_shape() const {
            return shape;
        }
    private:
        Shape shape;
        std::shared_ptr<Piece> parent_piece;
        std::string code;
};

class Piece {
    public:
        void set_edge_as_orientation(std::shared_ptr<Edge> edge, Orientation orientation) {
            return;
        }
    
    private:
        static const int num_of_edges = 4;
        std::unordered_map<Orientation, Edge, KeyHash, KeyEqual> edges;
};

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << edge.get_code();
    return os;
}

/**
 * Implement and NxN jigsaw puzzle. Design the data structure and explain
 * an algorithm to solve the puzzle. You can assume that you have a fitsWith
 * method which, when passed two puzzle edges, returns true if the two edges 
 * belong together.
 */
int main() {
    std::cout << "=============\n"
                 "Jigsaw solver\n"
                 "=============\n";
}