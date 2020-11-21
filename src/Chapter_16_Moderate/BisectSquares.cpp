#include<iostream>

class Point {
    public:
        Point() = default;
        Point(double x, double y) : _x(x), _y(y) {}
        double _x;
        double _y;
};

class Square {
    public:
        Point middle() {
            return Point((_left + _right) / 2.0, (_top + _bottom) / 2.0);
        }
        double _left;
        double _right;
        double _top;
        double _bottom;
};

/**
 * Bisect Squares: Given two squares on a two-dimensional place, find a line that would cut these two
 * squares in half. Assume that the top and the bottom sides of the square run parallel to the x-axis.
 */
int main() {

}