#include "Entity.h"
#include <limits>
#include <stdexcept>

miit::bakery::Id miit::bakery::Entity::nextId = 1;

miit::bakery::Id miit::bakery::Entity::createId()
{
    if (nextId == (std::numeric_limits<Id>::max)())
        throw std::overflow_error("Закончились свободные идентификаторы.");
    return nextId++;
}

miit::bakery::Entity::Entity() : id(createId()) {}
miit::bakery::Id miit::bakery::Entity::getId() const noexcept { return id; }
