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
        * @brief Создаёт непустой заказ без повторяющихся ID товаров
        * и проверяет переполнение общей стоимости.
        * Существование магазина и продукции проверяет Bakery.
        */
        ShopOrder(const Id shopId, const Date& date, std::vector<OrderLine> lines);
        /** @brief Возвращает ID магазина, оформившего заказ. */
        Id getShopId() const noexcept;
        /** @brief Возвращает дату заказа. */
        const Date& getDate() const noexcept;
        /** @brief Возвращает позиции заказа для чтения. */
        const std::vector<OrderLine>& getLines() const noexcept;
        /** @brief Возвращает общую стоимость заказа в копейках. */
        Money getTotal() const noexcept;
    };
}
