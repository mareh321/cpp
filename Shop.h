#pragma once
#include "Entity.h"
#include <string>

namespace miit::bakery
{
    /**
     * @brief Магазин, заказывающий готовую продукцию.
     */
    class Shop final : public Entity
    {
    private:
        /** @brief Название магазина. */
        std::string name;
        /** @brief Адрес магазина. */
        std::string address;
    public:
        /**
         * @brief Создаёт новую запись с автоматически выданным ID.
         * @param name Непустое название.
         * @param address Непустой адрес.
         * @throw std::invalid_argument Если название или адрес пусты после удаления пробелов.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        Shop(const std::string& name, const std::string& address);
        /**
         * @brief Возвращает название.
         * @return Константная ссылка на название.
         */
        const std::string& getName() const noexcept;
        /**
         * @brief Возвращает адрес.
         * @return Константная ссылка на адрес.
         */
        const std::string& getAddress() const noexcept;
    };
}
