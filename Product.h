#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /** @brief Абстрактный базовый класс готовой продукции хлебопекарни. */
    class Product : public Entity
    {
    private:
        std::string name;
        Money price;
        Quantity weightGrams;
    protected:
        /** @brief Создаёт продукцию с положительными ценой и массой. */
        Product(const std::string& name, const Money price, const Quantity weightGrams);
    public:
        virtual ~Product() = default;
        Product(const Product& other) = default;
        Product& operator=(const Product& other) = default;
        Product(Product&& other) noexcept = default;
        Product& operator=(Product&& other) noexcept = default;
        const std::string& getName() const noexcept;
        /** @brief Цена одной штуки в копейках. */
        Money getPrice() const noexcept;
        Quantity getWeightGrams() const noexcept;
        /** @brief Возвращает описание, определяемое конкретным видом продукции. */
        virtual std::string toString() const = 0;
    };
}
