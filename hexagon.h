#pragma once
#include "Point.h"

/**
*@brief Класс для моделирования правильного шестиугольника.
*/
class Figure
{
private:
    /**
    *@brief Центральная точка фигуры.
    */
    Point origin;
    /**
    *@brief Опорная точка на границе.
    */
    Point border_point;
    /**
    *@brief Дистанция от центра до вершины.
    */
    double outer_radius;

public:
    /**
    *@brief Конструктор правильного шестиугольника.
    *@param center_p Точка центра.
    *@param rad Величина радиуса.
    *@param edge_p Точка на окружности.
    */
    Figure(const Point& center_p, double rad, const Point& edge_p);

    /**
    *@brief Определяет размер стороны фигуры.
    *@return Длина стороны.
    */
    double calculate_edge();

    /**
    *@brief Вычисляет общую площадь фигуры.
    *@return Значение площади.
    */
    double calculate_square();
};
