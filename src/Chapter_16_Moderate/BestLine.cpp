#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<unordered_map>

class GraphPoint {
    public:
        GraphPoint(double x, double y) : _x(x), _y(y) {}
        double _x, _y;
};

class Line {
    public:
        static double epsilon;
        double slope, intercept;
        bool infinite_slope = false;
        Line() = default;
        Line(GraphPoint p1, GraphPoint p2) {
            if(std::abs(p1._x - p2._x) > epsilon) { // x's are different
                slope = (p1._y - p2._y) / (p1._x - p2._x);
                intercept = p1._y - slope * p1._x;
            } else {
                infinite_slope = true;
                intercept = p1._x;
            }
        }
        /**
         * i.e. epsilon = 0.1, d = 5.44 
         * r = 5.44 / 0.1 = 54
         * returns 54 * 0.1 = 5.4
         * input = 5.44, output = 5.4
         */
        static double floorToNearestEpsilon(double d) {
            int r = d / epsilon;
            return ((double) r) * epsilon;
        }
        bool is_equivalent(double a, double b) {
            return std::abs(a - b) < epsilon;
        }
        bool is_equivalent(Line l) {
            if(is_equivalent(l.slope, slope) && is_equivalent(l.intercept, intercept) && l.infinite_slope == infinite_slope) {
                return true;
            }
            return false;
        }
};

double Line::epsilon = 0.0001;

std::unordered_map<double, std::vector<Line>> getListOfLines(std::vector<GraphPoint> points) {
    std::unordered_map<double, std::vector<Line>> linesBySlope;
    for(int i = 0; i < points.size(); i++) {
        for(int j = i + 1; j < points.size(); j++) {
            Line line(points[i], points[j]);
            double key = Line::floorToNearestEpsilon(line.slope);
            linesBySlope[key].push_back(line);
        }
    }
    return linesBySlope;
}

int countEquivalentLines(std::vector<Line> lines, Line line) {
    if(lines.size() == 0) return 0;
    int count = 0; 
    for(Line parallel_line : lines) {
        if(parallel_line.is_equivalent(line)) {
            count++;
        }
    }
    return count;
}

/**
 * This function checks one epsilon above and below actual slope since defining two lines as
 * equivalent if they're within an epsilon of each other
 */
int countEquivalentLines(std::unordered_map<double, std::vector<Line>> linesBySlope, Line line) {
    int slope = line.slope;
    int count = countEquivalentLines(linesBySlope[slope], line);
    count += countEquivalentLines(linesBySlope[slope - Line::epsilon], line);
    count += countEquivalentLines(linesBySlope[slope + Line::epsilon], line);
    return count;
}

Line getBestLine(std::unordered_map<double, std::vector<Line>> linesBySlope) {
    Line best_line;
    int best_count = 0;
    for(auto pair : linesBySlope) {
        std::vector<Line> lines = pair.second;
        for(Line line : lines) {
            int count = countEquivalentLines(linesBySlope, line);
            if(count > best_count) {
                best_count = count;
                best_line = line;
            }
        }
    }
    return best_line;
}

Line findBestLine(std::vector<GraphPoint> points) {
    // key - slope, value - lines with slope equal to key 
    std::unordered_map<double, std::vector<Line>> linesBySlope = getListOfLines(points);
    return getBestLine(linesBySlope);
}

/**
 * Best Line: Given a two-dimensional graph with points on it, find a line which passes 
 * the most number of points.
 */
int main() {
    std::vector<GraphPoint> points = {
        GraphPoint(0, 1), GraphPoint(1, 1), GraphPoint(0, 2), GraphPoint(0, 4), GraphPoint(4, 4)
    };
    Line best_line = findBestLine(points);
    std::string slope = best_line.infinite_slope ? ", slope is infinite" : (", k = " + std::to_string(best_line.slope));
    std::cout << "Best line: intercept = " << best_line.intercept << slope << '\n';
}