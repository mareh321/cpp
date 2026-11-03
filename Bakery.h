#pragma once
#include "Bread.h"
#include "Pastry.h"
#include "Supplier.h"
#include "Shop.h"
#include "Ingredient.h"
#include "IngredientOrder.h"
#include "ShopOrder.h"
#include "ProductionBatch.h"
#include <deque>
#include <functional>
#include <utility>
#include <vector>

namespace miit::bakery
{
    /**
     * @brief Хлебопекарня: ассортимент, заказы сырья, заказы магазинов и производство.
     * Владеет всеми записями. Ссылки, полученные из методов, действуют до её уничтожения.
     * Добавление записей не нарушает ссылки; удаления записей нет.
     * Периоды включают начальную и конечную даты. Неизвестный ID вызывает out_of_range,
     * нулевой ID и обратный период — invalid_argument.
     */
    class Bakery
    {
    private:
        std::string bakeryName;
        std::deque<Bread> breads;
        std::deque<Pastry> pastries;
        std::deque<Supplier> suppliers;
        std::deque<Shop> shops;
        std::deque<Ingredient> ingredients;
        std::deque<IngredientOrder> ingredientOrders;
        std::deque<ShopOrder> shopOrders;
        std::deque<ProductionBatch> production;
        void requireNewProductName(const std::string& productName) const;
    public:
        explicit Bakery(const std::string& name);
        ~Bakery() = default;
        Bakery(const Bakery&) = delete;
        Bakery& operator=(const Bakery&) = delete;
        Bakery(Bakery&&) = delete;
        Bakery& operator=(Bakery&&) = delete;
        const std::string& getName() const noexcept;

        /** @brief Добавляет хлеб; одинаковые названия продукции запрещены. */
        const Bread& addBread(const std::string& name, const Money price,
            const Quantity weightGrams, const std::string& flourType);
        /** @brief Добавляет выпечку; одинаковые названия продукции запрещены. */
        const Pastry& addPastry(const std::string& name, const Money price,
            const Quantity weightGrams, const std::string& filling);
        /** @brief Добавляет поставщика с непустым уникальным названием. */
        const Supplier& addSupplier(const std::string& name, const std::string& address);
        /** @brief Добавляет магазин с непустым уникальным названием. */
        const Shop& addShop(const std::string& name, const std::string& address);
        /** @brief Добавляет вид сырья с непустым уникальным названием. */
        const Ingredient& addIngredient(const std::string& name, const Unit unit);

        const Product& getProduct(const Id id) const;
        const Product& getProductByName(const std::string& name) const;
        const Supplier& getSupplier(const Id id) const;
        const Shop& getShop(const Id id) const;
        const Ingredient& getIngredient(const Id id) const;

        /** @brief Возвращает ассортимент как коллекцию ссылок на базовый класс Product. */
        std::vector<std::reference_wrapper<const Product>> getAssortment() const;

        /** @brief Регистрирует заказ сырья после проверки поставщика и сырья. */
        const IngredientOrder& orderIngredient(const Id supplierId, const Id ingredientId,
            const Date& date, const Quantity quantity, const Money unitPrice);
        /**
         * @brief Регистрирует заказ магазина, сохраняя цены продукции на эту дату.
         * @param items пары «ID продукции, количество штук»; повтор ID запрещён
         * @throw invalid_argument если заказ пустой, товар повторён или количество неположительно
         * @throw overflow_error если сумма не помещается в Money
         */
        const ShopOrder& placeShopOrder(const Id shopId, const Date& date,
            const std::vector<std::pair<Id, Quantity>>& items);
        /** @brief Записывает фактически произведённое количество изделий. */
        const ProductionBatch& recordProduction(const Id productId, const Date& date,
            const Quantity quantity);

        /** @brief Возвращает заказы сырья выбранному поставщику за период. */
        std::vector<std::reference_wrapper<const IngredientOrder>> getSupplierOrders(
            const Id supplierId, const Date& from, const Date& to) const;
        /** @brief Количество выбранного сырья, заказанного у поставщика за период. */
        Quantity getIngredientQuantity(const Id supplierId, const Id ingredientId,
            const Date& from, const Date& to) const;
        /** @brief Стоимость выбранного сырья, заказанного у поставщика за период. */
        Money getIngredientTotal(const Id supplierId, const Id ingredientId,
            const Date& from, const Date& to) const;

        /** @brief Возвращает все заказы магазина за период с позициями и суммами. */
        std::vector<std::reference_wrapper<const ShopOrder>> getShopOrders(
            const Id shopId, const Date& from, const Date& to) const;
        /** @brief Общая стоимость заказов магазина за период. */
        Money getShopOrdersTotal(const Id shopId, const Date& from, const Date& to) const;
        /** @brief Возвращает ID различных товаров, заказанных магазином за период. */
        std::vector<Id> getShopProductIds(const Id shopId, const Date& from, const Date& to) const;
        /** @brief Количество выбранного товара в заказах магазина за период. */
        Quantity getShopProductQuantity(const Id shopId, const Id productId,
            const Date& from, const Date& to) const;
        /** @brief Стоимость выбранного товара во всех заказах магазина за период. */
        Money getShopProductTotal(const Id shopId, const Id productId,
            const Date& from, const Date& to) const;

        /** @brief Общее количество произведённых изделий за период, в штуках. */
        Quantity getProducedQuantity(const Date& from, const Date& to) const;
        /** @brief Количество произведённых изделий с точным названием за период. */
        Quantity getProducedQuantity(const std::string& productName,
            const Date& from, const Date& to) const;
    };
}
