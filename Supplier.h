#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /** @brief Поставщик продуктов для хлебопекарни. */
    class Supplier final : public Entity
    {
    private:
        std::string name;
        std::string address;
    public:
        Supplier(const std::string& name, const std::string& address);
        const std::string& getName() const noexcept;
        const std::string& getAddress() const noexcept;
    };
}
