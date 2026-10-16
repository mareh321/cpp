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
         * Здесь хранится матрица и, если он нужен, указатель на генератор.
         * Конкретные задачи задают свои способы решения и описание.
         */
        class Exercise
        {
        protected:
            /**
             * @brief Матрица, которую будет обрабатывать задача.
             */
            Matrix<int> matrix;

            /**
             * @brief Генератор значений. Сам объект принадлежит вызывающему коду.
             */
            const Generator* generator;

        public:
            /**
             * @brief Конструктор с готовой матрицей
             * @param matrix матрица целых чисел
             * @param generator указатель на генератор значений (необязательный)
             */
            explicit Exercise(Matrix<int> matrix, const Generator* generator = nullptr);

            /**
             * @brief Создаёт матрицу и заполняет её значениями генератора.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений, который меняет своё состояние при выдаче чисел
             */
            Exercise(const size_t rows, const size_t cols, Generator& generator);

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

            /**
             * @brief Получить используемый генератор
             * @return указатель на генератор
             */
            const Generator* getGenerator() const noexcept;

            /**
             * @brief Установить новый генератор
             * @param gen указатель на новый генератор
             */
            void setGenerator(const Generator* gen) noexcept;
        };
    }
}
