#include <iostream>
#include <memory>
#include <clocale>
#include <utility>
#include "Matrix.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Exercise.h"
#include "Task1.h"
#include "Task2.h"

using namespace miit::algebra;

/**
 * @brief Способ заполнения матрицы
 */
enum class Choice : int
{
    Random = 1,     // случайными числами
    Keyboard = 2,   // с клавиатуры
    Constant = 3    // константным значением
};

/**
 * @brief Считывание корректного положительного размера
 * @param prompt Приглашение к вводу
 * @return Размер матрицы (> 0)
 */
size_t readSize(const std::string& prompt)
{
    int value = 0;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value && value > 0)
        {
            return static_cast<size_t>(value);
        }
        std::cout << "Ошибка: размер должен быть целым положительным числом (> 0). Повторите ввод.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

/**
 * @brief Точка входа в демонстрационную программу
 * @return 0, если программа завершена успешно
 */
int main()
{
    std::setlocale(LC_ALL, "Russian");

    std::cout << "========================================================\n";
    std::cout << "  Лабораторная работа 4.3 (ООП стиль) - Вариант 8 (24)  \n";
    std::cout << "========================================================\n\n";

    const size_t n = readSize("Введите количество строк матрицы n: ");
    const size_t m = readSize("Введите количество столбцов матрицы m: ");

    std::cout << "\nВыберите способ заполнения матрицы:\n"
              << static_cast<int>(Choice::Random) << " - случайными числами\n"
              << static_cast<int>(Choice::Keyboard) << " - с клавиатуры\n"
              << static_cast<int>(Choice::Constant) << " - константным значением\n"
              << "Ваш выбор: ";

    int inputChoice = 0;
    std::unique_ptr<Generator> gen;

    if (!(std::cin >> inputChoice))
    {
        std::cerr << "Не удалось прочитать выбор способа заполнения.\n";
        return 1;
    }

    Choice choice = static_cast<Choice>(inputChoice);
    if (choice == Choice::Random)
    {
        int minV = 0;
        int maxV = 0;
        std::cout << "Введите минимальное значение диапазона (min): ";
        std::cin >> minV;
        std::cout << "Введите максимальное значение диапазона (max): ";
        std::cin >> maxV;
        if (minV > maxV)
        {
            std::swap(minV, maxV);
        }
        gen = std::make_unique<RandomGenerator>(minV, maxV);
    }
    else if (choice == Choice::Keyboard)
    {
        gen = std::make_unique<IStreamGenerator>(std::cin);
        std::cout << "Введите " << (n * m) << " целых чисел:\n";
    }
    else if (choice == Choice::Constant)
    {
        int value = 0;
        std::cout << "Введите константное значение: ";
        std::cin >> value;
        gen = std::make_unique<ConstGenerator>(value);
    }
    else
    {
        std::cerr << "Неверный выбор. Введите 1, 2 или 3.\n";
        return 1;
    }

    if (!gen)
    {
        std::cerr << "Не удалось прочитать выбор способа заполнения.\n";
        return 1;
    }

    // Создание и заполнение матрицы через генератор
    Matrix<int> matrix(n, m, *gen);

    std::cout << "\nИсходная матрица (" << matrix.getRows() << "x" << matrix.getCols() << "):\n"
              << matrix.toString() << "\n\n";

    // Демонстрация работы Задачи 1 (через полиморфизм абстрактного класса Exercise)
    std::unique_ptr<Exercise> task1 = std::make_unique<Task1>(matrix);
    std::cout << "Задача 1: " << task1->description() << "\n";
    task1->solve();
    std::cout << "Результат Задачи 1:\n" << task1->getMatrix().toString() << "\n\n";

    // Демонстрация работы Задачи 2 (через полиморфизм абстрактного класса Exercise)
    std::unique_ptr<Exercise> task2 = std::make_unique<Task2>(matrix);
    std::cout << "Задача 2: " << task2->description() << "\n";
    task2->solve();
    std::cout << "Результат Задачи 2:\n" << task2->getMatrix().toString() << "\n\n";

    // Демонстрация перегруженных операторов класса Matrix
    std::cout << "--- Демонстрация операторов сдвига матрицы ---\n";
    Matrix<int> shiftedMatrix = matrix;
    std::cout << "Оператор сдвига влево << 1 (удаление верхней строки):\n";
    shiftedMatrix << 1;
    std::cout << shiftedMatrix.toString() << "\n\n";

    std::cout << "Оператор сдвига вправо >> 1 (добавление пустой строки в начало):\n";
    shiftedMatrix >> 1;
    std::cout << shiftedMatrix.toString() << "\n";

    return 0;
}
