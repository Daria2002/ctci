#include <iostream>
#include <vector>
#include <unordered_set>

class Position
{
    public:
        int row, column;
        Position(int r, int c) : row(r), column(c) {}
        Position() = default;
};

inline bool operator==(const Position& p1, const Position& p2)
{
    return p1.column == p2.column && p1.row == p2.row;
}

enum Orientation
{
    left, up, right, down
};

Orientation get_turn(const Orientation& o, const bool clockwise)
{
    if(o == Orientation::left) return clockwise ? Orientation::up : Orientation::down;
    else if(o == Orientation::right) return clockwise ? Orientation::down : Orientation::up;
    else if(o == Orientation::up) return clockwise ? Orientation::right : Orientation::left;
    else if(o == Orientation::down) return clockwise ? Orientation::left : Orientation::right;
}

std::string orientation_to_str(const Orientation& o)
{
    if(o == Orientation::left) return "<";
    else if(o == Orientation::right) return ">";
    else if(o == Orientation::up) return "^";
    else if(o == Orientation::down) return "ˇ";
}

class Ant
{
    public:
        Position position = Position(0, 0);
        Orientation orientation = Orientation::right; 

        void turn(const bool clockwise)
        {
            orientation = get_turn(orientation, clockwise);
        }

        void move()
        {
            if(orientation == Orientation::left)
            {
                position.column--;
            } 
            else if(orientation == Orientation::right)
            {
                position.column++;
            } 
            else if(orientation == Orientation::down)
            {
                position.row++;
            } 
            else if(orientation == Orientation::up)
            {
                position.row--;
            }
        }

        void adjust_position(const int shift_row, const int shift_column)
        {
            position.row += shift_row;
            position.column += shift_column;
        }
};

class Grid
{
    public:
        // white - false, black - true
        std::vector<std::vector<bool>> grid;
        Ant ant;

        Grid()
        {
            grid = std::vector<std::vector<bool>> { std::vector<bool> { false } };
        }

        void copyWithShift(const std::vector<std::vector<bool>>& old_grid,
        std::vector<std::vector<bool>>& new_grid, const int shift_row, const int shift_column) const
        {
            for(int r = 0; r < old_grid.size(); r++)
            {
                for(int c = 0; c < old_grid[0].size(); c++)
                {
                    new_grid[r + shift_row][c + shift_column] = old_grid[r][c];
                }
            }
        }

        void ensure_fit(const Position& position)
        {
            int shift_row = 0;
            int shift_column = 0;
            // calculate new number of rows
            int num_rows = grid.size();
            if(position.row < 0)
            {
                shift_row = num_rows;
                num_rows *= 2;
            }
            else if(position.row >= num_rows)
            {
                num_rows *= 2;
            }
            int num_columns = grid[0].size();
            // calculate new number of columns
            if(position.column < 0)
            {
                shift_column = num_columns;
                num_columns *= 2;
            }
            else if(position.column >= num_columns)
            {
                num_columns *= 2;
            }
            // grow array and shift ant's position, if necessary
            if(num_rows != grid.size() || num_columns != grid[0].size())
            {
                std::vector<std::vector<bool>> new_grid;
                // initialize new_grid
                for(int r = 0; r < num_rows; r++)
                {
                    std::vector<bool> row;
                    for(int c = 0; c < num_columns; c++)
                    {
                        row.push_back(false);
                    }
                    new_grid.push_back(row);
                }
                copyWithShift(grid, new_grid, shift_row, shift_column);
                ant.adjust_position(shift_row, shift_column);
                grid = new_grid;
            }
        }

        void flip(const Position& position)
        {
            grid[position.row][position.column] = grid[position.row][position.column] ? false : true;
        }

        void move()
        {
            ant.turn(!grid[ant.position.row][ant.position.column]);
            flip(ant.position);
            ant.move();
            ensure_fit(ant.position);
        }

        void print() const
        {
            for(int r = 0; r < grid.size(); r++)
            {
                for(int c = 0; c < grid[0].size(); c++)
                {
                    if(r == ant.position.row && c == ant.position.column)
                    {
                        std::cout << orientation_to_str(ant.orientation);
                    }
                    else
                    {
                        std::cout << (grid[r][c] ? 'B' : 'W');
                    }
                }
                std::cout << '\n';
            }
        }
};

void printKMovesResizableArray(const int K)
{
    Grid grid;
    for(int i = 0; i < K; i++)
    {
        std::cout << "K = " << i << '\n';
        grid.print();
        grid.move();
        std::cout << '\n';
    }
}

struct Hash
{
    std::size_t operator()(const Position& position) const
    {
        return position.row * position.column;
    }
};

class Board
{
    public: 
        std::unordered_set<Position, Hash> black_cells;
        Ant ant;
        Position top_left = Position(0, 0);
        Position bottom_right = Position(0, 0);

        void move()
        {
            ant.turn(!is_black(ant.position));
            flip(ant.position);
            ant.move();
            ensure_fit(ant.position);
        }

        void flip(const Position& position)
        {
            // if black, remove from black set, otherwise add in black set
            if(is_black(position))
            {
                black_cells.erase(black_cells.find(position));
            }
            else
            {
                black_cells.insert(position);
            }
        }

        void ensure_fit(const Position& position)
        {
            int row = position.row;
            int column = position.column;
            // update top_left and bottom_right, if necessary
            top_left.column = std::min(column, top_left.column);
            top_left.row = std::min(row, top_left.row);
            bottom_right.column = std::max(column, bottom_right.column);
            bottom_right.row = std::max(row, bottom_right.row);
        }

        void print() const
        {
            for(int r = top_left.row; r <= bottom_right.row; r++)
            {
                for(int c = top_left.column; c <= bottom_right.column; c++)
                {
                    if(ant.position.column == c && ant.position.row == r)
                    {
                        std::cout << orientation_to_str(ant.orientation);
                    }
                    else
                    {
                        std::cout << (is_black(r, c) ? 'B' : 'W');
                    }
                }
                std::cout << '\n';
            } 
        }
    
    private:
        bool is_black(const Position& position) const
        {
            return is_black(position.row, position.column);
        }

        bool is_black(int row, int column) const
        {
            return black_cells.find(Position(row, column)) != black_cells.end();
        }
};

void printKMovesHashSet(const int K)
{
    Board board;
    for(int i = 0; i < K; i++)
    {
        std::cout << "K = " << i << '\n';
        board.print();
        board.move();
        std::cout << '\n';
    }
}

/**
 * Langton's Ant: An ant is sitting on an infinite grid of white and black
 * squares. Initially, the grid is all white and the ant faces right.
 * At each step, it does the following:
 * (1) At a white square, flip the color of the square, turn 90 degrees right
 * (clockwise), and move forward one unit.
 * (2) At a black square, flip the color of the square, turn 90 degrees left
 * (counter-clockwise), and move forward one unit.
 * Write a program to simulate the first K moves that the ant makes and print the
 * final board as a grid. Note that you are not provided with the data structure 
 * to represent the grid. This is something you must design yourself. The only
 * input to your method is K. You should print the final grid and return nothing.
 * The method signature might be something like void printKMoves(int K).
 */
int main()
{
    std::cout << "Enter 1 to solve using resizable array approach or\n"
    "any other number to solve using hash set approach:\n";
    int method;
    std::cin >> method;
    std::cout << "Enter K:\n";
    int K;
    std::cin >> K;
    // if(method == 1) printKMovesResizableArray(K);
    // else printKMovesHashSet(K);

    printKMovesResizableArray(K);
    printKMovesHashSet(K);
}