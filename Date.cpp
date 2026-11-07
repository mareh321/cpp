#include "Date.h"
#include <stdexcept>
#include <tuple>

namespace miit::bakery
{
    Date::Date(const int year, const int month, const int day)
        : year(year), month(month), day(day)
    {
        if (year < 1 || year > 9999 || month < 1 || month > 12)
            throw std::invalid_argument("Неверный год или месяц.");
        const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        const bool leap = year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
        const int limit = days[month - 1] + (month == 2 && leap ? 1 : 0);
        if (day < 1 || day > limit) throw std::invalid_argument("Неверный день месяца.");
    }

    Date::Date(const std::string& iso) : Date(1, 1, 1)
    {
        if (iso.size() != 10 || iso[4] != '-' || iso[7] != '-')
            throw std::invalid_argument("Ожидается дата YYYY-MM-DD.");
        for (std::size_t i = 0; i < iso.size(); ++i)
            if (i != 4 && i != 7 && (iso[i] < '0' || iso[i] > '9'))
                throw std::invalid_argument("В дате допустимы только цифры и дефисы.");
        *this = Date(std::stoi(iso.substr(0, 4)), std::stoi(iso.substr(5, 2)),
            std::stoi(iso.substr(8, 2)));
    }

    std::string Date::toString() const
    {
        const std::string y = std::to_string(year);
        return std::string(4 - y.size(), '0') + y + "-" + (month < 10 ? "0" : "")
            + std::to_string(month) + "-" + (day < 10 ? "0" : "") + std::to_string(day);
    }
    bool Date::operator<(const Date& other) const noexcept
    { return std::tie(year, month, day) < std::tie(other.year, other.month, other.day); }
    bool Date::operator<=(const Date& other) const noexcept { return !(other < *this); }
    bool Date::operator==(const Date& other) const noexcept
    { return std::tie(year, month, day) == std::tie(other.year, other.month, other.day); }
}
