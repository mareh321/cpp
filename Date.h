#pragma once
#include <string>

namespace miit::bakery
{
    /** @brief Календарная дата без времени, годы от 1 до 9999. */
    class Date
    {
    private:
        int year;
        int month;
        int day;
    public:
        /** @brief Создаёт дату; при невозможной дате бросает invalid_argument. */
        Date(const int year, const int month, const int day);
        /** @brief Читает строго YYYY-MM-DD; проверяет високосный год и число дней. */
        explicit Date(const std::string& iso);
        /** @brief Возвращает дату в формате YYYY-MM-DD. */
        std::string toString() const;
        bool operator<(const Date& other) const noexcept;
        bool operator<=(const Date& other) const noexcept;
        bool operator==(const Date& other) const noexcept;
    };
}
