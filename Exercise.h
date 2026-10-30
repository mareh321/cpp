#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Общая основа для задач, которые работают с матрицей.
         *
         * Здесь хранится матрица.
         * Конкретные задачи задают свои способы решения и описание.
         */
        class Exercise
        {
        protected:
            /**
             * @brief Матрица, которую будет обрабатывать задача.
             */
            Matrix<int> matrix;

        public:
            /**
             * @brief Конструктор с готовой матрицей
             * @param matrix матрица целых чисел
             */
            explicit Exercise(Matrix<int> matrix);

            /**
             * @brief Создаёт матрицу и заполняет её значениями генератора.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений, который меняет своё состояние при выдаче чисел
             */
            Exercise(const size_t rows, const size_t cols, const Generator& generator);

            /**
             * @brief Виртуальный деструктор
             */
            virtual ~Exercise() = default;

            /**
             * @brief Выполняет задачу; реализация есть в классах-наследниках.
             */
            virtual void solve() = 0;

            /**
             * @brief Возвращает короткое описание задачи.
             * @return строка с описанием
             */
            virtual std::string description() const = 0;

            /**
             * @brief Даёт доступ к матрице без возможности её изменить.
             * @return константная ссылка на матрицу
             */
            const Matrix<int>& getMatrix() const noexcept;

            /**
             * @brief Даёт доступ к матрице для изменения.
             * @return ссылка на матрицу
             */
            Matrix<int>& getMatrix() noexcept;

            /**
             * @brief Установить новую матрицу
             * @param newMatrix новая матрица
             */
            void setMatrix(Matrix<int> newMatrix);

        };
    }
}
