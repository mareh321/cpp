#pragma once
#include "Generator.h"
#include <istream>

namespace miit::algebra
{
    /**
     * @brief Генератор значений из входного потока
     */
    class IStreamGenerator : public Generator
    {
    private:
        /**
         * @brief Ссылка на входной поток данных
         */
        std::istream& in;

    public:
        /**
         * @brief Конструктор со ссылкой на входной поток
         * @param in Ссылка на входной поток
         */
        explicit IStreamGenerator(std::istream& in);

        /**
         * @brief Конструктор по умолчанию (использует стандартный поток ввода std::cin)
         */
        IStreamGenerator();

        /**
         * @brief Считать очередное целое число из входного потока
         * @return Считанное целое число
         * @throw std::runtime_error при ошибке чтения из потока
         */
        int generate() const override;
    };
}
