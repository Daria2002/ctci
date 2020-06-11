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
        void group_pieces(std::list<std::shared_ptr<Piece>>&, std::list<std::shared_ptr<Piece>>&, std::list<std::shared_ptr<Piece>>&);
        // orient this corner piece so that it's flat edges are on the top left
        void orient_top_left_corner(std::shared_ptr<Piece>);
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
        Edge() = default;
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

inline bool operator==(const Edge& e1, const Edge& e2) { return e1.get_code() == e2.get_code(); }

class Piece : public std::enable_shared_from_this<Piece> {
    public:
        void initialize_edges(std::vector<Edge> edges) {
            std::vector<Orientation> orientations;
            for(int i = 0; i < edges.size(); i++) {
                Edge edge = edges[i];
                edge.set_parent_piece(shared_from_this());
                edges_map[static_cast<Orientation>(i)] = edge;
            }
        }
        // set edge in the appropriate orientation, rotating the piece as necessary
        void set_edge_as_orientation(std::shared_ptr<Edge> edge, Orientation orientation) {
            Orientation current_orientation = get_orientation(edge);
            rotate_edges_by(static_cast<std::size_t>(orientation) - static_cast<std::size_t>(current_orientation));
        }
        Orientation get_orientation(std::shared_ptr<Edge> edge) {
            for(std::pair<Orientation, Edge> el : edges_map) {
                if(el.second.get_code() == edge -> get_code()) {
                    return el.first;
                }
            }
        }
        void rotate_edges_by(std::size_t num_of_rotations) {
            std::vector<Orientation> orientations;
            for(int i = 0; i < num_of_edges; i++) {
                orientations.push_back(static_cast<Orientation>(i));
            }
            std::unordered_map<Orientation, Edge, KeyHash, KeyEqual> after_rotation;
            num_of_rotations %= num_of_edges;
            if(num_of_rotations < 0) num_of_rotations += num_of_edges;
            for(int i = 0; i < orientations.size(); i++) {
                Orientation old_orientation = orientations[(i - num_of_rotations + num_of_edges) % num_of_edges];
                Orientation new_orientation = orientations[i];
                after_rotation[new_orientation] = edges_map[old_orientation];
            }
            edges_map = after_rotation;
        }
        bool is_corner() {
            std::vector<Orientation> orientations;
            for(int i = 0; i < num_of_edges; i++) {
                orientations.push_back(static_cast<Orientation>(i));
            }
            for(int i = 0; i < orientations.size(); i++) {
                Shape current = edges_map[orientations[i]].get_shape();
                Shape next = edges_map[orientations[(i + 1) % num_of_edges]].get_shape();
                if(current == Shape::FLAT && next == Shape::FLAT) {
                    return true;
                }
            }
            return false;
        }
        bool is_border() {
            std::vector<Orientation> orientations;
            for(int i = 0; i < num_of_edges; i++) {
                orientations.push_back(static_cast<Orientation>(i));
            }
            for(int i = 0; i < orientations.size(); i++) {
                if(edges_map[orientations[i]].get_shape() == Shape::FLAT) {
                    return true;
                }
            }
            return false;
        }
        Edge get_edge_with_orientation(Orientation orientation) {
            return edges_map[orientation];
        }
        Edge get_matching_edge(Edge target_edge) {
            for(std::pair<Orientation, Edge> el : edges_map) {
                if(target_edge.fits_with(el.second)) {
                    return el.second;
                }
            }
        }
        static constexpr int num_of_edges = 4;
        std::unordered_map<Orientation, Edge, KeyHash, KeyEqual> edges_map;
};

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << edge.get_code();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
    std::vector<Orientation> orientations;
    for(int i = 0; i < Piece::num_of_edges; i++) {
        orientations.push_back(static_cast<Orientation>(i));
    }
    std::string str;
    os << "[";
    for(Orientation o : orientations) {
        os << o;
        os << ", ";
    }
    os << "]";
    return os;
}

void Puzzle::orient_top_left_corner(std::shared_ptr<Piece> piece) {
    if(!piece -> is_corner()) return;
    std::vector<Orientation> orientations;
    for(int i = 0; i < 4; i++) {
        orientations.push_back(static_cast<Orientation>(i));
    }
    for(int i = 0; i < orientations.size(); i++) {
        std::shared_ptr<Edge> current = std::make_shared<Edge>(piece -> get_edge_with_orientation(orientations[i]));
        std::shared_ptr<Edge> next = std::make_shared<Edge>(piece -> get_edge_with_orientation(orientations[i]));
        if(current -> get_shape() == Shape::FLAT && next -> get_shape() == Shape::FLAT) {
            piece -> set_edge_as_orientation(current, Orientation::LEFT);
            return;
        }
    }
}

void Puzzle::group_pieces(std::list<std::shared_ptr<Piece>>& corner_pieces, std::list<std::shared_ptr<Piece>>& border_piece, std::list<std::shared_ptr<Piece>>& inside_pieces) {
    for(std::shared_ptr<Piece> piece : unsorted_pieces) {
        if(piece -> is_corner()) {
            corner_pieces.push_back(piece);
        } else if(piece -> is_border()) {
            border_piece.push_back(piece);
        } else {
            inside_pieces.push_back(piece);
        }
    }
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