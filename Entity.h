#pragma once
#include "Values.h"

namespace miit::bakery
{
    /**
     * @brief Объект с автоматически созданным уникальным ключом.
     * Ключи общие для всех сущностей, не изменяются и не используются повторно.
     * Копирование и перемещение запрещены, чтобы не дублировать ключи.
     */
    class Entity
    {
    private:
        static Id nextId;
        const Id id;
        static Id createId();
    protected:
        Entity();
    public:
        virtual ~Entity() = default;
        Entity(const Entity&) = delete;
        Entity& operator=(const Entity&) = delete;
        Entity(Entity&&) = delete;
        Entity& operator=(Entity&&) = delete;
        /** @brief Возвращает неизменяемый положительный ключ объекта. */
        Id getId() const noexcept;
    };
}
