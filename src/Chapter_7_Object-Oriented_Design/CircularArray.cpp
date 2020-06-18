#include <iostream>
#include <vector>

template <typename T>
class CircularArray {
    public:
        CircularArray(int size) {
            items = std::vector<T>(size);
        }
        int convert(int index) {
            if(index < 0) {
                index += items.size();
            }
            return (head + index) % items.size();
        }
        void rotate(int shift_right) {
            head = convert(shift_right);
        }
        T get(int i) {
            return items[convert[i]];
        }
        void set(int i, T item) {
            items[convert(i)] = item;
        }
    private:
        std::vector<T> items;
        int head = 0;
};

/**
 * Implement a CircularArray class that supports an array-like data structure which can be efficiently rotated.
 * If possible, the class should use a generic type (also called a template), and should support iteration via 
 * the standard for(Obj o : circularArray) notation. The rotate() method should be able to run in O(1) time.
 */
int main() {
    CircularArray<int> ca(5);
}
