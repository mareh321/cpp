#pragma once 

/**
*@brief Класс для работы с двумерными координатами.
*/
class Point
{
private:
    /**
    *@brief Значение абсциссы.
    */
    double x_coord;
    /**
    *@brief Значение ординаты.
    */
    double y_coord;
public:
    /**
    *@brief Инициализирует объект точки.
    *@param x_val Начальная координата x.
    *@param y_val Начальная координата y.
    */
    Point(const double x_val = 0, const double y_val = 0);
    /**
    *@brief Получает текущую координату x.
    *@return Значение x.
    */
    double get_x() const;
    /**
    *@brief Получает текущую координату y.
    *@return Значение y.
    */
    double get_y() const;
};
/**
*@brief Выполняет проверку идентичности двух точек.
*@param first_p Первая точка для сравнения.
*@param second_p Вторая точка для сравнения.
*@return true, если точки совпадают, иначе false.
*/
bool check_equal(Point first_p, Point second_p);
