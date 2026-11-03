#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /**
     * @brief Абстрактный базовый класс готовой продукции хлебопекарни.
     */
    class Product : public Entity
    {
    private:
        std::string name;
        Money price;
        Quantity weightGrams;
    protected:
        /**
         * @brief Создаёт новую запись готовой продукции.
         * @param name Непустое название изделия.
         * @param price Положительная цена одной штуки в копейках.
         * @param weightGrams Положительная масса одной штуки в граммах.
         * @throw std::invalid_argument Если название пустое, цена или масса неположительна.
         */
        Product(const std::string& name, const Money price, const Quantity weightGrams);
    public:
        /**
         * @brief Виртуальный деструктор базового класса продукции.
         */
        virtual ~Product() = default;
        /**
         * @brief Стандартный конструктор копирования.
         * @param other Исходный объект.
         * @note Данные и ID копируются; новые ключи не создаются.
         */
        Product(const Product& other) = default;
        /**
         * @brief Стандартное присваивание копированием.
         * @param other Объект, данные и ID которого заменяют текущие.
         * @return Ссылка на текущий объект.
         */
        Product& operator=(const Product& other) = default;
        /**
         * @brief Стандартный конструктор перемещения.
         * @param other Объект, из которого переносятся данные.
         * @note Сохраняются ключи переносимых записей. Исходный объект можно уничтожить или присвоить ему новое значение.
         */
        Product(Product&& other) noexcept = default;
        /**
         * @brief Стандартное присваивание перемещением.
         * @param other Объект, из которого переносятся данные и ID.
         * @return Ссылка на текущий объект.
         * @note Исходный объект можно уничтожить или присвоить ему новое значение.
         */
        Product& operator=(Product&& other) noexcept = default;
        /**
         * @brief Возвращает название продукции.
         * @return Константная ссылка на название.
         */
        const std::string& getName() const noexcept;
        /**
         * @brief Возвращает цену одной штуки.
         * @return Цена в копейках.
         */
        Money getPrice() const noexcept;
        /**
         * @brief Возвращает массу одной штуки.
         * @return Масса в граммах.
         */
        Quantity getWeightGrams() const noexcept;
        /**
         * @brief Формирует описание конкретного вида продукции.
         * @return Строка, определяемая классом-наследником.
         */
        virtual std::string toString() const = 0;
    };
}
