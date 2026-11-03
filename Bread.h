#pragma once
#include "Product.h"

namespace miit::bakery
{
    /** @brief Хлеб с указанием вида муки. */
    class Bread final : public Product
    {
    private:
        std::string flourType;
    public:
        Bread(const std::string& name, const Money price, const Quantity weightGrams,
            const std::string& flourType);
        const std::string& getFlourType() const noexcept;
        std::string toString() const override;
    };
}
