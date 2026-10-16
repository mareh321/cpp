#pragma once
#include "Matrix.h"
#include "Generator.h"
#include <string>

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Абстрактный базовый класс упражнения (задачи) над матрицей
         * 
         * В соответствии с принципами ООП агрегирует класс Matrix<int> и Generator,
         * предоставляя единый интерфейс и общее состояние для конкретных задач (Task1, Task2).
         */
        class Exercise
        {
        protected:
            /**
             * @brief Матрица, с которой работает упражнение
             */
            Matrix<int> matrix;

            /**
             * @brief Указатель на генератор (агрегация, внешнее владение)
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
             * @brief Конструктор с инициализацией матрицы через генератор
             * @param rows количество строк
             * @param cols количество столбцов
             * @param generator генератор значений для матрицы
             */
            Exercise(const size_t rows, const size_t cols, const Generator& generator);

            /**
             * @brief Виртуальный деструктор
             */
            virtual ~Exercise() = default;

            /**
             * @brief Решить задачу (чисто виртуальный метод)
             */
            virtual void solve() = 0;

            /**
             * @brief Получить текстовое описание задачи (чисто виртуальный метод)
             * @return строка с описанием
             */
            virtual std::string description() const = 0;

            /**
             * @brief Получить константную ссылку на матрицу
             * @return константная ссылка на матрицу
             */
            const Matrix<int>& getMatrix() const noexcept;

            /**
             * @brief Получить неконстантную ссылку на матрицу
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
