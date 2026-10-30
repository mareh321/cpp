#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <utility>
#include "Generator.h"

namespace miit
{
    namespace algebra
    {
        /**
         * @brief Матрица с элементами типа T.
         * @tparam T Тип значений, которые будут храниться в матрице.
         */
        template <typename T>
        class Matrix
        {
        private:
            /** 
             * @brief Здесь лежат строки матрицы, каждая в виде отдельного вектора.
             */
            std::vector<std::vector<T>> data;

            /**
             * @brief Сколько строк сейчас в матрице.
             */
            size_t rows;

            /**
             * @brief Сколько элементов находится в каждой строке.
             */
            size_t cols;

        public:
            /**
             * @brief Создаёт пустую матрицу размером 0 на 0.
             */
            Matrix() noexcept;

            /**
             * @brief Создаёт матрицу нужного размера и заполняет её значениями T{}.
             * @param rows Число строк.
             * @param cols Число столбцов.
             */
            Matrix(const size_t rows, const size_t cols);

            /**
             * @brief Создаёт матрицу и заполняет все ячейки одним значением.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param value Значение для каждой ячейки.
             */
            Matrix(const size_t rows, const size_t cols, const T& value);

            /**
             * @brief Создаёт матрицу и получает значения у генератора.
             * @param rows количество строк
             * @param cols количество столбцов
             * @param gen Генератор, который выдаёт значения.
             */
            Matrix(const size_t rows, const size_t cols, const Generator& gen);


            /**
             * @brief Конструктор копирования
             * @param other ссылка на копируемую матрицу
             */
            Matrix(const Matrix& other) = default;

            /**
             * @brief Конструктор перемещения
             * @param other rvalue-ссылка на перемещаемую матрицу
             */
            Matrix(Matrix&& other) noexcept = default;

            /**
             * @brief Деструктор
             */
            ~Matrix() = default;

            /**
             * @brief Оператор присваивания копированием
             * @param other ссылка на копируемую матрицу
             * @return ссылка на текущий объект
             */
            Matrix& operator=(const Matrix& other) = default;

            /**
             * @brief Оператор присваивания перемещением
             * @param other rvalue-ссылка на перемещаемую матрицу
             * @return ссылка на текущий объект
             */
            Matrix& operator=(Matrix&& other) noexcept = default;

            /**
             * @brief Возвращает строку по индексу, её элементы можно менять.
             * @param index индекс строки (0 .. rows - 1)
             * @return ссылка на вектор элементов строки
             * @throw std::out_of_range при выходе индекса за границы
             * @note Не меняйте размер возвращённого вектора: все строки должны иметь cols элементов.
             */
            std::vector<T>& operator[](const size_t index);

            /**
             * @brief Возвращает строку по индексу без возможности её изменить.
             * @param index индекс строки (0 .. rows - 1)
             * @return константная ссылка на вектор элементов строки
             * @throw std::out_of_range при выходе индекса за границы
             */
            const std::vector<T>& operator[](const size_t index) const;

            /**
             * @brief Удаляет первые shift строк.
             * @param shift количество удаляемых верхних строк
             * @return ссылка на текущий объект
             */
            Matrix& operator<<(const size_t shift);

            /**
             * @brief Добавляет в начало shift строк, заполненных значениями по умолчанию.
             * @param shift количество добавляемых верхних строк
             * @return ссылка на текущий объект
             */
            Matrix& operator>>(const size_t shift);

            /**
             * @brief Заполнить матрицу с помощью генератора
             * @param gen ссылка на генератор значений
             */
            void fill(const Generator& gen);

            /**
             * @brief Получить количество строк
             * @return количество строк матрицы
             */
            size_t getRows() const noexcept { return rows; }

            /**
             * @brief Получить количество столбцов
             * @return количество столбцов матрицы
             */
            size_t getCols() const noexcept { return cols; }

            /**
             * @brief Проверить, является ли матрица пустой
             * @return true, если матрица не содержит строк или столбцов
             */
            bool empty() const noexcept { return rows == 0 || cols == 0; }

