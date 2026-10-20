#pragma once
#include "Exercise.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 1 (вариант 8): заменить максимальные элементы столбцов нулём.
         */
        class Task1 : public Exercise
        {
        public:
            /**
             * @brief Конструктор задачи с передачей готовой матрицы
             * @param matrix матрица, с которой работаем
             */
            explicit Task1(Matrix<int> matrix);

            /**
             * @brief Создаёт задачу и заполняет матрицу значениями генератора.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений; при выдаче чисел он меняет своё состояние
             */
            Task1(const size_t rows, const size_t cols,const Generator& generator);

            /**
             * @brief Заменяет нулём все максимальные элементы в каждом столбце.
             * При совпадении максимумов обнуляются все такие элементы.
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
