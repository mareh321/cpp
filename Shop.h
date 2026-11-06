#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /** @brief Заказ магазина из одной или нескольких различных позиций. */
    class Shop final : public Entity
    {
    private:
        std::string name;
        std::string address;
    public:
        /** @brief Создаёт магазин с указанными названием и адресом; ID выдаётся автоматически. */
        Shop(const std::string& name, const std::string& address);
        /** @brief Возвращает название магазина. */
        const std::string& getName() const noexcept;
        /** @brief Возвращает адрес магазина. */
        const std::string& getAddress() const noexcept;
    };
}
