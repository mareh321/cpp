#include "Product.h"
#include <stdexcept>

miit::bakery::Product::Product(const std::string& name, const Money price,
    const Quantity weightGrams)
    : name(requireText(name)), price(price), weightGrams(weightGrams)
{
    if (price <= 0 || weightGrams <= 0)
        throw std::invalid_argument("Цена и масса продукции должны быть положительными.");
}
const std::string& miit::bakery::Product::getName() const noexcept { return name; }
miit::bakery::Money miit::bakery::Product::getPrice() const noexcept { return price; }
miit::bakery::Quantity miit::bakery::Product::getWeightGrams() const noexcept { return weightGrams; }
