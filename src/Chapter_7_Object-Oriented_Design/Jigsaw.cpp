#include <iostream>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <cstdlib>

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

std::string orientation_to_str(Orientation o) {
    switch (o)
    {
    case LEFT:
        return "left";
    case RIGHT:
        return "right";
    case TOP:
        return "top";
    case BOTTOM:
        return "bottom";
    default:
        return "";
    }
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
        bool is_border_index(int location) {
            return location == 0 || location == size - 1;
        }
        bool get_matching_edge(std::shared_ptr<Edge>, std::list<std::shared_ptr<Piece>>, std::shared_ptr<Edge>&);
        void set_edge_in_solution(std::list<std::shared_ptr<Piece>>, std::shared_ptr<Edge>, int, int, Orientation);
        std::list<std::shared_ptr<Piece>> get_piece_list_to_search(std::list<std::shared_ptr<Piece>>, std::list<std::shared_ptr<Piece>>, std::list<std::shared_ptr<Piece>>, int, int);
        // find the matching piece within pieces_to_search and insert it at row, column
        bool fit_next_edge(std::list<std::shared_ptr<Piece>>, int, int);
        std::vector<std::vector<std::shared_ptr<Piece>>> get_current_solution() {
            return solution;
        }
        bool solve();
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
        bool get_matching_edge(std::shared_ptr<Edge> target_edge, std::shared_ptr<Edge>& matching_edge) {
            for(std::pair<Orientation, Edge> el : edges_map) {
                if(target_edge -> fits_with(el.second)) {
                    matching_edge = std::make_shared<Edge>(el.second);
                    return true;
                }
            }
            return false;
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

std::string piece_to_str(std::shared_ptr<Piece> piece) {
    std::vector<Orientation> orientations;
    for(int i = 0; i < Piece::num_of_edges; i++) {
        orientations.push_back(static_cast<Orientation>(i));
    }
    std::string str;
    str.append("[");
    for(Orientation o : orientations) {
        str.append(orientation_to_str(o) + ", ");
    }
    str.append("]");
    return str;
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

bool Puzzle::get_matching_edge(std::shared_ptr<Edge> target_edge, std::list<std::shared_ptr<Piece>> pieces, std::shared_ptr<Edge>& matching_edge) {
    for(std::shared_ptr<Piece> piece : pieces) {
        if(piece -> get_matching_edge(target_edge, matching_edge)) {
            return true;
        }
    }
    return false;
}

void Puzzle::set_edge_in_solution(std::list<std::shared_ptr<Piece>> pieces, std::shared_ptr<Edge> edge, int row, int column, Orientation orientation) {
    std::shared_ptr<Piece> piece = edge -> get_parent_piece();
    piece -> set_edge_as_orientation(edge, orientation);
    pieces.remove(piece);
    solution[row][column] = piece;
}

std::list<std::shared_ptr<Piece>> Puzzle::get_piece_list_to_search(std::list<std::shared_ptr<Piece>> corner_pieces, std::list<std::shared_ptr<Piece>> border_pieces, std::list<std::shared_ptr<Piece>> inside_pieces, int row, int column) {
    if(is_border_index(row) && is_border_index(column)) {
        return corner_pieces;
    } else if(is_border_index(row) || is_border_index(column)) {
        return border_pieces;
    }
    return inside_pieces;
}

// find the matching piece within pieceToSearch and insert it at row, column
bool Puzzle::fit_next_edge(std::list<std::shared_ptr<Piece>> pieces_to_search, int row, int column) {
    if(row == 0 && column == 0) {
        std::shared_ptr<Piece> piece = pieces_to_search.back();
        pieces_to_search.pop_back();
        orient_top_left_corner(piece);
        solution[0][0] = piece;
    } else {
        // get the right edge and list to match
        std::shared_ptr<Piece> piece_to_match = ((column == 0) ? solution[row - 1][0] : solution[row][column - 1]);
        Orientation orientation_to_match = column == 0 ? Orientation::BOTTOM : Orientation::RIGHT;
        Edge edge_to_match = piece_to_match -> get_edge_with_orientation(orientation_to_match);
        std::shared_ptr<Edge> edge_to_match_ptr = std::make_shared<Edge>(edge_to_match);
        // get matching edge
        std::shared_ptr<Edge> edge;
        if(!get_matching_edge(edge_to_match_ptr, pieces_to_search, edge)) {
            return false;
        }
        Orientation orientation = get_opposite(orientation_to_match);
        set_edge_in_solution(pieces_to_search, edge, row, column, orientation);
    }
    return true;
}

bool Puzzle::solve() {
    std::list<std::shared_ptr<Piece>> corner_pieces;
    std::list<std::shared_ptr<Piece>> border_pieces;
    std::list<std::shared_ptr<Piece>> inside_pieces;
    group_pieces(corner_pieces, border_pieces, inside_pieces);
    // walk through puzzle, finding the piece that joins the previous one
    for(int row = 0; row < size; row++) {
        for(int column = 0; column < size; column++) {
            std::list<std::shared_ptr<Piece>> pieces_to_search = get_piece_list_to_search(corner_pieces, border_pieces, inside_pieces, row, column);
            if(!fit_next_edge(pieces_to_search, row, column)) {
                return false;
            }
        }
    }
    return true;
}            

Edge create_random_edge(std::string str) {

}

std::vector<Edge> create_edges(std::vector<std::vector<std::shared_ptr<Piece>>> puzzle, int column, int row) {
    std::string key = column + ":" + row + ':';
    Edge left = column == 0 ? Edge(Shape::FLAT, key + "h|e") : 
                              Edge((puzzle[row][column - 1]) -> get_edge_with_orientation(Orientation::RIGHT).create_matching_edge());
    Edge top = row == 0 ? Edge(Shape::FLAT, key + "v|e") : 
                          Edge((puzzle[row - 1][column]) -> get_edge_with_orientation(Orientation::BOTTOM).create_matching_edge());
    Edge right = column == puzzle[row].size() - 1 ? Edge(Shape::FLAT, key + "h|e") : create_random_edge(key + "h");
    Edge bottom = row == puzzle.size() - 1 ? Edge(Shape::FLAT, key + "h|e") : create_random_edge(key + "v");
    std::vector<Edge> edges = {left, top, right, bottom};
    return edges;
}

std::list<std::shared_ptr<Piece>> ini_puzzle(int size) {
    std::vector<std::vector<std::shared_ptr<Piece>>> puzzle;
    for(int i = 0; i < size; i++) {
        puzzle.push_back(std::vector<std::shared_ptr<Piece>>());
    }
    for(int row = 0; row < size; row++) {
        for(int column = 0; column < size; column++) {
            std::vector<Edge> edges = create_edges(puzzle, column, row);
            puzzle[row][column] = std::make_shared<Piece>();
            puzzle[row][column] -> initialize_edges(edges);
        }
    }
    srand(time(0));
    // shuffle and rotate pieces
    std::list<std::shared_ptr<Piece>> pieces;
    for(int row = 0; row < size; row++) {
        for(int column = 0; column < size; column++) {
            int rotations = rand() % 4;
            std::shared_ptr<Piece> piece = puzzle[row][column];
            piece -> rotate_edges_by(rotations);
            int index = pieces.size() == 0 ? 0 : rand() % size;
            std::list<std::shared_ptr<Piece>>::iterator it = pieces.begin();
            for(int i = 0; i < index; i++) {
                it++;
            }
            pieces.insert(it, piece);
        }
    }
    return pieces;
}

std::string solution_to_str(std::vector<std::vector<std::shared_ptr<Piece>>> solution) {
    std::string str;
    for(int h = 0; h < solution.size(); h++) {
        for(int w = 0; w < solution[h].size(); w++) {
            std::shared_ptr<Piece> piece = solution[h][w];
            if(piece == nullptr) {
                str.append("null");
            } else {
                str.append(piece_to_str(piece));
            }
        }
    }
    return str;
}

bool validate(std::vector<std::vector<std::shared_ptr<Piece>>> solution) {
    if(solution.empty()) return false;
    for(int r = 0; r < solution.size(); r++) {
        for(int c = 0; c < solution[r].size(); c++) {
            std::shared_ptr<Piece> piece = solution[r][c];
            if(piece == nullptr) return false;
            if(c > 0) {
                std::shared_ptr<Piece> left = solution[r][c-1];
                if(!(left -> get_edge_with_orientation(Orientation::RIGHT).fits_with(piece -> get_edge_with_orientation(Orientation::LEFT)))) {
                    return false;
                }
            }
            if(c < solution[r].size() - 1) {
                std::shared_ptr<Piece> right = solution[r][c+1];
                if(!right -> get_edge_with_orientation(Orientation::LEFT).fits_with(piece -> get_edge_with_orientation(Orientation::RIGHT))) {
                    return false;
                }
            }
            if(r > 0) {
                std::shared_ptr<Piece> top = solution[r - 1][c];
                if(!(top -> get_edge_with_orientation(Orientation::BOTTOM).fits_with(piece -> get_edge_with_orientation(Orientation::TOP)))) {
                    return false;
                }
            }
            if(r < solution.size() - 1) {
                std::shared_ptr<Piece> bottom = solution[r+1][c];
                if(!(bottom->get_edge_with_orientation(Orientation::TOP).fits_with(piece -> get_edge_with_orientation(Orientation::BOTTOM)))) {
                    return false;
                }
            }
            return true;
        }
    }
}

bool test_size(int size) {
    std::list<std::shared_ptr<Piece>> pieces = ini_puzzle(size);
    Puzzle puzzle(size, pieces);
    puzzle.solve();
    std::vector<std::vector<std::shared_ptr<Piece>>> solution = puzzle.get_current_solution();
    std::cout << solution_to_str(solution);
    bool result = validate(solution);
    std::cout << result << '\n';
    return result;
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

    for(int size = 1; size < 10; size++) {
        if(!test_size(size)) {
            std::cout << "ERROR: " << size << '\n';
        }
    }
}