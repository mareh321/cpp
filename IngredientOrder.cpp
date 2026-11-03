#include "IngredientOrder.h"
#include <stdexcept>

miit::bakery::IngredientOrder::IngredientOrder(const Id supplierId, const Id ingredientId,
    const Date& date, const Quantity quantity, const Money unitPrice)
    : supplierId(supplierId), ingredientId(ingredientId), date(date), quantity(quantity),
      unitPrice(unitPrice), total(checkedMultiply(quantity, unitPrice))
{
    requireId(supplierId);
    requireId(ingredientId);
    if (quantity <= 0) throw std::invalid_argument("Количество сырья должно быть положительным.");
}
miit::bakery::Id miit::bakery::IngredientOrder::getSupplierId() const noexcept { return supplierId; }
miit::bakery::Id miit::bakery::IngredientOrder::getIngredientId() const noexcept { return ingredientId; }
const miit::bakery::Date& miit::bakery::IngredientOrder::getDate() const noexcept { return date; }
miit::bakery::Quantity miit::bakery::IngredientOrder::getQuantity() const noexcept { return quantity; }
miit::bakery::Money miit::bakery::IngredientOrder::getUnitPrice() const noexcept { return unitPrice; }
miit::bakery::Money miit::bakery::IngredientOrder::getTotal() const noexcept { return total; }
