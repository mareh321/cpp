#include "Bakery.h"
#include <set>
#include <stdexcept>

namespace
{
     /** @brief Находит зарегистрированный объект по положительному ID или бросает исключение. */
    template <typename T>
    const T& findById(const std::deque<T>& objects, const miit::bakery::Id id)
    {
        miit::bakery::requireId(id);
        for (const auto& object : objects)
            if (object.getId() == id) return object;
        throw std::out_of_range("Объект с таким ID не найден.");
    }

     /** @brief Проверяет непустое название и отсутствие совпадений в справочнике. */
    template <typename T>
    void requireNewName(const std::deque<T>& objects, const std::string& name)
    {
        const auto clean = miit::bakery::requireText(name);
        for (const auto& object : objects)
            if (object.getName() == clean)
                throw std::invalid_argument("Такое название уже зарегистрировано.");
    }
    /** @brief Отклоняет период, в котором конечная дата раньше начальной. */
    void checkPeriod(const miit::bakery::Date& from, const miit::bakery::Date& to)
    {
        if (to < from) throw std::invalid_argument("Конец периода раньше начала.");
    }

    /** @brief Проверяет попадание даты в период с включёнными границами. */
    bool within(const miit::bakery::Date& date, const miit::bakery::Date& from,
        const miit::bakery::Date& to)
    {
        return from <= date && date <= to;
    }
}

namespace miit::bakery
{
    Bakery::Bakery(const std::string& name) : bakeryName(requireText(name)) {}
    const std::string& Bakery::getName() const noexcept { return bakeryName; }

    void Bakery::requireNewProductName(const std::string& productName) const
    {
        requireNewName(breads, productName);
        requireNewName(pastries, productName);
    }

    const Bread& Bakery::addBread(const std::string& name, const Money price,
        const Quantity weightGrams, const std::string& flourType)
    {
        requireNewProductName(name);
        breads.emplace_back(name, price, weightGrams, flourType);
        return breads.back();
    }

    const Pastry& Bakery::addPastry(const std::string& name, const Money price,
        const Quantity weightGrams, const std::string& filling)
    {
        requireNewProductName(name);
        pastries.emplace_back(name, price, weightGrams, filling);
        return pastries.back();
    }

    const Supplier& Bakery::addSupplier(const std::string& name, const std::string& address)
    {
        requireNewName(suppliers, name);
        suppliers.emplace_back(name, address);
        return suppliers.back();
    }

    const Shop& Bakery::addShop(const std::string& name, const std::string& address)
    {
        requireNewName(shops, name);
        shops.emplace_back(name, address);
        return shops.back();
    }

    const Ingredient& Bakery::addIngredient(const std::string& name, const Unit unit)
    {
        requireNewName(ingredients, name);
        ingredients.emplace_back(name, unit);
        return ingredients.back();
    }

    const Product& Bakery::getProduct(const Id id) const
    {
        requireId(id);
        for (const auto& bread : breads) if (bread.getId() == id) return bread;
        for (const auto& pastry : pastries) if (pastry.getId() == id) return pastry;
        throw std::out_of_range("Продукция с таким ID не найдена.");
    }

    const Product& Bakery::getProductByName(const std::string& name) const
    {
        const auto clean = requireText(name);
        for (const auto& bread : breads) if (bread.getName() == clean) return bread;
        for (const auto& pastry : pastries) if (pastry.getName() == clean) return pastry;
        throw std::out_of_range("Продукция с таким названием не найдена.");
    }

    const Supplier& Bakery::getSupplier(const Id id) const { return findById(suppliers, id); }
    const Shop& Bakery::getShop(const Id id) const { return findById(shops, id); }
    const Ingredient& Bakery::getIngredient(const Id id) const { return findById(ingredients, id); }

    std::vector<std::reference_wrapper<const Product>> Bakery::getAssortment() const
    {
        std::vector<std::reference_wrapper<const Product>> result;
        result.reserve(breads.size() + pastries.size());
        for (const auto& bread : breads) result.emplace_back(bread);
        for (const auto& pastry : pastries) result.emplace_back(pastry);
        return result;
    }

    const IngredientOrder& Bakery::orderIngredient(const Id supplierId, const Id ingredientId,
        const Date& date, const Quantity quantity, const Money unitPrice)
    {
        (void)getSupplier(supplierId);
        (void)getIngredient(ingredientId);
        ingredientOrders.emplace_back(supplierId, ingredientId, date, quantity, unitPrice);
        return ingredientOrders.back();
    }

