#pragma once
#include <cstdint>
#include <string>

namespace miit::bakery
{
    using Id = std::uint64_t;
    using Quantity = std::int64_t;
    using Money = std::int64_t; // Сумма в копейках.

    /** @brief Единица измерения количества сырья. */
    enum class Unit { Gram, Milliliter, Piece };

    /** @brief Удаляет пробелы по краям; отклоняет пустой текст. */
    std::string requireText(const std::string& text);
    /** @brief Проверяет, что идентификатор не равен нулю. */
    void requireId(const Id id);
    /** @brief Складывает неотрицательные числа с проверкой переполнения. */
    std::int64_t checkedAdd(const std::int64_t left, const std::int64_t right);
    /** @brief Умножает неотрицательные числа с проверкой переполнения. */
    std::int64_t checkedMultiply(const std::int64_t left, const std::int64_t right);
    /** @brief Возвращает сумму в формате «125.50 руб.». */
    std::string formatMoney(const Money value);
    /** @brief Возвращает обозначение единицы измерения. */
    std::string unitName(const Unit unit);
}
