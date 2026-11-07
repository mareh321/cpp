#include <iostream>
#include <exception>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif
#include "Bakery.h"

using namespace miit::bakery;

/**
 * @brief Демонстрирует полиморфную коллекцию и все отчёты варианта 24.
 * @return 0 при успехе, 1 при перехваченном исключении.
 */
int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    try
    {
        Bakery bakery("Городская хлебопекарня");
        const Bread& wheat = bakery.addBread("Пшеничный", 5500, 400, "пшеничная");
        const Bread& rye = bakery.addBread("Ржаной", 7000, 500, "ржаная");
        const Pastry& bun = bakery.addPastry("Булочка с изюмом", 8500, 120, "изюм");
        const Supplier& mill = bakery.addSupplier("Мельница", "Москва, Мельничная, 1");
        const Supplier& farm = bakery.addSupplier("Ферма", "Москва, Полевая, 8");
        const Ingredient& flour = bakery.addIngredient("Мука", Unit::Gram);
        const Ingredient& milk = bakery.addIngredient("Молоко", Unit::Milliliter);
        const Shop& nearHome = bakery.addShop("У дома", "Москва, Лесная, 3");
        const Shop& secondShop = bakery.addShop("Пекарская лавка", "Москва, Садовая, 5");
        const Date from(2026, 11, 1);
        const Date to(2026, 11, 30);

        bakery.orderIngredient(mill.getId(), flour.getId(), from, 50000, 5);
        bakery.orderIngredient(mill.getId(), flour.getId(), Date(2026, 11, 15), 25000, 6);
        bakery.orderIngredient(farm.getId(), milk.getId(), from, 30000, 8);
        bakery.orderIngredient(mill.getId(), flour.getId(), Date(2026, 10, 31), 10000, 5);

        bakery.placeShopOrder(nearHome.getId(), Date(2026, 11, 2),
            { {wheat.getId(), 20}, {bun.getId(), 10} });
        bakery.placeShopOrder(nearHome.getId(), Date(2026, 11, 3),
            { {wheat.getId(), 5}, {rye.getId(), 8} });
        bakery.placeShopOrder(secondShop.getId(), from, { {wheat.getId(), 3} });
        bakery.placeShopOrder(nearHome.getId(), Date(2026, 10, 31), { {wheat.getId(), 9} });

        bakery.recordProduction(wheat.getId(), from, 100);
        bakery.recordProduction(rye.getId(), from, 60);
        bakery.recordProduction(bun.getId(), from, 80);
        bakery.recordProduction(wheat.getId(), Date(2026, 11, 3), 120);
        bakery.recordProduction(wheat.getId(), Date(2026, 10, 31), 50);

        std::cout << bakery.getName() << " — вариант 24, Хлебопекарня\n";
        std::cout << "Период: " << from.toString() << " — " << to.toString() << "\n\n";

        std::cout << "1. Ассортимент и цены\n";
        // Одна коллекция базового типа содержит объекты разных классов-наследников.
        const std::vector<std::reference_wrapper<const Product>> products = bakery.getAssortment();
        for (const Product& product : products)
            std::cout << "ID " << product.getId() << ": " << product.toString() << '\n';

        std::cout << "\n2. Заказы сырья у поставщика «" << mill.getName() << "»\n";
        for (const IngredientOrder& order : bakery.getSupplierOrders(mill.getId(), from, to))
        {
            const Ingredient& ingredient = bakery.getIngredient(order.getIngredientId());
            std::cout << "Заказ " << order.getId() << ", " << order.getDate().toString()
                << ": " << ingredient.getName() << ", " << order.getQuantity() << ' '
                << unitName(ingredient.getUnit()) << ", " << formatMoney(order.getTotal()) << '\n';
        }
        std::cout << "Всего муки: " << bakery.getIngredientQuantity(mill.getId(), flour.getId(), from, to)
            << " г; сумма: " << formatMoney(bakery.getIngredientTotal(mill.getId(), flour.getId(), from, to)) << '\n';

        std::cout << "\n3. Заказы магазина «" << nearHome.getName() << "»\n";
        for (const ShopOrder& order : bakery.getShopOrders(nearHome.getId(), from, to))
        {
            std::cout << "Заказ " << order.getId() << " от " << order.getDate().toString() << '\n';
            for (const OrderLine& line : order.getLines())
                std::cout << "  " << bakery.getProduct(line.getProductId()).getName() << ": "
                    << line.getQuantity() << " шт., цена " << formatMoney(line.getUnitPrice())
                    << ", сумма " << formatMoney(line.getTotal()) << '\n';
            std::cout << "  Итого: " << formatMoney(order.getTotal()) << '\n';
        }
        std::cout << "Сумма всех заказов: "
            << formatMoney(bakery.getShopOrdersTotal(nearHome.getId(), from, to)) << '\n';
        for (const Id id : bakery.getShopProductIds(nearHome.getId(), from, to))
            std::cout << bakery.getProduct(id).getName() << ": "
                << bakery.getShopProductQuantity(nearHome.getId(), id, from, to) << " шт.; "
                << formatMoney(bakery.getShopProductTotal(nearHome.getId(), id, from, to)) << '\n';

        std::cout << "\n4. Производство\nВсего произведено: "
            << bakery.getProducedQuantity(from, to) << " шт.\n";
        for (const Product& product : products)
            std::cout << product.getName() << ": "
                << bakery.getProducedQuantity(product.getName(), from, to) << " шт.\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
