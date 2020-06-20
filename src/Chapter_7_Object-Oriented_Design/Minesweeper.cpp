#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <string>
#include <sstream>

class Game;
class Board;
class Cell;
class UserPlay;
class UserPlayResult;

// blank cell is a type of number cell where the number is 0
class Cell {
    public:
        Cell(int r, int c) : row(r), column(c) {}
        Cell() = default;
        void set_bomb(bool bomb) {
            is_bomb = bomb;
            num = -1;
        }
        bool flip() { // returns true if blank or num, otherwise false
            is_exposed = true;
            return !is_bomb;
        }
        bool toggle_guess() {
            if(!is_exposed) {
                is_guess = !is_guess;
            }
            return is_guess;
        }
        std::string get_real_state() {
            if(is_bomb) return "* ";
            else if(num > 0) return std::to_string(num) + " ";
            return "  "; // blank space and one space distance between consecutive columns
        }
        std::string get_revealed_state() {
            if(is_exposed) {
                return get_real_state();
            } else if(is_guess) {
                return "B ";
            }
            return "? ";
        }
        bool is_blank() {
            return num == 0;
        }
        void set_row_and_col(int r, int c) {
            row = r;
            column = c;
        }
        int column, row;
        bool is_bomb, is_exposed, is_guess;
        int num;
};

class Board {
    public:
        int n_rows, n_columns, n_bombs, num_of_unexposed;
        Board() = default;
        Board(int r, int c, int b) {
            n_bombs = b;
            n_columns = c;
            n_rows = r;
            ini_board();
            shuffle_board();
            set_numbered_cells();
            num_of_unexposed = n_rows * n_columns - n_bombs;
        }
        void ini_board() {
            for(int i = 0; i < n_rows; i++) {
                std::vector<std::shared_ptr<Cell>> row_i;
                for(int j = 0; j < n_columns; j++) {
                    row_i.push_back(std::make_shared<Cell>(i, j));
                }
                cells.push_back(row_i);
            }
            for(int i = 0; i < n_bombs; i++) {
                int r = i/n_columns;
                int c = (i - r*n_columns) % n_columns;
                bombs.push_back(cells[r][c]);
                bombs[i] -> set_bomb(true);
            }
        }
        void shuffle_board() {
            int n_cells = n_rows * n_columns;
            srand(time(0));
            for(int index1 = 0; index1 < n_cells; index1++) {
                int index2 = index1 + rand() % (n_cells - index1);
                if(index1 != index2) {
                    // get cell at index1
                    int row1 = index1 / n_columns;
                    int column1 = (index1 - row1*n_columns) % n_columns;
                    std::shared_ptr<Cell> cell1 = cells[row1][column1];
                    // get cell at index2
                    int row2 = index2 / n_columns;
                    int column2 = (index2 - row2*n_columns) % n_columns;
                    std::shared_ptr<Cell> cell2 = cells[row2][column2];
                    // swap
                    cells[row1][column1] = cell2;
                    cell2 -> set_row_and_col(row1, column1);
                    cells[row2][column2] = cell1;
                    cell2 -> set_row_and_col(row2, column2);
                }
            }
        }
        bool in_bounds(int row, int column) {
            return row >= 0 && row < n_rows && column >= 0 && column < n_columns;
        }
        void set_numbered_cells() {
            std::vector<std::vector<int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; 
            for(std::shared_ptr<Cell>& bomb : bombs) {
                int row = bomb -> row;
                int col = bomb -> column;
                for(std::vector<int>& offset : offsets) { // for every surranding cell
                    int r = row + offset[0]; // make surranding cell row
                    int c = col + offset[1]; // make surranding cell column
                    if(in_bounds(r, c)) {
                        cells[r][c] -> num++;
                    }
                }
            }
        }
        void print_board(bool show_real) {
            std::cout << "\n   ";
            for(int i = 0; i < n_columns; i++) {
                std::cout << i << " ";
            }
            std::cout << "\n  ";
            for(int i = 0; i < n_columns; i++) {
                std::cout << "--";
            }
            std::cout << '\n';
            for(int r = 0; r < n_rows; r++) {
                std::cout << r << "| ";
                for(int c = 0; c < n_columns; c++) {
                    if(show_real) {
                        std::cout << cells[r][c] -> get_real_state();
                    } else {
                        std::cout << cells[r][c] -> get_revealed_state();
                    }
                }
                std::cout << '\n';
            }
        }
        bool flip_cell(std::shared_ptr<Cell> cell) {
            if(!cell -> is_exposed && !cell -> is_guess) {
                cell -> flip();
                num_of_unexposed--;
                return true;
            }
            return false;
        }
        void expand_blank(std::shared_ptr<Cell> cell) {
            std::vector<std::vector<int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}; 
            std::list<std::shared_ptr<Cell>> to_be_explored;
            to_be_explored.push_back(cell);
            while (!to_be_explored.empty())
            {
                std::shared_ptr<Cell> current = to_be_explored.back();
                to_be_explored.pop_back();
                for(std::vector<int> offset : offsets) {
                    int r = current->row + offset[0];
                    int c = current->column + offset[1];
                    if(in_bounds(r, c)) {
                        std::shared_ptr<Cell> neighbor = cells[r][c];
                        if(flip_cell(neighbor) && neighbor->is_blank()) {
                            to_be_explored.push_back(neighbor);
                        }
                    }
                }
            }
        }
        std::shared_ptr<Cell> get_cell_at_location(std::shared_ptr<UserPlay>);
        std::shared_ptr<UserPlayResult> play_flip(std::shared_ptr<UserPlay>);
        std::vector<std::vector<std::shared_ptr<Cell>>> cells;
        std::vector<std::shared_ptr<Cell>> bombs;
};

