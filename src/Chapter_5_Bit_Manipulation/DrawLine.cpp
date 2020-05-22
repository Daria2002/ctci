#include <iostream>
#include <array>

#define SCREEN_SIZE 50

// char range: [-128, 127]
// unsigned char range: [0, 255]
using byte = unsigned char;

void draw_line(std::array<byte, SCREEN_SIZE>& screen, int width, int x1, int x2, int y) {
    // start offset
    int start_bit_index = y * width + x1;
    int start_byte_index = start_bit_index / 8; // be careful: indices range starts at 0 
    int start_offset = start_bit_index % 8;

    // end offset
    int end_bit_index = y * width + x2;
    int end_byte_index = end_bit_index / 8;
    int end_offset = end_bit_index % 8;

    // set full bites
    for(int i = start_byte_index + 1; i < end_byte_index; i++) {
        screen[i] = 0xFF; // 1111 1111
    }

    int start_mask = (0xFF >> (start_offset));
    int end_mask = (0xFF << (8 - end_offset - 1));
    if(start_byte_index == end_byte_index) {
        int byte_mask = start_mask & end_mask;
        screen[start_byte_index] |= byte_mask;  
    } else {
        if(start_offset != 0) {
            screen[start_byte_index] |= start_mask;
        }
        if(end_offset != 0) {
            screen[end_byte_index] |= end_mask;
        }
    }
}

void display(std::array<byte, SCREEN_SIZE> screen, int width) {
    int columns = width / 8;
    int rows = SCREEN_SIZE / columns; // 50 bytes = 50 * 8 bits
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            int val = screen[i * columns + j];
            for(int k = 0; k < 8; k++) {
                std::cout << (((val << k) & 0x80) ? "_" : ".");
            }
        }
        std::cout << '\n';
    }
}

void initialize_array(std::array<byte, SCREEN_SIZE>& arr) {
    for(int i =  0; i < SCREEN_SIZE; i++) {
        arr[i] = 0x00;
    }
}

/**
 * A monochrome screen is stored as a single array of bytes, allowing eight consecutive
 * pixels to be stored in one byte. The screen has width w, where w is divisible by 8
 * (that is, no byte will be split across rows). The height of the screen, of course, 
 * can be derived from the length of the array and the width. Implement a function that
 * draws a horizontal line from (x1, y) to (x2, y).
 * The method signature should look something like:
 * drawLine(byte[] screen, int width, int x1,  int x2, int y)
 */
int main() {
    std::cout << "========================\n"
                 "Program for drawing line\n"
                 "========================\n";
    constexpr int width = 80;
    std::array<byte, SCREEN_SIZE> screen;
    initialize_array(screen);
    constexpr int height = screen.size() / width;
    std::cout << "Before drawing line:\n";
    display(screen, width);
    int x1, x2, y;
    std::cout << "Enter x1 (first index = 0):\n";
    std::cin >> x1;
    std::cout << "Enter x2 (first index = 0):\n";
    std::cin >> x2;
    std::cout << "Enter y (first index = 0):\n";
    std::cin >> y;
    std::cout << "After drawing line:\n";
    draw_line(screen, width, x1, x2, y);
    display(screen, width);
}
