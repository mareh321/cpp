#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /**
     * @brief Вид сырья с выбранной единицей измерения.
     */
    class Ingredient final : public Entity
    {
    private:
        std::string name;
        Unit unit;
    public:
        /**
         * @brief Создаёт новый вид сырья.
         * @param name Непустое название сырья.
         * @param unit Граммы, миллилитры или штуки.
         * @throw std::invalid_argument Если название пусто или значение Unit не поддерживается.
         */
        Ingredient(const std::string& name, const Unit unit);
        /**
         * @brief Возвращает название сырья.
         * @return Константная ссылка на название.
         */
        const std::string& getName() const noexcept;
        /**
         * @brief Возвращает единицу измерения сырья.
         * @return Значение перечисления Unit.
         */
        Unit getUnit() const noexcept;
    };
}
