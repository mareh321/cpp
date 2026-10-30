#include "Task1.h"
#include <utility>

miit::algebra::Task1::Task1(Matrix<int> matrix)
    : Exercise(std::move(matrix))
{
}

miit::algebra::Task1::Task1(const size_t rows, const size_t cols,const Generator& generator)
    : Exercise(rows, cols, generator)
{
}

void miit::algebra::Task1::solve()
{
    if (this->matrix.getRows() == 0 || this->matrix.getCols() == 0)
    {
        return;
    }

    const size_t rows = this->matrix.getRows();
    const size_t cols = this->matrix.getCols();


    for (size_t j = 0; j < cols; ++j)
    {
        int maxVal = this->matrix[0][j];
        for (size_t i = 1; i < rows; ++i)
        {
            if (this->matrix[i][j] > maxVal)
            {
                maxVal = this->matrix[i][j];
            }
        }

        for (size_t i = 0; i < rows; ++i)
        {
            if (this->matrix[i][j] == maxVal)
            {
                this->matrix[i][j] = 0;
            }
        }
    }
}

std::string miit::algebra::Task1::description() const
{
    return "Заменить максимальный элемент каждого столбца нулем";
}
