#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /** @brief Магазин, заказывающий готовую продукцию. */
    class Shop final : public Entity
    {
    private:
        std::string name;
        std::string address;
    public:
        Shop(const std::string& name, const std::string& address);
        const std::string& getName() const noexcept;
        const std::string& getAddress() const noexcept;
    };
}
