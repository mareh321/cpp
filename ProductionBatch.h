#pragma once
#include "Entity.h"
#include "Date.h"

namespace miit::bakery
{
    /** @brief Партия фактически произведённой продукции; количество в штуках. */
    class ProductionBatch final : public Entity
    {
    private:
        Id productId;
        Date date;
        Quantity quantity;
    public:
        ProductionBatch(const Id productId, const Date& date, const Quantity quantity);
        Id getProductId() const noexcept;
        const Date& getDate() const noexcept;
        Quantity getQuantity() const noexcept;
    };
}
