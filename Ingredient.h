#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /** @brief Сырьё, учитываемое в граммах, миллилитрах или штуках. */
    class Ingredient final : public Entity
    {
    private:
        std::string name;
        Unit unit;
    public:
        Ingredient(const std::string& name, const Unit unit);
        const std::string& getName() const noexcept;
        Unit getUnit() const noexcept;
    };
}
