#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <cstdlib>
#include <ctime>

class Game;
class Player;
class Piece;
class Board;
class Game;

enum Direction {
    right, left, up, down
};  

enum Color {
    white, black
};  

std::ostream& operator<<(std::ostream& os, const Color& color) {
    os << (color == Color::white ? "white" : "black");
    return os;
}

class Board {
    public:
        Board() = default;
        Board(int r, int c) : rows(r), columns(c) {
            for(int i = 0; i < r; i++) {
                std::vector<std::shared_ptr<Piece>> v;
                for(int j = 0; j < c; j++) {
                    v.push_back(nullptr);
                }
                board.push_back(v);
            }
        }
        // initialize center black and white pieces
        void initialize() {
            board[rows/2 - 1][columns/2 - 1] = std::make_shared<Piece>(Color::black);
            board[rows/2][columns/2] = std::make_shared<Piece>(Color::black);
            board[rows/2 - 1][columns/2] = std::make_shared<Piece>(Color::white);
            board[rows/2][columns/2 - 1] = std::make_shared<Piece>(Color::white);
            black_count = 2;
            white_count = 2;
        }
        bool place_color(int row, int column, Color color) {
            if(board[row][column] != nullptr) { // position is already taken
                return false;
            }
            // attempt to capture each of the four directions
            std::array<int, 4> res;
            res[0] = flip_section(row - 1, column, color, Direction::up);
            res[1] = flip_section(row + 1, column, color, Direction::down);
            res[2] = flip_section(row, column - 1, color, Direction::left);
            res[3] = flip_section(row, column + 1, color, Direction::right);
            int flipped = 0; // num of flipped pieces
            for(int r : res) {
                if(r > 0) {
                    flipped += r;
                }
            }
            if(flipped <= 0) {
                return false;
            }
            board[row][column] = std::make_shared<Piece>(color);
            update_score(color, flipped + 1);
            return true;
        }
        int get_score(Color color) {
            return color == Color::white ? white_count : black_count;
        }
        // i.e. we add one black piece and after flipping pieces that are captured
        // there are x black pieces added and x - 1 white pieces removed (replaced with black piece) 
        // x - 1 because one black piece is added on board (it's not flipped from captured white piece)
        void update_score(Color new_color, int new_pieces) {
            if(new_color == Color::black) {
                black_count += new_pieces;
                white_count -= new_pieces - 1;
                return;
            }    
            white_count += new_pieces;
            black_count -= new_pieces - 1;
        }
        int flip_section(int, int, Color, Direction);
        void print_board();
    private:
        std::vector<std::vector<std::shared_ptr<Piece>>> board;
        int black_count = 0;
        int white_count = 0;
        int rows = 0;
        int columns = 0;
};

class Game {
    public:
        Game() {
            constexpr int rows = 10;
            constexpr int columns = 10;
            board = std::make_shared<Board>(rows, columns);
            players[0] = std::make_shared<Player>(Color::black);
            players[1] = std::make_shared<Player>(Color::white);
        }
        static Game& get_instance() {
            static Game g;
            return g;
        }
        std::shared_ptr<Board> get_board() const {
            return board;
        }
    private:
        std::array<std::shared_ptr<Player>, 2> players;
        std::shared_ptr<Board> board;
};

class Player {
    public:
        Player() = default;
        Player(Color col) : color(col) {}
        int get_score() const {
            return Game::get_instance().get_board() -> get_score(color);
        }
        Color get_color() const {
            return color;
        }
        std::string get_color_str() const {
            return (color == Color::white ? "white" : "black");
        }
        bool play_piece(int, int);
    private:
        Color color;
};

inline bool operator==(const Player& p1, const Player& p2) {
    return p1.get_color() == p2.get_color();
}

class Piece {
    public:
        Piece() = default;
        Piece(Color col) : color(col) {}
        void flip() {
            color = color == Color::black ? Color::white : Color::black;
        }
        Color get_color() const {
            return color;
        }
    private:
        Color color;
};

bool Player::play_piece(int row, int column) {
    return Game::get_instance().get_board() -> place_color(row, column, get_color());
}

void Board::print_board() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(board[i][j] == nullptr) {
                std::cout << "_";
            } else if(board[i][j] -> get_color() == Color::white) {
                std::cout << "W";
            } else {
                std::cout << "B";
            }
        }
        std::cout << '\n';
    }
}

