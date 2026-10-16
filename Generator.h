#pragma once

namespace miit::algebra
{
    /**
     * @brief Абстрактный базовый класс генератора значений
     */
    class Generator
    {
    public:
        /**
         * @brief Виртуальный деструктор
         */
        virtual ~Generator() = default;

        /**
         * @brief Сгенерировать очередное целое число
         * @return Сгенерированное значение
         */
        virtual int generate() = 0;
    };
}
