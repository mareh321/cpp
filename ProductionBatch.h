#pragma once
#include "Entity.h"
#include "Date.h"

namespace miit::bakery
{
    /**
     * @brief Запись о фактически произведённой партии изделий.
     */
    class ProductionBatch final : public Entity
    {
    private:
        /** @brief ID произведённого изделия. */
        Id productId;
        /** @brief Дата фактического производства партии. */
        Date date;
        /** @brief Количество произведённых изделий в штуках. */
        Quantity quantity;
    public:
        /**
         * @brief Регистрирует объём производства на дату.
         * @param productId Положительный ID продукции.
         * @param date Дата производства.
         * @param quantity Положительное количество произведённых штук.
         * @throw std::invalid_argument Если ID равен нулю или количество неположительно.
         * @note Существование продукции проверяет Bakery до добавления записи.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
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
