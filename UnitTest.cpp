#include "CppUnitTest.h"
#include "Bakery.h"
#include <limits>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::bakery;

static_assert(std::is_abstract_v<Product>);
static_assert(std::is_copy_constructible_v<Bread>);
static_assert(std::is_copy_assignable_v<Bread>);
static_assert(std::is_copy_constructible_v<Bakery>);
static_assert(std::is_copy_assignable_v<Bakery>);
static_assert(std::is_move_constructible_v<Bakery>);
static_assert(std::is_move_assignable_v<Bakery>);


namespace BakeryTests
{
    TEST_CLASS(DateTests)
    {
    public:
        TEST_METHOD(LeapYearAndFormatting)
        {
            Assert::AreEqual(std::string("2024-02-29"), Date(2024, 2, 29).toString());
            Assert::AreEqual(std::string("0001-01-01"), Date(1, 1, 1).toString());
            Assert::IsTrue(Date("2026-11-02") == Date(2026, 11, 2));
        }
        TEST_METHOD(InvalidCalendarDates)
        {
            Assert::ExpectException<std::invalid_argument>([] { Date d(2025, 2, 29); });
            Assert::ExpectException<std::invalid_argument>([] { Date d(1900, 2, 29); });
            Assert::ExpectException<std::invalid_argument>([] { Date d(2026, 4, 31); });
            Assert::ExpectException<std::invalid_argument>([] { Date d(2026, 13, 1); });
            Assert::ExpectException<std::invalid_argument>([] { Date d(0, 1, 1); });
        }
        TEST_METHOD(StrictDateParsing)
        {
            Assert::ExpectException<std::invalid_argument>([] { Date d("2026-1-01"); });
            Assert::ExpectException<std::invalid_argument>([] { Date d("2026-0x-01"); });
            Assert::ExpectException<std::invalid_argument>([] { Date d("2026-11-02x"); });
            Assert::ExpectException<std::invalid_argument>([] { Date d("2026-02-30"); });
        }
        TEST_METHOD(ChronologicalComparison)
        {
            Assert::IsTrue(Date(2025, 12, 31) < Date(2026, 1, 1));
            Assert::IsTrue(Date(2026, 1, 31) < Date(2026, 2, 1));
            Assert::IsTrue(Date(2026, 1, 1) <= Date(2026, 1, 1));
        }
    };

    TEST_CLASS(ModelTests)
    {
    public:
        TEST_METHOD(IdsArePositiveAndUniqueAcrossTypes)
        {
            Bread bread("Хлеб", 100, 100, "Мука");
            Pastry pastry("Булка", 100, 100, "Изюм");
            Supplier supplier("Поставщик", "Адрес");
            Shop shop("Магазин", "Адрес");
            Ingredient ingredient("Мука", Unit::Gram);
            std::set<Id> ids = { bread.getId(), pastry.getId(), supplier.getId(),
                shop.getId(), ingredient.getId() };
            Assert::IsTrue(ids.size() == 5 && ids.count(0) == 0);
        }
        TEST_METHOD(WhitespaceNamesAreRejected)
        {
            Assert::ExpectException<std::invalid_argument>([] { Bakery b(" \t\n"); });
            Assert::ExpectException<std::invalid_argument>([] { Supplier s("", "Адрес"); });
            Assert::ExpectException<std::invalid_argument>([] { Shop s("Магазин", " "); });
            Assert::ExpectException<std::invalid_argument>([] { Ingredient i("", Unit::Gram); });
        }
        TEST_METHOD(ProductValidation)
        {
            Assert::ExpectException<std::invalid_argument>([] { Bread b("Хлеб", 0, 100, "Мука"); });
            Assert::ExpectException<std::invalid_argument>([] { Bread b("Хлеб", 100, -1, "Мука"); });
            Assert::ExpectException<std::invalid_argument>([] { Pastry p("Булка", 100, 100, ""); });
            Assert::ExpectException<std::invalid_argument>([] { Ingredient i("Мука", static_cast<Unit>(99)); });
        }
        TEST_METHOD(MoneyFormattingAndOverflow)
        {
            Assert::AreEqual(std::string("0.05 руб."), formatMoney(5));
            Assert::AreEqual(std::string("125.50 руб."), formatMoney(12550));
            const Money max = (std::numeric_limits<Money>::max)();
            Assert::ExpectException<std::overflow_error>([=] { checkedAdd(max, 1); });
            Assert::ExpectException<std::overflow_error>([=] { checkedMultiply(max, 2); });
            Assert::ExpectException<std::invalid_argument>([] { formatMoney(-1); });
        }
        TEST_METHOD(OrderLineValidation)
        {
            Assert::ExpectException<std::invalid_argument>([] { OrderLine l(0, 1, 100); });
            Assert::ExpectException<std::invalid_argument>([] { OrderLine l(1, 0, 100); });
            Assert::ExpectException<std::invalid_argument>([] { OrderLine l(1, 1, -1); });
            Assert::IsTrue(OrderLine(1, 3, 125).getTotal() == 375);
        }
        TEST_METHOD(EmptyAndDuplicateShopOrdersAreRejected)
        {
            const Date date(2026, 11, 1);
            Assert::ExpectException<std::invalid_argument>([&] { ShopOrder o(1, date, {}); });
            Assert::ExpectException<std::invalid_argument>([&] {
                ShopOrder o(1, date, { OrderLine(2, 1, 100), OrderLine(2, 3, 100) });
            });
        }
        TEST_METHOD(OrderTotalOverflowIsRejected)
        {
            const Money max = (std::numeric_limits<Money>::max)();
            Assert::ExpectException<std::overflow_error>([&] {
                ShopOrder o(1, Date(2026, 11, 1), { OrderLine(2, 1, max), OrderLine(3, 1, 1) });
            });
        }
        TEST_METHOD(ProductionAndIngredientOrderValidation)
        {
            const Date date(2026, 11, 1);
            Assert::ExpectException<std::invalid_argument>([&] { ProductionBatch p(0, date, 1); });
            Assert::ExpectException<std::invalid_argument>([&] { ProductionBatch p(1, date, 0); });
            Assert::ExpectException<std::invalid_argument>([&] { IngredientOrder o(0, 1, date, 1, 1); });
            Assert::ExpectException<std::invalid_argument>([&] { IngredientOrder o(1, 1, date, -1, 1); });
        }
    };

