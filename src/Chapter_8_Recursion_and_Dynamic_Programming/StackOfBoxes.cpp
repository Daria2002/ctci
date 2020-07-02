#include <iostream>
#include <vector>

class Box {
    public:
        int x, y, z;
        Box() = default;
        Box(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

int tallest_height_optimal(std::vector<Box> boxes) {
    // TODO
}

int tallest_height(std::vector<Box> boxes) {
    // TODO
}

std::vector<Box> get_boxes() {
    std::vector<Box> boxes;
    boxes.push_back(Box(2, 3, 3));
    boxes.push_back(Box(7, 4, 1));
    boxes.push_back(Box(9, 3, 7));
    boxes.push_back(Box(3, 3, 9));
    boxes.push_back(Box(2, 2, 1));
    return boxes;
}

std::vector<Box> sort_boxes(std::vector<Box> boxes) {
    std::vector<Box> boxes;
    // TODO
    return boxes;
}

/**
 * You have a stack of n boxes, with widths W_i heights h_i and depths d_i. The boxes
 * cannot be rotated and can only be stacked on top of one another if each box in the stack is strictly
 * larger than the box above it in width, height. and depth. Implement a method to compute the
 * height of the tallest possible stack. The height of a stack is the sum of the heights of each box.
 */
int main() {
    int method;
    std::cout << "Enter 1 to solve using optimal method, otherwise any other number\n";
    std::cin >> method;
    std::vector<Box> boxes = get_boxes();
    sort_boxes(boxes);
    std::cout << "Tallest possible stack has a height = " << (method == 1 ? tallest_height_optimal(boxes) : tallest_height(boxes)) << '\n';
}
