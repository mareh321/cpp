#pragma once
#include "Values.h"

namespace miit::bakery
{
    /**
     * @brief Одна позиция заказа с сохранённой ценой за штуку.
     * @note Копирование сохраняет все значения; собственный ID для позиции не требуется.
     */
    class OrderLine
    {
    private:
        Id productId;
        Quantity quantity;
        Money unitPrice;
        Money total;
    public:
        /**
         * @brief Создаёт позицию и рассчитывает её стоимость.
         * @param productId Положительный ID продукции.
         * @param quantity Положительное количество штук.
         * @param unitPrice Неотрицательная цена штуки в копейках.
         * @throw std::invalid_argument Если ID, количество или цена недопустимы.
         * @throw std::overflow_error Если стоимость не помещается в Money.
         */
        OrderLine(const Id productId, const Quantity quantity, const Money unitPrice);
        /**
         * @brief Возвращает ключ продукции.
         * @return ID продукции.
         */
        Id getProductId() const noexcept;
        /**
         * @brief Возвращает количество.
         * @return Количество изделий в штуках.
         */
        Quantity getQuantity() const noexcept;
        /**
         * @brief Возвращает цену единицы на момент заказа.
         * @return Цена в копейках.
         */
        Money getUnitPrice() const noexcept;
        /**
         * @brief Возвращает рассчитанную стоимость.
         * @return Сумма в копейках.
         */
        Money getTotal() const noexcept;
    };
}
