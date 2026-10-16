#include "RandomGenerator.h"
#include <stdexcept>

miit::algebra::RandomGenerator::RandomGenerator(const int min, const int max)
{
    if (min > max)
    {
        throw std::invalid_argument("RandomGenerator: min must be less than or equal to max");
    }
    this->generator = std::mt19937(std::random_device{}());
    this->distribution = std::uniform_int_distribution<int>(min, max);
}

int miit::algebra::RandomGenerator::generate()
{
    return this->distribution(this->generator);
}
