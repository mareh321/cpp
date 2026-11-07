#pragma once
#include <string>

namespace miit::bakery
{
    /**
     * @brief Календарная дата без времени, годы от 1 до 9999.
     * @note Копируется и присваивается как обычное значение.
     */
    class Date
    {
    private:
        /** @brief Год от 1 до 9999. */
        int year;
        /** @brief Номер месяца от 1 до 12. */
        int month;
        /** @brief День месяца с учётом числа дней и високосного года. */
        int day;
    public:
        /**
         * @brief Создаёт календарную дату с проверкой числа дней и високосного года.
         * @param year Год от 1 до 9999.
         * @param month Месяц от 1 до 12.
         * @param day День выбранного месяца.
         * @throw std::invalid_argument Если дата не существует.
         */
        Date(const int year, const int month, const int day);
        /**
         * @brief Читает календарную дату из строки.
         * @param iso Дата строго в формате YYYY-MM-DD.
         * @throw std::invalid_argument Если формат неверен или дата не существует.
         */
        explicit Date(const std::string& iso);
        /**
         * @brief Формирует строковую дату.
         * @return Дата в формате YYYY-MM-DD.
         */
        std::string toString() const;
        /**
         * @brief Сравнивает даты по времени.
         * @param other Дата для сравнения.
         * @return true, если текущая дата раньше other.
         */
        bool operator<(const Date& other) const noexcept;
        /**
         * @brief Сравнивает даты с учётом равенства.
         * @param other Дата для сравнения.
         * @return true, если текущая дата не позже other.
         */
        bool operator<=(const Date& other) const noexcept;
        /**
         * @brief Проверяет совпадение календарных дат.
         * @param other Дата для сравнения.
         * @return true, если год, месяц и день совпадают.
         */
        bool operator==(const Date& other) const noexcept;
    };
}
