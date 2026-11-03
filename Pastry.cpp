#include "Pastry.h"

miit::bakery::Pastry::Pastry(const std::string& name, const Money price,
    const Quantity weightGrams, const std::string& filling)
    : Product(name, price, weightGrams), filling(requireText(filling)) {}
const std::string& miit::bakery::Pastry::getFilling() const noexcept { return filling; }
std::string miit::bakery::Pastry::toString() const
{
    return "Выпечка: " + getName() + "; начинка: " + filling + "; масса: "
        + std::to_string(getWeightGrams()) + " г; цена: " + formatMoney(getPrice());
}