    TEST_CLASS(CatalogTests)
    {
    public:
        TEST_METHOD(PolymorphicCollectionUsesDerivedDescriptions)
        {
            Bakery b("Пекарня");
            b.addBread("Хлеб", 5500, 400, "пшеничная");
            b.addPastry("Булка", 8500, 120, "изюм");
            const auto catalog = b.getAssortment();
            Assert::IsTrue(catalog.size() == 2);
            Assert::IsTrue(catalog[0].get().toString().find("Хлеб:") == 0);
            Assert::IsTrue(catalog[1].get().toString().find("Выпечка:") == 0);
            Assert::IsTrue(catalog[0].get().getPrice() == 5500);
        }
        TEST_METHOD(DuplicateProductNamesAcrossSubclasses)
        {
            Bakery b("Пекарня");
            b.addBread("Хлеб", 100, 100, "Мука");
            Assert::ExpectException<std::invalid_argument>([&] { b.addPastry(" Хлеб ", 100, 100, "Изюм"); });
            Assert::IsTrue(b.getAssortment().size() == 1);
        }
        TEST_METHOD(DuplicateDirectoryNamesAreRejected)
        {
            Bakery b("Пекарня");
            b.addSupplier("Поставщик", "Адрес");
            b.addShop("Магазин", "Адрес");
            b.addIngredient("Мука", Unit::Gram);
            Assert::ExpectException<std::invalid_argument>([&] { b.addSupplier("Поставщик", "Другой адрес"); });
            Assert::ExpectException<std::invalid_argument>([&] { b.addShop("Магазин", "Адрес"); });
            Assert::ExpectException<std::invalid_argument>([&] { b.addIngredient("Мука", Unit::Piece); });
        }
        TEST_METHOD(UnknownAndZeroIdsAreRejected)
        {
            Bakery b("Пекарня");
            Assert::ExpectException<std::invalid_argument>([&] { b.getProduct(0); });
            Assert::ExpectException<std::out_of_range>([&] { b.getShop(999999); });
            Assert::ExpectException<std::out_of_range>([&] { b.getProductByName("Нет такого товара"); });
        }
        TEST_METHOD(ReferencesStayValidWhenCatalogGrows)
        {
            Bakery b("Пекарня");
            const Product& first = b.addBread("Первый", 100, 100, "Мука");
            const Id key = first.getId();
            for (int i = 0; i < 200; ++i) b.addBread("Хлеб " + std::to_string(i), 100, 100, "Мука");
            Assert::IsTrue(first.getId() == key);
            Assert::AreEqual(std::string("Первый"), first.getName());
        }
    };
                source.recordProduction(product, d, 7);
                return Bakery(source);
            }();
            Assert::IsTrue(copied.getProduct(product).getName() == "Хлеб");
            Assert::IsTrue(copied.getShopOrdersTotal(shop, d, d) == 11000);
            Assert::IsTrue(copied.getIngredientTotal(supplier, ingredient, d, d) == 5000);
            Assert::IsTrue(copied.getProducedQuantity("Хлеб", d, d) == 7);
            const auto products = copied.getAssortment();
            Assert::IsTrue(products.size() == 2);
            Assert::IsTrue(products.at(1).get().toString().find("Выпечка:") == 0);
        }

        /** @brief Добавление заказов в копию не меняет исходную хлебопекарню. */
        TEST_METHOD(CopiesOwnIndependentCollections)
        {
            Bakery source("Пекарня");
            const Id p = source.addBread("Хлеб", 100, 100, "Мука").getId();
            const Id s = source.addShop("Магазин", "Адрес").getId();
            const Date d(2026, 11, 1);
            source.placeShopOrder(s, d, {{p, 2}});
            Bakery copied(source);
            copied.placeShopOrder(s, d, {{p, 3}});
            copied.recordProduction(p, d, 4);
            Assert::IsTrue(source.getShopOrdersTotal(s, d, d) == 200);
            Assert::IsTrue(copied.getShopOrdersTotal(s, d, d) == 500);
            Assert::IsTrue(source.getProducedQuantity(d, d) == 0);
            Assert::IsTrue(copied.getProducedQuantity(d, d) == 4);
            Assert::IsTrue(&source.getProduct(p) != &copied.getProduct(p));
        }

        /** @brief Присваивание заменяет прежние записи вместе с их ключами и связями. */
        TEST_METHOD(CopyAssignmentReplacesExistingData)
        {
            Bakery source("Исходная");
            const Id p = source.addBread("Хлеб", 200, 100, "Мука").getId();
            const Id s = source.addShop("Магазин", "Адрес").getId();
            const Date d(2026, 11, 1);
            source.placeShopOrder(s, d, {{p, 3}});
            Bakery target("Прежняя");
            const Id old = target.addBread("Другой хлеб", 100, 100, "Мука").getId();
            target = source;
            Assert::AreEqual(std::string("Исходная"), target.getName());
            Assert::IsTrue(target.getShopOrdersTotal(s, d, d) == 600);
            Assert::ExpectException<std::out_of_range>([&] { target.getProduct(old); });
            Assert::IsTrue(source.getShopOrdersTotal(s, d, d) == 600);
        }

        /** @brief Самоприсваивание сохраняет содержимое объекта. */
        TEST_METHOD(SelfCopyAssignmentPreservesData)
        {
            Bakery b("Пекарня");
            const Id p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const Date d(2026, 11, 1);
            b.recordProduction(p, d, 5);
            Bakery& alias = b;
            b = alias;
            Assert::IsTrue(b.getProducedQuantity("Хлеб", d, d) == 5);
            Assert::IsTrue(b.getProduct(p).getPrice() == 100);
        }

        /** @brief Конструктор перемещения переносит данные; исходному объекту можно присвоить новые. */
        TEST_METHOD(MoveConstructorPreservesReports)
        {
            Bakery source("Пекарня");
            const Id p = source.addBread("Хлеб", 100, 100, "Мука").getId();
            const Date d(2026, 11, 1);
            source.recordProduction(p, d, 8);
            Bakery target(std::move(source));
            Assert::IsTrue(target.getProducedQuantity("Хлеб", d, d) == 8);
            Assert::IsTrue(target.getProduct(p).getName() == "Хлеб");
            source = Bakery("Новая");
            Assert::IsTrue(source.getAssortment().empty());
            Assert::AreEqual(std::string("Новая"), source.getName());
        }

        /** @brief Перемещающее присваивание заменяет заполненный объект. */
        TEST_METHOD(MoveAssignmentReplacesExistingData)
        {
            Bakery source("Источник");
            const Id p = source.addBread("Хлеб", 100, 100, "Мука").getId();
            const Id s = source.addShop("Магазин", "Адрес").getId();
            const Date d(2026, 11, 1);
            source.placeShopOrder(s, d, {{p, 9}});
            Bakery target("Прежняя");
            const Id old = target.addPastry("Булка", 100, 100, "Изюм").getId();
            target = std::move(source);
            Assert::IsTrue(target.getShopOrdersTotal(s, d, d) == 900);
            Assert::ExpectException<std::out_of_range>([&] { target.getProduct(old); });
            source = Bakery("Новая");
            Assert::IsTrue(source.getAssortment().empty());
        }

        /** @brief Копирование сущности сохраняет ID логической записи и её данные. */
        TEST_METHOD(EntityCopiesPreserveLogicalIdentity)
        {
            Bread first("Первый", 100, 200, "Пшеничная");
            Bread copy(first);
            Assert::IsTrue(first.getId() == copy.getId());
            Bread second("Второй", 300, 400, "Ржаная");
            copy = second;
            Assert::IsTrue(copy.getId() == second.getId());
            Assert::IsTrue(copy.getPrice() == 300 && copy.getWeightGrams() == 400);
            Assert::AreEqual(std::string("Ржаная"), copy.getFlourType());
            Assert::IsTrue(first.getId() != second.getId());
        }

        /** @brief Новые записи в разных копиях получают различные ключи из общего счётчика. */
        TEST_METHOD(NewRecordsStayUniqueAfterCopying)
        {
            Bakery source("Пекарня");
            const Id old = source.addBread("Хлеб", 100, 100, "Мука").getId();
            Bakery copy(source);
            const Id first = source.addBread("Первый", 100, 100, "Мука").getId();
            const Id second = copy.addBread("Второй", 100, 100, "Мука").getId();
            Assert::IsTrue(first != second && first != old && second != old);
            Assert::IsTrue(copy.getProduct(old).getId() == source.getProduct(old).getId());
        }
    };

    TEST_CLASS(ReportTests)
    {
    public:
        TEST_METHOD(SupplierPeriodAndIngredientFilters)
        {
            Bakery b("Пекарня");
            const auto s = b.addSupplier("Первый", "Адрес").getId();
            const auto other = b.addSupplier("Второй", "Адрес").getId();
            const auto flour = b.addIngredient("Мука", Unit::Gram).getId();
            const auto milk = b.addIngredient("Молоко", Unit::Milliliter).getId();
            const Date from(2026, 11, 1), to(2026, 11, 30);
            b.orderIngredient(s, flour, from, 1000, 5);
            b.orderIngredient(s, flour, to, 2000, 6);
            b.orderIngredient(s, milk, from, 1000, 7);
            b.orderIngredient(other, flour, from, 9000, 8);
            b.orderIngredient(s, flour, Date(2026, 10, 31), 9000, 8);
            b.orderIngredient(s, flour, Date(2026, 12, 1), 9000, 8);
            Assert::IsTrue(b.getIngredientQuantity(s, flour, from, to) == 3000);
            Assert::IsTrue(b.getIngredientTotal(s, flour, from, to) == 17000);
            Assert::IsTrue(b.getSupplierOrders(s, from, to).size() == 3);
        }
        TEST_METHOD(SupplierOrderRejectsUnknownLinks)
        {
            Bakery b("Пекарня");
            const auto s = b.addSupplier("Поставщик", "Адрес").getId();
            const auto i = b.addIngredient("Мука", Unit::Gram).getId();
            const Date d(2026, 11, 1);
            Assert::ExpectException<std::out_of_range>([&] { b.orderIngredient(999999, i, d, 1, 1); });
            Assert::ExpectException<std::out_of_range>([&] { b.orderIngredient(s, 999999, d, 1, 1); });
            Assert::IsTrue(b.getSupplierOrders(s, d, d).empty());
        }
        TEST_METHOD(ShopOrdersProductsAndTotals)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 5500, 400, "Мука").getId();
            const auto q = b.addPastry("Булка", 8500, 100, "Изюм").getId();
            const auto s = b.addShop("Магазин", "Адрес").getId();
            const auto other = b.addShop("Другой", "Адрес").getId();
            const Date from(2026, 11, 1), to(2026, 11, 30);
            const auto& order = b.placeShopOrder(s, from, { {p, 20}, {q, 10} });
            b.placeShopOrder(s, to, { {p, 5} });
            b.placeShopOrder(other, from, { {p, 99} });
            b.placeShopOrder(s, Date(2026, 12, 1), { {p, 99} });
            Assert::IsTrue(order.getTotal() == 195000);
            Assert::IsTrue(order.getLines()[0].getUnitPrice() == 5500);
            Assert::IsTrue(b.getShopOrdersTotal(s, from, to) == 222500);
            Assert::IsTrue(b.getShopProductQuantity(s, p, from, to) == 25);
            Assert::IsTrue(b.getShopProductTotal(s, p, from, to) == 137500);
            Assert::IsTrue(b.getShopProductIds(s, from, to).size() == 2);
            Assert::IsTrue(b.getShopOrders(s, from, to).size() == 2);
        }
        TEST_METHOD(FailedShopOrderDoesNotChangeReports)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const auto s = b.addShop("Магазин", "Адрес").getId();
            const Date d(2026, 11, 1);
            b.placeShopOrder(s, d, { {p, 1} });
            Assert::ExpectException<std::invalid_argument>([&] { b.placeShopOrder(s, d, { {p, 1}, {p, 2} }); });
            Assert::ExpectException<std::out_of_range>([&] { b.placeShopOrder(s, d, { {999999, 1} }); });
            Assert::ExpectException<std::invalid_argument>([&] { b.placeShopOrder(s, d, {}); });
            Assert::IsTrue(b.getShopOrdersTotal(s, d, d) == 100);
            Assert::IsTrue(b.getShopOrders(s, d, d).size() == 1);
        }
        TEST_METHOD(ProductionFiltersByPeriodAndName)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const auto q = b.addPastry("Булка", 100, 100, "Изюм").getId();
            const Date from(2026, 11, 1), to(2026, 11, 30);
            b.recordProduction(p, from, 10);
            b.recordProduction(p, to, 20);
            b.recordProduction(q, from, 5);
            b.recordProduction(p, Date(2026, 12, 1), 99);
            Assert::IsTrue(b.getProducedQuantity(from, to) == 35);
            Assert::IsTrue(b.getProducedQuantity("Хлеб", from, to) == 30);
            Assert::IsTrue(b.getProducedQuantity("Булка", from, to) == 5);
        }
        TEST_METHOD(OrdersDoNotCountAsProduction)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const auto s = b.addShop("Магазин", "Адрес").getId();
            const Date d(2026, 11, 1);
            b.placeShopOrder(s, d, { {p, 20} });
            Assert::IsTrue(b.getProducedQuantity(d, d) == 0);
        }
        TEST_METHOD(EmptyReportsAreZero)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const auto s = b.addShop("Магазин", "Адрес").getId();
            const auto v = b.addSupplier("Поставщик", "Адрес").getId();
            const auto i = b.addIngredient("Мука", Unit::Gram).getId();
            const Date d(2026, 11, 1);
            Assert::IsTrue(b.getShopOrdersTotal(s, d, d) == 0);
            Assert::IsTrue(b.getShopProductTotal(s, p, d, d) == 0);
            Assert::IsTrue(b.getIngredientQuantity(v, i, d, d) == 0);
            Assert::IsTrue(b.getProducedQuantity("Хлеб", d, d) == 0);
        }
        TEST_METHOD(ReversePeriodIsRejected)
        {
            Bakery b("Пекарня");
            const auto s = b.addShop("Магазин", "Адрес").getId();
            const auto v = b.addSupplier("Поставщик", "Адрес").getId();
            const Date from(2026, 11, 30), to(2026, 11, 1);
            Assert::ExpectException<std::invalid_argument>([&] { b.getShopOrders(s, from, to); });
            Assert::ExpectException<std::invalid_argument>([&] { b.getSupplierOrders(v, from, to); });
            Assert::ExpectException<std::invalid_argument>([&] { b.getProducedQuantity(from, to); });
        }
        TEST_METHOD(ProductionRejectsUnknownProduct)
        {
            Bakery b("Пекарня");
            Assert::ExpectException<std::out_of_range>([&] { b.recordProduction(999999, Date(2026, 11, 1), 5); });
        }
        TEST_METHOD(ReportOverflowIsDetected)
        {
            Bakery b("Пекарня");
            const auto p = b.addBread("Хлеб", 100, 100, "Мука").getId();
            const Date d(2026, 11, 1);
            b.recordProduction(p, d, (std::numeric_limits<Quantity>::max)());
            b.recordProduction(p, d, 1);
            Assert::ExpectException<std::overflow_error>([&] { b.getProducedQuantity(d, d); });
        }
    };
}