enum GameState {
    won, lost, playing
};

class Game {
    public:
        int rows, columns, bombs;
        std::shared_ptr<Board> board;
        GameState game_state;
        Game() = default;
        Game(int r, int c, int b) : rows(r), columns(c), bombs(b) {
            game_state = GameState::playing;
        }
        bool ini() {
            if(board == nullptr) {
                board = std::make_shared<Board>(rows, columns, bombs);
                board -> print_board(true); // show real board
                return true;
            }
            return false; // already initialized
        }
        bool start() {
            if(board == nullptr) {
                ini();
            }
            return play_game();
        }
        bool play_game();
        void print_game_state() {
            if(game_state == GameState::lost) {
                board -> print_board(true);
                std::cout << "FAIL\n";
            } else if(game_state == GameState::won) {
                board -> print_board(true);
                std::cout << "WIN\n";
            } else {
                std::cout << "Number of unexposed elements: " << board -> num_of_unexposed << '\n';
                board -> print_board(false);
            }
        }
};

class UserPlayResult {
    public:
        UserPlayResult(bool sm, GameState s) : successful_move(sm), state(s) {}
        bool successful_move;
        GameState state;
};

void split(const std::string& str, std::vector<std::string>& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

class UserPlay : public std::enable_shared_from_this<UserPlay> {
    public:
        int row, col;
        bool is_guess;
        UserPlay() = default;
        UserPlay(int r, int c, bool guess) : row(r), col(c), is_guess(guess) {}
};

static std::shared_ptr<UserPlay> from_string(std::string input) {
    bool isguess = false;
    if(input.size() > 0 && input[0] == 'B') {
        isguess = true;
        input = input.substr(1);
    }
    std::vector<std::string> parts;
    split(input, parts, ' ');
    int r = std::stoi(parts[0]);
    int c = std::stoi(parts[1]);
    return std::make_shared<UserPlay>(r, c, isguess);
}

std::shared_ptr<UserPlayResult> Board::play_flip(std::shared_ptr<UserPlay> play) {
    std::shared_ptr<Cell> cell = get_cell_at_location(play);
    if(cell == nullptr) {
        return std::make_shared<UserPlayResult>(false, GameState::playing);
    }
    if(play -> is_guess) {
        bool guess_res = cell -> toggle_guess();
        return std::make_shared<UserPlayResult>(guess_res, GameState::playing);
    }
    bool res = flip_cell(cell);
    if(cell->is_bomb) {
        return std::make_shared<UserPlayResult>(res, GameState::lost);
    } else if(cell->is_blank()) {
        expand_blank(cell);
    }
    if(num_of_unexposed == 0) {
        return std::make_shared<UserPlayResult>(res, GameState::won);
    }
    return std::make_shared<UserPlayResult>(res, GameState::playing);
}

std::shared_ptr<Cell> Board::get_cell_at_location(std::shared_ptr<UserPlay> play) {
    int row = play -> row;
    int col = play -> col;
    if(!in_bounds(row, col)){
        return nullptr;
    }
    return cells[row][col];
}

bool Game::play_game() {
    print_game_state();
    std::string input;
    while (game_state == GameState::playing)
    {
        std::getline(std::cin, input);
        if(input == "exit") {
            return false;
        }
        std::shared_ptr<UserPlay> play = from_string(input);
        if(play == nullptr) {
            continue;
        }
        std::shared_ptr<UserPlayResult> result = board -> play_flip(play);
        if(result -> successful_move) {
            game_state = result -> state;
        } else {
            std::cout << "Cell (" << play -> row << ", " << play -> col << ") is not possible to flip.\n";
        }
        print_game_state();
    }
}

/**
 * Design and implement a text-based Minesweeper game. Minesweeper is the classic 
 * single-player computer game where an NxN grid has B mines (or bombs) hidden across the grid.The 
 * remaining cells are either blank or have a number behind them.The numbers reflect the number of
 * bombs in the surrounding eight cells. The user then uncovers a cell. If it is a bomb, the player loses.
 * If it is a number, the number is exposed. If it is a blank cell, this cell and all adjacent blank cells (up to
 * and including the surrounding numeric cells) are exposed. The player wins when all non-bomb cells
 * are exposed. The player can also flag certain places as potential bombs. This doesn't affect game
 * play, other than to block the user from accidentally clicking a cell that is thought to have a bomb
 * (Tip for the reader: if you're not familiar with this game, please play a few rounds online first.) 
 */
int main() {
    Game game(7, 7, 3);
    game.ini();
    game.start();
}
