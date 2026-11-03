#pragma once
#include "Product.h"

namespace miit::bakery
{
    /** @brief Выпечка с указанием начинки. */
    class Pastry final : public Product
    {
    private:
        std::string filling;
    public:
        Pastry(const std::string& name, const Money price, const Quantity weightGrams,
            const std::string& filling);
        const std::string& getFilling() const noexcept;
        std::string toString() const override;
    };
}
