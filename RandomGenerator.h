#pragma once
#include "Generator.h"
#include <random>

namespace miit::algebra
{
    /**
     * @brief Генератор псевдослучайных чисел в заданном диапазоне
     */
    class RandomGenerator : public Generator
    {
    private:
        /**
         * @brief Генератор случайных чисел Mersenne Twister
         */
        std::mt19937 generator;

        /**
         * @brief Равномерное целочисленное распределение
         */
        std::uniform_int_distribution<int> distribution;

    public:
        /**
         * @brief Конструктор генератора
         * @param min Минимальная граница диапазона (включительно)
         * @param max Максимальная граница диапазона (включительно)
         * @throw std::invalid_argument если min > max
         */
        RandomGenerator(const int min, const int max);

        /**
         * @brief Сгенерировать случайное число в заданном диапазоне
         * @return Сгенерированное случайное число
         */
        int generate() cosnt override;
    };
}
