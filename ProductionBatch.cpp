#include "ProductionBatch.h"
#include <stdexcept>

miit::bakery::ProductionBatch::ProductionBatch(const Id productId, const Date& date,
    const Quantity quantity) : productId(productId), date(date), quantity(quantity)
{
    requireId(productId);
    if (quantity <= 0) throw std::invalid_argument("Объём производства должен быть положительным.");
}
miit::bakery::Id miit::bakery::ProductionBatch::getProductId() const noexcept { return productId; }
const miit::bakery::Date& miit::bakery::ProductionBatch::getDate() const noexcept { return date; }
miit::bakery::Quantity miit::bakery::ProductionBatch::getQuantity() const noexcept { return quantity; }
