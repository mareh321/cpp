#include "Point.h"
#include <limits>
#include <cmath>

Point::Point(const double x_val, const double y_val) : x_coord(x_val), y_coord(y_val)
{
}

double Point::get_x() const
{
    return x_coord;
}

double Point::get_y() const
{
    return y_coord;
}

bool check_equal(Point first_p, Point second_p)
{
    return std::abs(first_p.get_x() - second_p.get_x()) < std::numeric_limits<double>::epsilon() &&
        std::abs(first_p.get_y() - second_p.get_y()) < std::numeric_limits<double>::epsilon();
}
