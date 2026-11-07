#include "Bread.h"

miit::bakery::Bread::Bread(const std::string& name, const Money price,
    const Quantity weightGrams, const std::string& flourType)
    : Product(name, price, weightGrams), flourType(requireText(flourType)) {}
const std::string& miit::bakery::Bread::getFlourType() const noexcept { return flourType; }
std::string miit::bakery::Bread::toString() const
{
    return "Хлеб: " + getName() + "; мука: " + flourType + "; масса: "
        + std::to_string(getWeightGrams()) + " г; цена: " + formatMoney(getPrice());
}
