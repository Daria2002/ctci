#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>

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
            return " ";
        }
        std::string get_revealed_state() {
            if(is_exposed) {
                return get_real_state();
            } else if(is_guess) {
                return "B ";
            }
            return "? ";
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
        void set_numbered_cells() {
            // TODO
        }
        std::vector<std::vector<std::shared_ptr<Cell>>> cells;
        std::vector<std::shared_ptr<Cell>> bombs;
};

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
}