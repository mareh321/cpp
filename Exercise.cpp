#include "Exercise.h"
#include <utility>

miit::algebra::Exercise::Exercise(Matrix<int> matrix)
    : matrix(std::move(matrix))
{
}

miit::algebra::Exercise::Exercise(const size_t rows, const size_t cols, const Generator& generator)
    : matrix(rows, cols)
{
    this->matrix.fill(generator);
}

const miit::algebra::Matrix<int>& miit::algebra::Exercise::getMatrix() const noexcept
{
    return this->matrix;
}

miit::algebra::Matrix<int>& miit::algebra::Exercise::getMatrix() noexcept
{
    return this->matrix;
}

void miit::algebra::Exercise::setMatrix(Matrix<int> newMatrix)
{
    this->matrix = std::move(newMatrix);
}
