#pragma once
#include "Entity.h"
#include "Date.h"
#include "OrderLine.h"
#include <vector>

namespace miit::bakery
{
    /** @brief Заказ магазина из одной или нескольких различных позиций. */
    class ShopOrder final : public Entity
    {
    private:
        Id shopId;
        Date date;
        std::vector<OrderLine> lines;
        Money total;
    public:
        /**
         * @brief Создаёт непустой заказ, запрещает повтор товара и переполнение суммы.
         * Существование магазина и продукции проверяет Bakery.
         */
        ShopOrder(const Id shopId, const Date& date, std::vector<OrderLine> lines);
        Id getShopId() const noexcept;
        const Date& getDate() const noexcept;
        const std::vector<OrderLine>& getLines() const noexcept;
        Money getTotal() const noexcept;
    };
}
