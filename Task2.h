#pragma once
#include "Exercise.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Задача 2 (вариант 8): вставить первую строку после строк с элементом наибольшего модуля.
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
             * @brief Создаёт задачу и заполняет матрицу значениями генератора.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений; при выдаче чисел он меняет своё состояние
             */
            Task2(const size_t rows, const size_t cols, Generator& generator);

            /**
             * @brief Вставляет копию первой строки после каждой строки, содержащей элемент
             * с наибольшим модулем во всей матрице.
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