            /**
             * @brief Собирает матрицу в строку, чтобы её было удобно вывести.
             * @return строка вида "[ a, b ]\n[ c, d ]" (или пустая строка для пустой матрицы)
             */
            std::string toString() const;

            /**
             * @brief Вставляет новую строку сразу после указанной позиции.
             * @param pos индекс строки, после которой выполняется вставка (0 .. rows - 1)
             * @param row строка из cols элементов
             * @throw std::out_of_range если pos не указывает на существующую строку
             * @throw std::invalid_argument если в row не ровно cols элементов
             */
            void insertRow(const size_t pos, const std::vector<T>& row);

            /**
             * @brief Оператор сравнения на равенство
             * @param other матрица для сравнения
             * @return true, если размеры и элементы совпадают
             */
            bool operator==(const Matrix& other) const
            {
                return rows == other.rows && cols == other.cols && data == other.data;
            }

            /**
             * @brief Оператор сравнения на неравенство
             * @param other матрица для сравнения
             * @return true, если размеры или элементы отличаются
             */
            bool operator!=(const Matrix& other) const
            {
                return !(*this == other);
            }
        };

        template <typename T>
        Matrix<T>::Matrix() noexcept
            : rows(0), cols(0), data{}
        {
        }

        template <typename T>
        Matrix<T>::Matrix(const size_t rows, const size_t cols)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{}))
        {
        }

        template <typename T>
        Matrix<T>::Matrix(const size_t rows, const size_t cols, const T& value)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, value))
        {
        }

        template <typename T>
        Matrix<T>::Matrix(const size_t rows, const size_t cols, const Generator& gen)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{}))
        {
            fill(gen);
        }

        template <typename T>
        std::vector<T>& Matrix<T>::operator[](const size_t index)
        {
            if (index >= rows)
            {
                throw std::out_of_range("Matrix row index out of range");
            }
            return data[index];
        }

        template <typename T>
        const std::vector<T>& Matrix<T>::operator[](const size_t index) const
        {
            if (index >= rows)
            {
                throw std::out_of_range("Matrix row index out of range");
            }
            return data[index];
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator<<(const size_t shift)
        {
            if (shift >= rows)
            {
                data.clear();
                rows = 0;
            }
            else
            {
                data.erase(data.begin(), data.begin() + shift);
                rows -= shift;
            }
            return *this;
        }

        template <typename T>
        Matrix<T>& Matrix<T>::operator>>(const size_t shift)
        {
            for (size_t s = 0; s < shift; ++s)
            {
                data.insert(data.begin(), std::vector<T>(cols, T{}));
                ++rows;
            }
            return *this;
        }

        template <typename T>
        void Matrix<T>::fill(const Generator& gen)
        {
            for (size_t i = 0; i < rows; ++i)
            {
                for (size_t j = 0; j < cols; ++j)
                {
                    data[i][j] = static_cast<T>(gen.generate());
                }
            }
        }

        template <typename T>
        std::string Matrix<T>::toString() const
        {
            if (rows == 0 || cols == 0)
            {
                return "";
            }

            std::ostringstream oss;
            for (size_t i = 0; i < rows; ++i)
            {
                oss << "[ ";
                for (size_t j = 0; j < cols; ++j)
                {
                    oss << data[i][j];
                    if (j + 1 < cols)
                    {
                        oss << ", ";
                    }
                }
                oss << " ]";
                if (i + 1 < rows)
                {
                    oss << "\n";
                }
            }
            return oss.str();
        }

        template <typename T>
        void Matrix<T>::insertRow(const size_t pos, const std::vector<T>& row)
        {
            if (pos >= rows)
            {
                throw std::out_of_range("Matrix row position out of range");
            }
            if (row.size() != cols)
            {
                throw std::invalid_argument("Inserted row has incorrect size");
            }
            data.insert(data.begin() + pos + 1, row);
            ++rows;
        }
    }
}
