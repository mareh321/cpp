#pragma once
#include "Exercise.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 1 (Вариант 8): Заменить максимальный элемент каждого столбца нулем
         */
        class Task1 : public Exercise
        {
        public:
            /**
             * @brief Конструктор задачи с передачей готовой матрицы
             * @param matrix матрица, с которой работаем
             * @param generator указатель на генератор (необязательный)
             */
            explicit Task1(Matrix<int> matrix, const Generator* generator = nullptr);

            /**
             * @brief Конструктор задачи с генерацией матрицы
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений для матрицы
             */
            Task1(const size_t rows, const size_t cols, const Generator& generator);

            /**
             * @brief Заменить максимальный элемент каждого столбца нулем
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
