#include <iostream>
#include <limits>

class Point {
    public:
        Point(int x_, int y_) : x(x_), y(y_) {}
        Point() = default;
        double x, y;
};

class Line {
    public:
        double slope, y_intersept;
        Point start, end;
        Line(Point s, Point e) : start(s), end(e) {
            // vertical - two points have the same x value
            if(start.x == end.x) {
                slope = std::numeric_limits<double>::max();
                y_intersept = std::numeric_limits<double>::max();
            } else {
                slope = (end.y - start.y) / (end.x - start.x);
                y_intersept = end.y - slope * end.x;
            }
        }
        bool is_vertical() const {
            return slope == std::numeric_limits<double>::max();
        }
        double getYFromX(double x) const {
            if(is_vertical()) {
                return std::numeric_limits<double>::max();
            }
            return slope * x + y_intersept;
        }
};

// returns true if middle is between start and end, otherwise false
bool is_between(double start, double middle, double end) {
    if(start > end) {
        return end <= middle && middle <= start;
    }
    return start <= middle && middle <= end;
}

// returns true if middle is between start and end, otherwise false
bool is_between(Point start, Point middle, Point end) {
    return is_between(start.x, middle.x, end.x) && is_between(start.y, middle.y, end.y);
}

// function returns true if there is intersection point between line1 and line2, otherwise false
bool intersection(const Point& start1, const Point& end1, const Point& start2, const Point& end2, Point& intersection_point) {
    // compute line1 and line2
    Line line1(start1, end1);
    Line line2(start2, end2);

    // check if lines are parallel
    if(line1.slope == line2.slope) {
        // return false, if line1 and line2 have different y_intercept (they are parallel and not on the same line)
        if(line1.y_intersept != line2.y_intersept) return false;
        // check if start or end of one line is on the other line
        if(is_between(start1, start2, end1)) {
            intersection_point = start2;
            return true;
        } else if(is_between(start1, end2, end2)) {
            intersection_point = end2;
            return true;
        } else if(is_between(start2, start1, end2)) {
            intersection_point = start1;
            return true;
        } else if(is_between(start2, end1, end2)) {
            intersection_point = end1;
            return true;
        }
        return false; // points are parallel and on same line but don't intersect
    }
    
    // if lines are infinite

    double intersection_x;

    // if one of the lines is vertical, intersection_x is known
    if(line1.is_vertical() || line2.is_vertical()) {
        intersection_x = line1.is_vertical() ? line1.start.x : line2.start.x;
    } else { // solve equation y1 = y2, where y1 = m1 * x1 + l1 and y2 = m2 * x2 + l2
        intersection_x = (line2.y_intersept - line1.y_intersept) / (line1.slope - line2.slope);
    }

    // get intersection_y using non-vertical line
    double intersection_y = line1.is_vertical() ? line2.getYFromX(intersection_x) : line1.getYFromX(intersection_x);

    // check if intersection coordinates are within the boundaries of each line segment
    Point to_check(intersection_x, intersection_y);
    if(is_between(line1.start, to_check, line1.end) && is_between(line2.start, to_check, line2.end)) {
        intersection_point = to_check;
        return true;
    }
    // intersection of the infinite lines is not within the boundaries of each line segment
    return false;
}

/**
 * Intersection: Given two straight line segments (represented as a start point and an end point),
 * compute the point of intersection, if any.
 */
int main() {
    Point intersection_point;
    Point start1(0, 0);
    Point end1(5, 5);
    Point start2(1, 1);
    Point end2(10, 10);
    std::cout << "intersection " << (intersection(start1, end1, start2, end2, intersection_point) ? "" : "doesn't ") << "exists\n";
    std::cout << "intersection_x = " << intersection_point.x << ", intersection_y = " << intersection_point.y << '\n';
}