    const ShopOrder& Bakery::placeShopOrder(const Id shopId, const Date& date,
        const std::vector<std::pair<Id, Quantity>>& items)
    {
        (void)getShop(shopId);
        std::vector<OrderLine> lines;
        lines.reserve(items.size());
        for (const auto& item : items)
            lines.emplace_back(item.first, item.second, getProduct(item.first).getPrice());
        shopOrders.emplace_back(shopId, date, std::move(lines));
        return shopOrders.back();
    }

    const ProductionBatch& Bakery::recordProduction(const Id productId, const Date& date,
        const Quantity quantity)
    {
        (void)getProduct(productId);
        production.emplace_back(productId, date, quantity);
        return production.back();
    }

    std::vector<std::reference_wrapper<const IngredientOrder>> Bakery::getSupplierOrders(
        const Id supplierId, const Date& from, const Date& to) const
    {
        (void)getSupplier(supplierId);
        checkPeriod(from, to);
        std::vector<std::reference_wrapper<const IngredientOrder>> result;
        for (const auto& order : ingredientOrders)
            if (order.getSupplierId() == supplierId && within(order.getDate(), from, to))
                result.emplace_back(order);
        return result;
    }

    Quantity Bakery::getIngredientQuantity(const Id supplierId, const Id ingredientId,
        const Date& from, const Date& to) const
    {
        (void)getIngredient(ingredientId);
        Quantity total = 0;
        for (const IngredientOrder& order : getSupplierOrders(supplierId, from, to))
            if (order.getIngredientId() == ingredientId)
                total = checkedAdd(total, order.getQuantity());
        return total;
    }

    Money Bakery::getIngredientTotal(const Id supplierId, const Id ingredientId,
        const Date& from, const Date& to) const
    {
        (void)getIngredient(ingredientId);
        Money total = 0;
        for (const IngredientOrder& order : getSupplierOrders(supplierId, from, to))
            if (order.getIngredientId() == ingredientId)
                total = checkedAdd(total, order.getTotal());
        return total;
    }

    std::vector<std::reference_wrapper<const ShopOrder>> Bakery::getShopOrders(
        const Id shopId, const Date& from, const Date& to) const
    {
        (void)getShop(shopId);
        checkPeriod(from, to);
        std::vector<std::reference_wrapper<const ShopOrder>> result;
        for (const auto& order : shopOrders)
            if (order.getShopId() == shopId && within(order.getDate(), from, to))
                result.emplace_back(order);
        return result;
    }

    Money Bakery::getShopOrdersTotal(const Id shopId, const Date& from, const Date& to) const
    {
        Money total = 0;
        for (const ShopOrder& order : getShopOrders(shopId, from, to))
            total = checkedAdd(total, order.getTotal());
        return total;
    }

    std::vector<Id> Bakery::getShopProductIds(const Id shopId, const Date& from, const Date& to) const
    {
        std::set<Id> ids;
        for (const ShopOrder& order : getShopOrders(shopId, from, to))
            for (const auto& line : order.getLines()) ids.insert(line.getProductId());
        return { ids.begin(), ids.end() };
    }

    Quantity Bakery::getShopProductQuantity(const Id shopId, const Id productId,
        const Date& from, const Date& to) const
    {
        (void)getProduct(productId);
        Quantity total = 0;
        for (const ShopOrder& order : getShopOrders(shopId, from, to))
            for (const auto& line : order.getLines())
                if (line.getProductId() == productId) total = checkedAdd(total, line.getQuantity());
        return total;
    }

    Money Bakery::getShopProductTotal(const Id shopId, const Id productId,
        const Date& from, const Date& to) const
    {
        (void)getProduct(productId);
        Money total = 0;
        for (const ShopOrder& order : getShopOrders(shopId, from, to))
            for (const auto& line : order.getLines())
                if (line.getProductId() == productId) total = checkedAdd(total, line.getTotal());
        return total;
    }

    Quantity Bakery::getProducedQuantity(const Date& from, const Date& to) const
    {
        checkPeriod(from, to);
        Quantity total = 0;
        for (const auto& batch : production)
            if (within(batch.getDate(), from, to)) total = checkedAdd(total, batch.getQuantity());
        return total;
    }

    Quantity Bakery::getProducedQuantity(const std::string& productName,
        const Date& from, const Date& to) const
    {
        const Id id = getProductByName(productName).getId();
        checkPeriod(from, to);
        Quantity total = 0;
        for (const auto& batch : production)
            if (batch.getProductId() == id && within(batch.getDate(), from, to))
                total = checkedAdd(total, batch.getQuantity());
        return total;
    }
}
