#include "Exercise.h"
#include <stdexcept>
#include <utility>

miit::algebra::Exercise::Exercise(Matrix<int> matrix, const Generator* generator)
    : matrix(std::move(matrix)), generator(generator)
{
}

miit::algebra::Exercise::Exercise(const size_t rows, const size_t cols, const Generator& generator)
    : matrix(rows, cols, generator), generator(&generator)
{
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
        if (this->generator == nullptr)
    {
        throw std::logic_error("Exercise has no generator");
    }
    this->matrix = std::move(newMatrix);
}

const miit::algebra::Generator& miit::algebra::Exercise::getGenerator() const
{
    return *this->generator;
}

void miit::algebra::Exercise::setGenerator(const Generator* gen) noexcept
{
    this->generator = gen;
}
