#pragma once
#include "Entity.h"
#include "Date.h"
#include "OrderLine.h"
#include <vector>

namespace miit::bakery
{
    /**
     * @brief Заказ магазина с позициями и общей стоимостью.
     */
    class ShopOrder final : public Entity
    {
    private:
        /** @brief ID магазина, оформившего заказ. */
        Id shopId;
        /** @brief Дата оформления заказа магазина. */
        Date date;
        /** @brief Позиции заказа с различными ID продукции. */
        std::vector<OrderLine> lines;
        /** @brief Общая стоимость всех позиций заказа в копейках. */
        Money total;
    public:
        /**
         * @brief Создаёт непустой заказ и рассчитывает общую сумму.
         * @param shopId Положительный ID магазина.
         * @param date Дата оформления.
         * @param lines Позиции заказа; один товар может встретиться только один раз.
         * @throw std::invalid_argument Если ID равен нулю, список пуст или товар повторён.
         * @throw std::overflow_error Если общая сумма не помещается в Money или исчерпан диапазон ID.
         * @note Существование магазина и товаров проверяет Bakery. Цены позиций сохраняются в заказе.
         */
        ShopOrder(const Id shopId, const Date& date, std::vector<OrderLine> lines);
        /**
         * @brief Возвращает ключ магазина.
         * @return ID магазина.
         */
        Id getShopId() const noexcept;
        /**
         * @brief Возвращает дату записи.
         * @return Константная ссылка на дату.
         */
        const Date& getDate() const noexcept;
        /**
         * @brief Возвращает позиции заказа для чтения.
         * @return Константная ссылка на список позиций.
         */
        const std::vector<OrderLine>& getLines() const noexcept;
        /**
         * @brief Возвращает рассчитанную стоимость.
         * @return Сумма в копейках.
         */
        Money getTotal() const noexcept;
    };
}
