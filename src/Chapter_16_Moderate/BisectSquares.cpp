#include <iostream>
#include <vector>

class Point {
    public:
        Point() = default;
        Point(double x, double y) : _x(x), _y(y) {}
        double _x;
        double _y;
};

class Line {
    public:
        Line(Point start, Point end) : _start(start), _end(end) {}
        Point _start;
        Point _end;
};

Point extend(Point mid1, Point mid2, double size) {
    // mid2 -> mid1 direction
    double x_dir = mid1._x < mid2._x ? -1 : 1;
    double y_dir = mid1._y < mid2._y ? -1 : 1;
    // slope = (y2 - y2) / (x2 - x1), if x2 == x1 -> 0 exception -> special case
    if(mid1._x == mid2._x) {
        return Point(mid1._x, mid1._y + y_dir * size / 2.0);
    } 
    double slope = (mid1._y - mid2._y) / (mid1._x - mid2._x);
    double x1 = 0;
    double y1 = 0;
    if(std::abs(slope) == 1) {
        x1 = mid1._x + x_dir * size / 2.0;
        y1 = mid1._y + y_dir * size / 2.0;
    } else if(std::abs(slope) < 1) {
        x1 = mid1._x + x_dir * size / 2.0;
        y1 = slope * (x1 - mid1._x) + mid1._y;
    } else {
        y1 = mid1._y + y_dir * size / 2.0;
        x1 = (y1 - mid1._y) / slope + mid1._x;
    }
    return Point(x1, y1);
}

class Square {
    public:
        double _left;
        double _right;
        double _top;
        double _bottom;

        Square(double left, double right, double top, double bottom) : _left(left), _right(right), _top(top), _bottom(bottom) {}

        Point middle() 
        {
            return Point((_left + _right) / 2.0, (_top + _bottom) / 2.0);
        }

        double size() 
        {
            return std::abs(_right - _left);
        }

        Line cut(Square other) 
        {
            Point p1 = extend(middle(), other.middle(), size());
            Point p2 = extend(middle(), other.middle(), -size());
            Point p3 = extend(other.middle(), middle(), other.size());
            Point p4 = extend(other.middle(), middle(), -other.size());
            Point start = p1;
            Point end = p1;
            std::vector<Point> points = {p2, p3, p4};
            for(int i = 0; i < points.size(); i++) {
                if(points[i]._x < start._x || (points[i]._x == start._x && points[i]._y < start._y)) {
                    start = points[i];
                } else if(points[i]._x > end._x || (points[i]._x == end._x && points[i]._y > end._y)) {
                    end = points[i];
                }
            }
            return Line(start, end);
        }
};

/**
 * Bisect Squares: Given two squares on a two-dimensional place, find a line that would cut these two
 * squares in half. Assume that the top and the bottom sides of the square run parallel to the x-axis.
 */
int main() 
{    
    Square s1(2, 3, 2, 1);
    Square s2(2, 3, 2, 1);
    Line line = s1.cut(s2);
    std::cout << "Start point = (" << line._start._x << ", " << line._start._y << "), end point = (" << line._end._x << ", " << line._end._y << ")\n"; 
}