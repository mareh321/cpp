#include "ConstGenerator.h"

miit::algebra::ConstGenerator::ConstGenerator(const int value)
    : value{ value }
{
}

int miit::algebra::ConstGenerator::generate()
{
    return this->value;
}
