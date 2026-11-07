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
        /** @brief Создаёт поставщика с указанными названием и адресом; ID выдаётся автоматически. */
        Supplier(const std::string& name, const std::string& address);
        /** @brief Возвращает название поставщика. */
        const std::string& getName() const noexcept;
        /** @brief Возвращает адрес поставщика. */
        const std::string& getAddress() const noexcept;
    };
}
