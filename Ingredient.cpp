#include "Ingredient.h"

miit::bakery::Ingredient::Ingredient(const std::string& name, const Unit unit)
    : name(requireText(name)), unit(unit) { (void)unitName(unit); }
const std::string& miit::bakery::Ingredient::getName() const noexcept { return name; }
miit::bakery::Unit miit::bakery::Ingredient::getUnit() const noexcept { return unit; }
