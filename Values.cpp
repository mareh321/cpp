#include "Values.h"
#include <limits>
#include <stdexcept>

namespace miit::bakery
{
    std::string requireText(const std::string& text)
    {
        const auto first = text.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
            throw std::invalid_argument("Текст не может быть пустым.");
        return text.substr(first, text.find_last_not_of(" \t\r\n") - first + 1);
    }

    void requireId(const Id id)
    {
        if (id == 0) throw std::invalid_argument("ID должен быть положительным.");
    }

    std::int64_t checkedAdd(const std::int64_t left, const std::int64_t right)
    {
        if (left < 0 || right < 0) throw std::invalid_argument("Отрицательное значение.");
        if (left > (std::numeric_limits<std::int64_t>::max)() - right)
            throw std::overflow_error("Переполнение суммы.");
        return left + right;
    }

    std::int64_t checkedMultiply(const std::int64_t left, const std::int64_t right)
    {
        if (left < 0 || right < 0) throw std::invalid_argument("Отрицательное значение.");
        if (right != 0 && left > (std::numeric_limits<std::int64_t>::max)() / right)
            throw std::overflow_error("Переполнение произведения.");
        return left * right;
    }

    std::string formatMoney(const Money value)
    {
        if (value < 0) throw std::invalid_argument("Сумма не может быть отрицательной.");
        const auto cents = value % 100;
        return std::to_string(value / 100) + "." + (cents < 10 ? "0" : "")
            + std::to_string(cents) + " руб.";
    }

    std::string unitName(const Unit unit)
    {
        switch (unit)
        {
        case Unit::Gram: return "г";
        case Unit::Milliliter: return "мл";
        case Unit::Piece: return "шт.";
        default: throw std::invalid_argument("Неизвестная единица измерения.");
        }
    }
}
