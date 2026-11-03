#pragma once
#include "Product.h"

namespace miit::bakery
{
    /**
     * @brief Выпечка с указанием начинки.
     */
    class Pastry final : public Product
    {
    private:
        std::string filling;
    public:
        /**
         * @brief Создаёт новое изделие.
         * @param name Непустое название изделия.
         * @param price Положительная цена одной штуки в копейках.
         * @param weightGrams Положительная масса одной штуки в граммах.
         * @param filling Непустое название начинки.
         * @throw std::invalid_argument Если строка пуста, цена или масса неположительна.
         */
        Pastry(const std::string& name, const Money price, const Quantity weightGrams,
            const std::string& filling);
        /**
         * @brief Возвращает дополнительную характеристику изделия.
         * @return Константная ссылка на начинку.
         */
        const std::string& getFilling() const noexcept;
        /**
         * @brief Формирует описание изделия с массой, ценой и характеристикой.
         * @return Строка для вывода в приложении.
         */
        std::string toString() const override;
    };
}