int Board::flip_section(int row, int column, Color color, Direction direction) {
    int r = 0;
    int c = 0;
    switch (direction)
    {
    case Direction::up:
        r = -1;
        break;
    case Direction::down:
        r = 1;
        break;
    case Direction::left:
        c = -1;
        break;
    case Direction::right:
        c = 1;
        break;
    default:
        break;
    }
    // out of bounds
    if(row < 0 || row >= board.size() || column < 0 || column >= board[row].size() || board[row][column] == nullptr) {
        return -1;
    }
    // same color, nothing to flip
    if(board[row][column] -> get_color() == color) {
        return 0;
    }
    int flipped = flip_section(row + r, column + c, color, direction);
    if(flipped < 0) {
        return -1;
    }
    board[row][column] -> flip();
    return flipped + 1;
}

class Location {
    public:
        Location(int r, int c) : row(r), column(c) {}
        bool is_same_as(int r, int c) {
            return row == r && column == c;
        }
        int get_row() {
            return row;
        }
        int get_column() {
            return column;
        }
    private:
        int row, column;
};

class Simulator {
    public:
        Simulator() {
            for(int i = 0; i < 10; i++) {
                for(int j = 0; j < 10; j++) {
                    Location l(i, j);
                    remaining_positions.push_back(l);
                }
            }
            players[0] = Player(Color::black);
            players[1] = Player(Color::white);
            last_player = players[1];
        }
        static Simulator& get_instance() {
            static Simulator simulator;
            return simulator;
        }
        Location get_location(int index) {
            return remaining_positions.at(index);
        }
        void remove_location(int r, int c) {
            for(int i = 0; i < remaining_positions.size(); i++) {
                if(remaining_positions[i].is_same_as(r, c)) {
                    remaining_positions.erase(remaining_positions.begin() + i);
                }
            }
        }
        void shuffle() {
            srand(time(0));
            for(int i = 0; i < remaining_positions.size(); i++) {
                int rand_index = rand() % (remaining_positions.size() - 1);
                Location rand_loc = remaining_positions[rand_index];
                Location current = remaining_positions[i];
                remaining_positions[rand_index] = current;
                remaining_positions[i] = rand_loc;
            }
        }
        bool is_over() {
            // if one of the players has no more valid moves
            // valid move = capture at least one of your opponent's pieces
            // move cannot be valid if there is no piece of black or white because to capture one of 
            // opponent's pieces there should be at least two pieces of some color (new one that shoould
            // be added on board and already existing one on the board) 
            return (players[0].get_score() == 0 || players[1].get_score() == 0);
        }
        bool play_random() {
            std::shared_ptr<Board> board = Game::get_instance().get_board();
            shuffle();
            last_player = (last_player == players[0] ? players[1] : players[0]);
            std::string col = last_player.get_color_str();
            // go through all remaining positions until piece is not set on board
            // piece is set on board if setting that piece is valid move
            // move is valid if at least one of the opponent's pieces is captured after 
            // setting a piece on board
            for(int i = 0; i < remaining_positions.size(); i++) {
                Location loc = remaining_positions[i];
                bool success = last_player.play_piece(loc.get_row(), loc.get_column());
                if(success) {
                    std::cout << "Success " << col << " move at (" << loc.get_row() << ", " << loc.get_column() << ")\n";
                    board -> print_board();
                    print_scores();
                    return true;
                }
            }
            std::cout << "Game over. No valid moves found for " << col << ".\n";
            return false;
        }
        void print_scores() {
            std::cout << "Score: " << players[0].get_color() << ": " << players[0].get_score() << ", " << 
                                      players[1].get_color() << ": " << players[1].get_score() << '\n';
        }
    private:
        std::array<Player, 2> players;
        std::vector<Location> remaining_positions;
        Player last_player;
};

/**
 * Othello is played as follows: Each Othello piece is white on one side and black on the other. 
 * When a piece is surrounded by its opponents on both the left and right sides, or both the top and bottom, it is said to be captured and its color is flippeed.
 * On your turn, you must capture at least one of your opponent's pieces.
 * The game ends when either user has no more valid moves.
 * The win is assigned to the person with the most pieces. 
 * Implement the object-oriented design for Othello.
 */
int main() {
    Game game = Game::get_instance();
    game.get_board() -> initialize();
    game.get_board() -> print_board();
    Simulator simulator = Simulator::get_instance();
    while(!simulator.is_over() && simulator.play_random()) {}
    // TODO: store results in db
}
