#pragma once
#include "Values.h"

namespace miit::bakery
{
    /** @brief Позиция заказа; цена сохраняется на момент оформления. */
    class OrderLine
    {
    private:
        Id productId;
        Quantity quantity;
        Money unitPrice;
        Money total;
    public:
        /** @brief Проверяет положительные ID и количество, цену и переполнение суммы. */
        OrderLine(const Id productId, const Quantity quantity, const Money unitPrice);
        Id getProductId() const noexcept;
        Quantity getQuantity() const noexcept;
        Money getUnitPrice() const noexcept;
        Money getTotal() const noexcept;
    };
}
