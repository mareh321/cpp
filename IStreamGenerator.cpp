#include "IStreamGenerator.h"
#include <iostream>
#include <stdexcept>

miit::algebra::IStreamGenerator::IStreamGenerator(std::istream& in)
    : in{ in }
{
}

miit::algebra::IStreamGenerator::IStreamGenerator()
    : in{ std::cin }
{
}

int miit::algebra::IStreamGenerator::generate()
{
    int value = 0;
    if (!(this->in >> value))
    {
        throw std::runtime_error("IStreamGenerator: failed to read integer from stream");
    }
    return value;
}
