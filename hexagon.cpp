#include "Point.h"
#include "Hexagon.h"
#include <iostream> 
#include <cmath>

using namespace std;

Figure::Figure(const Point& center_p, double rad, const Point& edge_p)
{
    origin = Point(center_p.get_x(), center_p.get_y());
    border_point = Point(edge_p.get_x(), edge_p.get_y());
    outer_radius = rad;

    // Проверка корректности: расстояние от центра до точки должно соответствовать радиусу
    double actual_dist = sqrt(pow(edge_p.get_x() - center_p.get_x(), 2) +
        pow(edge_p.get_y() - center_p.get_y(), 2));

    // Сравнение с учетом погрешности для типа double
    if (abs(actual_dist - rad) > std::numeric_limits<double>::epsilon() || rad <= 0 || check_equal(center_p, edge_p))
    {
        cout << "Ошибка 2\n"; // Некорректные параметры фигуры
        exit(1);
    }
}

double Figure::calculate_edge()
{
    // У правильного шестиугольника сторона равна радиусу описанной окружности
    return outer_radius;
}

double Figure::calculate_square()
{
    // Формула площади правильного шестиугольника: (3 * sqrt(3) / 2) * R^2
    return (1.5 * sqrt(3.0)) * pow(outer_radius, 2);
}
