#include "ShopOrder.h"
#include <set>
#include <stdexcept>
#include <utility>

miit::bakery::ShopOrder::ShopOrder(const Id shopId, const Date& date, std::vector<OrderLine> lines)
    : shopId(shopId), date(date), lines(std::move(lines)), total(0)
{
    requireId(shopId);
    if (this->lines.empty()) throw std::invalid_argument("Заказ магазина не может быть пустым.");
    std::set<Id> seen;
    for (const auto& line : this->lines)
    {
        if (!seen.insert(line.getProductId()).second)
            throw std::invalid_argument("Товар повторяется в заказе.");
        total = checkedAdd(total, line.getTotal());
    }
}
miit::bakery::Id miit::bakery::ShopOrder::getShopId() const noexcept { return shopId; }
const miit::bakery::Date& miit::bakery::ShopOrder::getDate() const noexcept { return date; }
const std::vector<miit::bakery::OrderLine>& miit::bakery::ShopOrder::getLines() const noexcept { return lines; }
miit::bakery::Money miit::bakery::ShopOrder::getTotal() const noexcept { return total; }
