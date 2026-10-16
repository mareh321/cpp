#include "Task2.h"
#include <utility>
#include <vector>

namespace
{
    long long absAsLongLong(const int value) noexcept
    {
        const long long wideValue = value;
        return wideValue < 0 ? -wideValue : wideValue;
    }
}

miit::algebra::Task2::Task2(Matrix<int> matrix)
    : Exercise(std::move(matrix))
{
}

miit::algebra::Task2::Task2(Matrix<int> matrix, const Generator& generator)
    : Exercise(std::move(matrix), &generator)
{
}

miit::algebra::Task2::Task2(const size_t rows, const size_t cols, const Generator& generator)
    : Exercise(rows, cols, generator)
{
}

void miit::algebra::Task2::solve()
{
    if (this->matrix.getRows() == 0 || this->matrix.getCols() == 0)
    {
        return;
    }

    const size_t initialRows = this->matrix.getRows();
    const size_t cols = this->matrix.getCols();

    // Сначала находим наибольший модуль во всей матрице.
    long long maxAbsVal = absAsLongLong(this->matrix[0][0]);
    for (size_t i = 0; i < initialRows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            const long long currentAbs = absAsLongLong(this->matrix[i][j]);
            if (currentAbs > maxAbsVal)
            {
                maxAbsVal = currentAbs;
            }
        }
    }

    // Сохраняем первую строку: именно её нужно добавлять после найденных строк.
    std::vector<int> firstRow = this->matrix[0];

    // Идём с конца, чтобы вставленные строки не сдвигали ещё не проверенные индексы.
    for (size_t i = initialRows; i-- > 0; )
    {
        bool hasMaxAbs = false;
        for (size_t j = 0; j < cols; ++j)
        {
            if (absAsLongLong(this->matrix[i][j]) == maxAbsVal)
            {
                hasMaxAbs = true;
                break;
            }
        }

        if (hasMaxAbs)
        {
            this->matrix.insertRow(i, firstRow);
        }
    }
}

std::string miit::algebra::Task2::description() const
{
    return "Вставить после всех строк, содержащих максимальный по модулю элемент, первую строку";
}
