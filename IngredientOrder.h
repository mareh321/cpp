#pragma once
#include "Entity.h"
#include "Date.h"

namespace miit::bakery
{
    /** @brief Заказ одного вида сырья у поставщика на определённую дату. */
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
         * @brief Создаёт заказ с положительными ID и количеством, неотрицательной ценой.
         * Существование поставщика и сырья проверяет Bakery перед созданием заказа.
         * @param unitPrice цена в копейках за одну единицу измерения сырья
         */
        IngredientOrder(const Id supplierId, const Id ingredientId, const Date& date,
            const Quantity quantity, const Money unitPrice);
        Id getSupplierId() const noexcept;
        Id getIngredientId() const noexcept;
        const Date& getDate() const noexcept;
        Quantity getQuantity() const noexcept;
        Money getUnitPrice() const noexcept;
        Money getTotal() const noexcept;
    };
}
