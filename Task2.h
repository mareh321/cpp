#pragma once
#include "Exercise.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 2 (Вариант 8): Вставить после всех строк, содержащих максимальный по модулю элемент, первую строку
         */
        class Task2 : public Exercise
        {
        public:
            /**
             * @brief Конструктор задачи с передачей готовой матрицы
             * @param matrix матрица, с которой работаем
             * @param generator указатель на генератор (необязательный)
             */
            explicit Task2(Matrix<int> matrix, const Generator* generator = nullptr);

            /**
             * @brief Конструктор задачи с генерацией матрицы
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений для матрицы
             */
            Task2(const size_t rows, const size_t cols, const Generator& generator);

            /**
             * @brief Выполнить вставку первой строки после строк, содержащих максимальный по модулю элемент
             */
            void solve() override;

            /**
             * @brief Получить текстовое описание задачи
             * @return строка с описанием
             */
            std::string description() const override;
        };
    }
}
