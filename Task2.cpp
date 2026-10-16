#include "Task2.h"
#include <cstdlib>
#include <utility>
#include <vector>

miit::algebra::Task2::Task2(Matrix<int> matrix, const Generator* generator)
    : Exercise(std::move(matrix), generator)
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

    // 1. Находим максимальный по модулю элемент во всей матрице
    int maxAbsVal = std::abs(this->matrix[0][0]);
    for (size_t i = 0; i < initialRows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            const int currentAbs = std::abs(this->matrix[i][j]);
            if (currentAbs > maxAbsVal)
            {
                maxAbsVal = currentAbs;
            }
        }
    }

    // 2. Сохраняем исходную первую строку для вставки
    std::vector<int> firstRow = this->matrix[0];

    // 3. Проходим строки с конца к началу, чтобы вставка строк не сбивала индексы предыдущих строк
    for (size_t i = initialRows; i-- > 0; )
    {
        bool hasMaxAbs = false;
        for (size_t j = 0; j < cols; ++j)
        {
            if (std::abs(this->matrix[i][j]) == maxAbsVal)
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
