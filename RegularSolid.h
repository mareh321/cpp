#pragma once
#include <iostream>
#include <string>

namespace geometry {
    /**
    * @brief абстрактный базовый класс Правильная фигура
    */
    class RegularSolid {
    public:
        /**
        * @brief виртуальный деструктор по умолчанию
        */
        virtual ~RegularSolid() = default;

        /**
        * @brief расчет площади поверхности фигуры
        * @return площадь поверхности
        */
        virtual double getSurfaceArea() const = 0;

        /**
        * @brief расчет объема фигуры
        * @return объем
        */
        virtual double getVolume() const = 0;

        /**
        * @brief сериализация в строку
        * @return строковое представление фигуры
        */
        virtual std::string ToString() const = 0;

        /**
        * @brief метод чтения из стандартного потока ввода
        * @param is - входной поток
        */
        virtual void read(std::istream& is) = 0;

        /**
        * @brief оператор вывода в поток
        */
        friend std::ostream& operator<<(std::ostream& os, const RegularSolid& solid);

        /**
        * @brief оператор ввода из потока
        */
        friend std::istream& operator>>(std::istream& is, RegularSolid& solid);

        /**
        * @brief статический метод сериализации в строку
        * @param solid - фигура
        * @return строковое представление
        */
        static std::string ToString(const RegularSolid& solid);

        /**
        * @brief статический метод чтения из стандартного потока ввода
        * @param is - входной поток
        * @return указатель на созданную фигуру
        */
        static RegularSolid* readFromStream(std::istream& is);
    };
}
