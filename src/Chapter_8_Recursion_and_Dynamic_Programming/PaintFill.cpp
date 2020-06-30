#include <iostream>
#include <vector>

enum Color {
    red = 0,
    blue = 1,
    yellow = 2,
    green = 3,
    pink = 4
};

class Point {
    public:
        Point(int _row, int _column) : row(_row), column(_column) {}
        Point() {}
        int row, column;
};

std::string color_to_str(const int num) {
    switch (num)
    {
    case 0:
        return "R";
    case 1:
        return "B";
    case 2:
        return "Y";
    case 3:
        return "G";
    default:
        return "P";
    }
}

std::vector<std::vector<Color>> ini_screen() {
    std::vector<std::vector<Color>> screen;
    std::vector<Color> tmp = {Color(0), Color(0), Color(1), Color(1), Color(4), Color(3)};
    screen.push_back(tmp);
    tmp.clear();
    tmp = {Color(3), Color(0), Color(1), Color(4), Color(4), Color(3)};
    screen.push_back(tmp);
    tmp.clear();
    tmp = {Color(3), Color(3), Color(0), Color(4), Color(1), Color(3)};
    screen.push_back(tmp);
    tmp.clear();
    tmp = {Color(2), Color(2), Color(2), Color(1), Color(1), Color(2)};
    screen.push_back(tmp);
    tmp.clear();
    tmp = {Color(2), Color(4), Color(4), Color(3), Color(3), Color(3)};
    screen.push_back(tmp);
    tmp.clear();
    tmp = {Color(2), Color(4), Color(1), Color(1), Color(1), Color(1)};
    screen.push_back(tmp);
    tmp.clear();
    return screen;
}

void display(const std::vector<std::vector<Color>>& screen) {
    for(int i = 0; i < screen.size(); i++) {
        for(int j = 0; j < screen[i].size(); j++) {
            std::cout << color_to_str(screen[i][j]) << " ";
        }
        std::cout << '\n';
    }
}

/**
 * Return true if point is valid, otherwise false
 */
bool fill(std::vector<std::vector<Color>>& screen, Point point, const Color new_color, const Color old_color) {
    if(point.row < 0 || point.row >= screen.size() || point.column < 0 || point.column >= screen[0].size()) return false;
    if(screen[point.row][point.column] != old_color) return true; // don't change color
    screen[point.row][point.column] = new_color;
    fill(screen, Point(point.row - 1, point.column), new_color, old_color);
    fill(screen, Point(point.row + 1, point.column), new_color, old_color);
    fill(screen, Point(point.row, point.column - 1), new_color, old_color);
    fill(screen, Point(point.row, point.column + 1), new_color, old_color);
    return true;
}

bool fill(std::vector<std::vector<Color>>& screen, Point point, const Color& new_color) {
    if(screen[point.row][point.column] == new_color) return false; // old color is already filled with new color
    return fill(screen, point, new_color, screen[point.row][point.column]);
}

Point get_point() {
    int row, column;
    std::cout << "Enter row:\n";
    std::cin >> row;
    std::cout << "Enter column:\n";
    std::cin >> column;
    return Point(row, column);
}

Color get_color() {
    int col;
    std::cout << "Enter new color (red = 0, blue = 1, yellow = 2, green = 3, pink = 4):\n";
    std::cin >> col;
    return Color(col);
}

/**
 * Implement the "paint fill" function that one might see on many image editing programs.
 * That is, given a screen (represented by a two-dimensional array of colors), a point, and
 * a new color, fill in the surrounding area until the color changes from the original color.
 */
int main() {
    std::vector<std::vector<Color>> screen = ini_screen();
    display(screen);
    Point point = get_point();
    Color new_color = get_color();
    std::cout << "Screen has" << (fill(screen, point, new_color) ? " " : " not ") << "been changed.\n";
    display(screen);
}
