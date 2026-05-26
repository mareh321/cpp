#include <iostream>
#include <vector>
#include <memory>
#include "Tetrahedron.h"
#include <clocale>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

/**
* @brief точка входа в программу
* @return 0, если программа выполнена успешно
*/
int main(void) {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");

    try {
        std::cout << "=== Демонстрация работы с классами RegularSolid и Tetrahedron ===\n\n";

        std::cout << "1. Создание тетраэдра через четыре точки:\n";

        // Используем ГАРАНТИРОВАННО правильные координаты тетраэдра
        // Правильный тетраэдр с длиной ребра sqrt(8) ≈ 2.828
        geometry::Point p1(1, 1, 1);
        geometry::Point p2(1, -1, -1);
        geometry::Point p3(-1, 1, -1);
        geometry::Point p4(-1, -1, 1);

        geometry::Tetrahedron tetrahedron1(p1, p2, p3, p4);
        std::cout << "Тетраэдр 1: " << tetrahedron1 << "\n";
        std::cout << "Площадь поверхности: " << tetrahedron1.getSurfaceArea() << "\n";
        std::cout << "Объем: " << tetrahedron1.getVolume() << "\n\n";

        std::cout << "2. Создание тетраэдра через координаты вершин:\n";
        geometry::Tetrahedron tetrahedron2(
            1, 1, 1,
            1, -1, -1,
            -1, 1, -1,
            -1, -1, 1
        );
        std::cout << "Тетраэдр 2: " << tetrahedron2 << "\n";
        std::cout << "Площадь поверхности: " << tetrahedron2.getSurfaceArea() << "\n";
        std::cout << "Объем: " << tetrahedron2.getVolume() << "\n\n";

        std::cout << "3. Создание тетраэдра по центру описанной сферы и длине ребра:\n";
        geometry::Point center1(0, 0, 0);
        geometry::Tetrahedron tetrahedron3 = geometry::Tetrahedron::createFromCircumscribedSphere(center1, 2.0);
        std::cout << "Тетраэдр 3: " << tetrahedron3 << "\n\n";

        std::cout << "4. Создание тетраэдра по центру вписанной сферы и длине ребра:\n";
        geometry::Point center2(0, 0, 0);
        geometry::Tetrahedron tetrahedron4 = geometry::Tetrahedron::createFromInscribedSphere(center2, 3.0);
        std::cout << "Тетраэдр 4: " << tetrahedron4 << "\n\n";

        std::cout << "5. Коллекция объектов базового типа:\n";
        std::vector<std::unique_ptr<geometry::RegularSolid>> solids;
        solids.push_back(std::make_unique<geometry::Tetrahedron>(tetrahedron1));
        solids.push_back(std::make_unique<geometry::Tetrahedron>(tetrahedron2));
        solids.push_back(std::make_unique<geometry::Tetrahedron>(tetrahedron3));
        solids.push_back(std::make_unique<geometry::Tetrahedron>(tetrahedron4));

        std::cout << "Итерация по коллекции:\n";
        for (size_t i = 0; i < solids.size(); ++i) {
            std::cout << "Объект " << (i + 1) << ": " << *solids[i] << "\n";
            std::cout << "  Площадь поверхности: " << solids[i]->getSurfaceArea() << "\n";
            std::cout << "  Объем: " << solids[i]->getVolume() << "\n\n";
        }

        std::cout << "6. Демонстрация операторов сравнения:\n";
        geometry::Tetrahedron tetrahedron5 = tetrahedron1;
        geometry::Tetrahedron tetrahedron6 = tetrahedron3;

        std::cout << "tetrahedron1 == tetrahedron5: " << (tetrahedron1 == tetrahedron5 ? "истина" : "ложь") << "\n";
        std::cout << "tetrahedron1 == tetrahedron3: " << (tetrahedron1 == tetrahedron6 ? "истина" : "ложь") << "\n";
        std::cout << "tetrahedron1 != tetrahedron3: " << (tetrahedron1 != tetrahedron6 ? "истина" : "ложь") << "\n\n";

        std::cout << "7. Демонстрация статического метода ToString:\n";
        std::cout << geometry::Tetrahedron::ToString(tetrahedron1) << "\n\n";

        std::cout << "8. Демонстрация конструктора копирования:\n";
        geometry::Tetrahedron tetrahedron7(tetrahedron1);
        std::cout << "Скопированный тетраэдр: " << tetrahedron7 << "\n\n";

        std::cout << "9. Демонстрация оператора присваивания:\n";
        geometry::Tetrahedron tetrahedron8;
        tetrahedron8 = tetrahedron1;
        std::cout << "Присвоенный тетраэдр: " << tetrahedron8 << "\n\n";

        std::cout << "10. Попытка создания некорректного тетраэдра (ожидается исключение):\n";
        try {
            geometry::Tetrahedron invalidTetrahedron(0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3);
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }

        std::cout << "\n11. Попытка создания тетраэдра с отрицательной длиной ребра:\n";
        try {
            geometry::Tetrahedron invalidTetrahedron2(center1, -1.0, geometry::SphereType::Circumscribed);
        }
        catch (const std::exception& e) {
            std::cout << "Исключение: " << e.what() << "\n";
        }

        std::cout << "\n12. Получение вершин тетраэдра:\n";
        std::vector<geometry::Point> verts = tetrahedron1.getVertices();
        for (size_t i = 0; i < verts.size(); ++i) {
            std::cout << "Вершина " << (i + 1) << ": " << verts[i] << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nПрограмма завершена успешно.\n";
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
