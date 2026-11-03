#include "OrderLine.h"
#include <stdexcept>

miit::bakery::OrderLine::OrderLine(const Id productId, const Quantity quantity, const Money unitPrice)
    : productId(productId), quantity(quantity), unitPrice(unitPrice),
      total(checkedMultiply(quantity, unitPrice))
{
    requireId(productId);
    if (quantity <= 0) throw std::invalid_argument("Количество изделий должно быть положительным.");
}
miit::bakery::Id miit::bakery::OrderLine::getProductId() const noexcept { return productId; }
miit::bakery::Quantity miit::bakery::OrderLine::getQuantity() const noexcept { return quantity; }
miit::bakery::Money miit::bakery::OrderLine::getUnitPrice() const noexcept { return unitPrice; }
miit::bakery::Money miit::bakery::OrderLine::getTotal() const noexcept { return total; }
