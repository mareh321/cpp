#include <iostream>
#include "Hexagon.h"
#include <string>

using namespace std;

/**
*@brief Выполняет чтение координат из стандартного потока.
*@param msg Пояснительное сообщение для пользователя.
*@return Объект созданной точки.
*/
Point read_point(string msg = "");

/**
*@brief Точка входа в программу.
*@return 0, если программа выполнена корректно.
*/
int main()
{Ы
    system("chcp 1251");
    Point p_center = read_point("Введите координаты центра (x y): ");

    cout << "Введите радиус описанной окружности R: " << endl;
    double r_val;
    cin >> r_val;
    if (cin.fail() || r_val <= 0) {
        cout << "Ошибка 1\n"; // Ошибка ввода данных
        exit(1);
    }

    Point p_on_circle = read_point("Введите точку на окружности (x y): ");

    Figure hex_obj(p_center, r_val, p_on_circle);

    cout << "Длина стороны: " << hex_obj.calculate_edge() << endl;
    cout << "Площадь фигуры: " << hex_obj.calculate_square() << endl;

    return 0;
}

Point read_point(string msg)
{
    cout << msg << endl;
    double in_x = 0, in_y = 0;
    cin >> in_x >> in_y;
    if (cin.fail())
    {
        cout << "Ошибка 1\n"; // Ошибка ввода координат
        exit(1);
    }
    return Point(in_x, in_y);
}
