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
         * @brief Шаблонный класс двумерного массива (матрицы)
         * @tparam T тип хранимых элементов
         */
        template <typename T>
        class Matrix
        {
        private:
            /** 
             * @brief Внутреннее хранилище элементов (вектор строк)
             */
            std::vector<std::vector<T>> data;

            /**
             * @brief Количество строк
             */
            size_t rows;

            /**
             * @brief Количество столбцов
             */
            size_t cols;

        public:
            /**
             * @brief Конструктор по умолчанию (создает пустую матрицу 0x0)
             */
            Matrix() noexcept;

            /**
             * @brief Конструктор с заданными размерами (инициализирует элементы значением по умолчанию T{})
             * @param rows количество строк
             * @param cols количество столбцов
             */
            Matrix(const size_t rows, const size_t cols);

            /**
             * @brief Конструктор с заданными размерами и начальным значением элементов
             * @param rows количество строк
             * @param cols количество столбцов
             * @param value значение для заполнения всех элементов матрицы
             */
            Matrix(const size_t rows, const size_t cols, const T& value);

            /**
             * @brief Конструктор с заданными размерами и заполнением с помощью генератора
             * @param rows количество строк
             * @param cols количество столбцов
             * @param gen генератор для формирования элементов
             */
            Matrix(const size_t rows, const size_t cols, Generator& gen);

            /**
             * @brief Конструктор с заданными размерами и заполнением с помощью константного генератора
             * @param rows количество строк
             * @param cols количество столбцов
             * @param gen константная ссылка на генератор
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
             * @brief Оператор доступа к строке матрицы по индексу (неконстантный)
             * @param index индекс строки (0 .. rows - 1)
             * @return ссылка на вектор элементов строки
             * @throw std::out_of_range при выходе индекса за границы
             */
            std::vector<T>& operator[](const size_t index);

            /**
             * @brief Оператор доступа к строке матрицы по индексу (константный)
             * @param index индекс строки (0 .. rows - 1)
             * @return константная ссылка на вектор элементов строки
             * @throw std::out_of_range при выходе индекса за границы
             */
            const std::vector<T>& operator[](const size_t index) const;

            /**
             * @brief Оператор сдвига влево (удаление первых shift строк матрицы)
             * @param shift количество удаляемых верхних строк
             * @return ссылка на текущий объект
             */
            Matrix& operator<<(const size_t shift);

            /**
             * @brief Оператор сдвига вправо (добавление shift пустых/нулевых строк в начало матрицы)
             * @param shift количество добавляемых верхних строк
             * @return ссылка на текущий объект
             */
            Matrix& operator>>(const size_t shift);

            /**
             * @brief Заполнить матрицу с помощью генератора
             * @param gen ссылка на генератор значений
             */
            void fill(Generator& gen);

            /**
             * @brief Заполнить матрицу с помощью константного генератора
             * @param gen константная ссылка на генератор значений
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
             * @brief Представление матрицы в виде форматированной строки
             * @return строка вида "[ a, b ]\n[ c, d ]" (или пустая строка для пустой матрицы)
             */
            std::string toString() const;

            /**
             * @brief Вставить строку после указанной позиции
             * @param pos индекс строки, после которой выполняется вставка (0 .. rows - 1)
             * @param row вектор значений для вставки
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
        Matrix<T>::Matrix(const size_t rows, const size_t cols, Generator& gen)
            : rows(rows), cols(cols), data(rows, std::vector<T>(cols, T{}))
        {
            fill(gen);
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
        void Matrix<T>::fill(Generator& gen)
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
        void Matrix<T>::fill(const Generator& gen)
        {
            fill(const_cast<Generator&>(gen));
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
                return;
            }
            data.insert(data.begin() + pos + 1, row);
            ++rows;
        }
    }
}
