#pragma once
#include "Generator.h"

namespace miit::algebra
{
    /**
     * @brief Генератор константного значения
     */
    class ConstGenerator : public Generator
    {
    private:
        /**
         * @brief Значение, которое генератор возвращает при каждом вызове.
         */
        const int value;

    public:
        /**
         * @brief Конструктор
         * @param value Значение, которое возвращает генератор
         */
        explicit ConstGenerator(const int value);

        /**
         * @brief Получить константное значение
         * @return Значение, переданное в конструктор
         */
        int generate() override;
    };
}
