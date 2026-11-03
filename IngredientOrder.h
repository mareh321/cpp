#pragma once
#include "Entity.h"
#include "Date.h"

namespace miit::bakery
{
    /**
     * @brief Заказ одного вида сырья у поставщика на определённую дату.
     */
    class IngredientOrder final : public Entity
    {
    private:
        Id supplierId;
        Id ingredientId;
        Date date;
        Quantity quantity;
        Money unitPrice;
        Money total;
    public:
        /**
         * @brief Создаёт заказ сырья и рассчитывает его стоимость.
         * @param supplierId Положительный ID поставщика.
         * @param ingredientId Положительный ID сырья.
         * @param date Дата заказа.
         * @param quantity Положительное количество в единицах выбранного сырья.
         * @param unitPrice Неотрицательная цена одной единицы в копейках.
         * @throw std::invalid_argument Если ID, количество или цена недопустимы.
         * @throw std::overflow_error Если стоимость не помещается в Money.
         * @note Существование поставщика и сырья проверяет Bakery до добавления заказа.
         */
        IngredientOrder(const Id supplierId, const Id ingredientId, const Date& date,
            const Quantity quantity, const Money unitPrice);
        /**
         * @brief Возвращает ключ поставщика.
         * @return ID поставщика.
         */
        Id getSupplierId() const noexcept;
        /**
         * @brief Возвращает ключ сырья.
         * @return ID сырья.
         */
        Id getIngredientId() const noexcept;
        /**
         * @brief Возвращает дату записи.
         * @return Константная ссылка на дату.
         */
        const Date& getDate() const noexcept;
        /**
         * @brief Возвращает количество.
         * @return Количество в единицах сырья.
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
