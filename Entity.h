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
        Id id;
        static Id createId();
    protected:
        Entity();
    public:
        virtual ~Entity() = default;
        Entity(const Entity& other) = default;
        Entity& operator=(const Entity& other) = default;
        Entity(Entity&& other) noexcept = default;
        Entity& operator=(Entity&& other) noexcept = default;
        /** @brief Возвращает неизменяемый положительный ключ объекта. */
        Id getId() const noexcept;
    };
}
