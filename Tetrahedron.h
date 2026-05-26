#pragma once
#include "RegularSolid.h"
#include "Point.h"
#include <vector>

namespace geometry {
    /**
    * @brief перечислимый тип для идентификации типа сферы
    */
    enum class SphereType {
        Inscribed,   // вписанная сфера
        Circumscribed // описанная сфера
    };

    /**
    * @brief класс Правильный тетраэдр
    */
    class Tetrahedron : public RegularSolid {
    private:
        /**
        * @brief VERTEX_COUNT - постоянное количество вершин тетраэдра
        */
        static const int VERTEX_COUNT = 4;

        /**
        * @brief вершины тетраэдра
        */
        std::vector<Point> vertices;

        /**
        * @brief проверяет корректность вершин тетраэдра
        * @return true, если вершины образуют правильный тетраэдр
        */
        bool isValidTetrahedron() const;

        /**
        * @brief вычисляет длину ребра тетраэдра
        * @return длина ребра
        */
        double getEdgeLength() const;

    public:
        /**
        * @brief конструктор по умолчанию
        */
        Tetrahedron();

        /**
        * @brief конструктор, создающий тетраэдр по четырем вершинам
        * @param p1 - вершина 1
        * @param p2 - вершина 2
        * @param p3 - вершина 3
        * @param p4 - вершина 4
        */
        Tetrahedron(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

        /**
        * @brief конструктор, создающий тетраэдр по координатам четырех вершин
        * @param x1, y1, z1 - координаты вершины 1
        * @param x2, y2, z2 - координаты вершины 2
        * @param x3, y3, z3 - координаты вершины 3
        * @param x4, y4, z4 - координаты вершины 4
        */
        Tetrahedron(const double x1, const double y1, const double z1,
            const double x2, const double y2, const double z2,
            const double x3, const double y3, const double z3,
            const double x4, const double y4, const double z4);

        /**
        * @brief конструктор, создающий тетраэдр по центру сферы и длине ребра
        * @param center - центр сферы
        * @param edgeLength - длина ребра
        * @param sphereType - тип сферы (вписанная или описанная)
        */
        Tetrahedron(const Point& center, const double edgeLength, const SphereType sphereType);

        /**
        * @brief конструктор копирования
        * @param other - копируемый тетраэдр
        */
        Tetrahedron(const Tetrahedron& other);

        /**
        * @brief оператор присваивания
        * @param other - присваиваемый тетраэдр
        * @return ссылка на текущий объект
        */
        Tetrahedron& operator=(const Tetrahedron& other);

        /**
        * @brief расчет площади поверхности тетраэдра
        * @return площадь поверхности
        */
        double getSurfaceArea() const override;

        /**
        * @brief расчет объема тетраэдра
        * @return объем
        */
        double getVolume() const override;

        /**
        * @brief сериализация в строку
        * @return строковое представление тетраэдра
        */
        std::string ToString() const override;

        /**
        * @brief метод чтения из стандартного потока ввода
        * @param is - входной поток
        */
        void read(std::istream& is) override;

        /**
        * @brief оператор сравнения на равенство
        * @param other - другой тетраэдр
        * @return true, если тетраэдры равны
        */
        bool operator==(const Tetrahedron& other) const;

        /**
        * @brief оператор сравнения на неравенство
        * @param other - другой тетраэдр
        * @return true, если тетраэдры не равны
        */
        bool operator!=(const Tetrahedron& other) const;

        /**
        * @brief получение вершин тетраэдра
        * @return вектор вершин
        */
        std::vector<Point> getVertices() const;

        /**
        * @brief статический метод сериализации в строку
        * @param tetrahedron - тетраэдр
        * @return строковое представление
        */
        static std::string ToString(const Tetrahedron& tetrahedron);

        /**
        * @brief статический метод чтения из стандартного потока ввода
        * @param is - входной поток
        * @return созданный тетраэдр
        */
        static Tetrahedron readFromStream(std::istream& is);

        /**
        * @brief создает правильный тетраэдр по центру описанной сферы и длине ребра
        * @param center - центр описанной сферы
        * @param edgeLength - длина ребра
        * @return правильный тетраэдр
        */
        static Tetrahedron createFromCircumscribedSphere(const Point& center, const double edgeLength);

        /**
        * @brief создает правильный тетраэдр по центру вписанной сферы и длине ребра
        * @param center - центр вписанной сферы
        * @param edgeLength - длина ребра
        * @return правильный тетраэдр
        */
        static Tetrahedron createFromInscribedSphere(const Point& center, const double edgeLength);
    };
}
