#define _USE_MATH_DEFINES
#include "Point.h"
#include <cmath>
#include <sstream>
#include <limits>

namespace geometry {
    Point::Point(const double x, const double y, const double z) : x(x), y(y), z(z) {}

    double Point::getX() const {
        return x;
    }

    double Point::getY() const {
        return y;
    }

    double Point::getZ() const {
        return z;
    }

    double Point::distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    bool Point::operator==(const Point& other) const {
        return std::abs(x - other.x) < std::numeric_limits<double>::epsilon() &&
            std::abs(y - other.y) < std::numeric_limits<double>::epsilon() &&
            std::abs(z - other.z) < std::numeric_limits<double>::epsilon();
    }

    bool Point::operator!=(const Point& other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

    std::istream& operator>>(std::istream& is, Point& point) {
        char comma1, comma2, bracket;
        is >> bracket >> point.x >> comma1 >> point.y >> comma2 >> point.z >> bracket;
        return is;
    }
}
