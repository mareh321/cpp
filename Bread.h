#pragma once
#include "Product.h"

namespace miit::bakery
{
    /**
     * @brief Хлеб с указанием вида муки.
     */
    class Bread final : public Product
    {
    private:
        std::string flourType;
    public:
        /**
         * @brief Создаёт новое изделие.
         * @param name Непустое название изделия.
         * @param price Положительная цена одной штуки в копейках.
         * @param weightGrams Положительная масса одной штуки в граммах.
         * @param flourType Непустое название вида муки.
         * @throw std::invalid_argument Если строка пуста, цена или масса неположительна.
         */
        Bread(const std::string& name, const Money price, const Quantity weightGrams,
            const std::string& flourType);
        /**
         * @brief Возвращает дополнительную характеристику изделия.
         * @return Константная ссылка на вид муки.
         */
        const std::string& getFlourType() const noexcept;
        /**
         * @brief Формирует описание изделия с массой, ценой и характеристикой.
         * @return Строка для вывода в приложении.
         */
        std::string toString() const override;
    };
}
