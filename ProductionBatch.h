#pragma once
#include "Entity.h"
#include "Date.h"

namespace miit::bakery
{
    /** @brief Партия фактически произведённой продукции*/
    class ProductionBatch final : public Entity
    {
    private:
        Id productId;
        Date date;
        Quantity quantity;
    public:
        /** @brief Создаёт партию продукции с указанными ID изделия, датой и количеством. */
        ProductionBatch(const Id productId, const Date& date, const Quantity quantity);
         /**
         * @brief Возвращает ключ продукции.
         * @return ID продукции.
         */
        Id getProductId() const noexcept;
        /**
         * @brief Возвращает дату записи.
         * @return Константная ссылка на дату.
         */
        const Date& getDate() const noexcept;
        /**
         * @brief Возвращает количество.
         * @return Количество изделий в штуках.
         */
        Quantity getQuantity() const noexcept;
    };
}
