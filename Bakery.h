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
     * @brief Хранит данные хлебопекарни и рассчитывает отчёты варианта 24.
     * @note Копия содержит независимые коллекции тех же логических записей с сохранёнными ID. Периоды включают обе границы. Ссылки действуют до уничтожения, присваивания или перемещения владеющего объекта; добавление записей их не нарушает.
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
        /**
         * @brief Проверяет уникальность названия среди хлеба и выпечки.
         * @param productName Название нового изделия.
         * @throw std::invalid_argument Если название пусто или уже занято.
         */
        void requireNewProductName(const std::string& productName) const;
    public:
        /**
         * @brief Создаёт пустую хлебопекарню.
         * @param name Непустое название.
         * @throw std::invalid_argument Если название пусто после удаления пробелов.
         */
        explicit Bakery(const std::string& name);
        /**
         * @brief Освобождает все принадлежащие хлебопекарне записи.
         */
        ~Bakery() = default;
        /**
         * @brief Стандартный конструктор копирования.
         * @param other Исходный объект.
         * @note Данные и ID копируются; новые ключи не создаются.
         */
        Bakery(const Bakery& other) = default;
        /**
         * @brief Стандартное присваивание копированием.
         * @param other Объект, данные и ID которого заменяют текущие.
         * @return Ссылка на текущий объект.
         */
        Bakery& operator=(const Bakery& other) = default;
        /**
         * @brief Стандартный конструктор перемещения.
         * @param other Объект, из которого переносятся данные.
         * @note Сохраняются ключи переносимых записей. Исходный объект можно уничтожить или присвоить ему новое значение.
         */
        Bakery(Bakery&& other) = default;
        /**
         * @brief Стандартное присваивание перемещением.
         * @param other Объект, из которого переносятся данные и ID.
         * @return Ссылка на текущий объект.
         * @note Исходный объект можно уничтожить или присвоить ему новое значение.
         */
        Bakery& operator=(Bakery&& other) = default;
        /**
         * @brief Возвращает название хлебопекарни.
         * @return Константная ссылка на название.
         */
        const std::string& getName() const noexcept;

        /**
         * @brief Добавляет новый хлеб в ассортимент.
         * @param name Непустое название изделия.
         * @param price Положительная цена одной штуки в копейках.
         * @param weightGrams Положительная масса одной штуки в граммах.
         * @param flourType Непустой вид муки.
         * @return Константная ссылка на добавленное изделие.
         * @throw std::invalid_argument Если данные неверны или название занято.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const Bread& addBread(const std::string& name, const Money price,
            const Quantity weightGrams, const std::string& flourType);
        /**
         * @brief Добавляет новую выпечку в ассортимент.
         * @param name Непустое название изделия.
         * @param price Положительная цена одной штуки в копейках.
         * @param weightGrams Положительная масса одной штуки в граммах.
         * @param filling Непустая начинка.
         * @return Константная ссылка на добавленное изделие.
         * @throw std::invalid_argument Если данные неверны или название занято.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const Pastry& addPastry(const std::string& name, const Money price,
            const Quantity weightGrams, const std::string& filling);
        /**
         * @brief Регистрирует нового поставщика.
         * @param name Непустое уникальное название поставщика.
         * @param address Непустой адрес.
         * @return Константная ссылка на поставщика.
         * @throw std::invalid_argument Если строка пуста или название поставщика занято.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const Supplier& addSupplier(const std::string& name, const std::string& address);
        /**
         * @brief Регистрирует новый магазин.
         * @param name Непустое уникальное название магазина.
         * @param address Непустой адрес.
         * @return Константная ссылка на магазин.
         * @throw std::invalid_argument Если строка пуста или название магазина занято.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const Shop& addShop(const std::string& name, const std::string& address);
        /**
         * @brief Регистрирует новый вид сырья.
         * @param name Непустое уникальное название сырья.
         * @param unit Единица измерения сырья.
         * @return Константная ссылка на сырьё.
         * @throw std::invalid_argument Если название пусто, занято или единица не поддерживается.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const Ingredient& addIngredient(const std::string& name, const Unit unit);

        /**
         * @brief Находит запись продукции по ключу.
         * @param id Положительный ID искомой записи.
         * @return Константная ссылка на найденный объект.
         * @throw std::invalid_argument Если ID равен нулю.
         * @throw std::out_of_range Если запись не найдена.
         */
        const Product& getProduct(const Id id) const;
        /**
         * @brief Находит продукцию по точному названию с учётом регистра.
         * @param name Название продукции; пробелы по краям удаляются.
         * @return Константная ссылка на продукцию.
         * @throw std::invalid_argument Если название пусто.
         * @throw std::out_of_range Если продукция не найдена.
         */
        const Product& getProductByName(const std::string& name) const;
        /**
         * @brief Находит запись поставщика по ключу.
         * @param id Положительный ID искомой записи.
         * @return Константная ссылка на найденный объект.
         * @throw std::invalid_argument Если ID равен нулю.
         * @throw std::out_of_range Если запись не найдена.
         */
        const Supplier& getSupplier(const Id id) const;
        /**
         * @brief Находит запись магазина по ключу.
         * @param id Положительный ID искомой записи.
         * @return Константная ссылка на найденный объект.
         * @throw std::invalid_argument Если ID равен нулю.
         * @throw std::out_of_range Если запись не найдена.
         */
        const Shop& getShop(const Id id) const;
        /**
         * @brief Находит запись сырья по ключу.
         * @param id Положительный ID искомой записи.
         * @return Константная ссылка на найденный объект.
         * @throw std::invalid_argument Если ID равен нулю.
         * @throw std::out_of_range Если запись не найдена.
         */
        const Ingredient& getIngredient(const Id id) const;

        /**
         * @brief Возвращает ассортимент через базовый класс Product.
         * @return Коллекция невладеющих ссылок на хлеб и выпечку; пустая, если ассортимент пуст.
         */
        std::vector<std::reference_wrapper<const Product>> getAssortment() const;

        /**
         * @brief Проверяет связи и добавляет заказ сырья.
         * @param supplierId ID зарегистрированного поставщика.
         * @param ingredientId ID зарегистрированного сырья.
         * @param date Дата заказа.
         * @param quantity Положительное количество в единицах сырья.
         * @param unitPrice Неотрицательная цена единицы сырья в копейках.
         * @return Константная ссылка на созданный заказ.
         * @throw std::invalid_argument Если ID, количество или цена недопустимы.
         * @throw std::out_of_range Если поставщик или сырьё не найдены.
         * @throw std::overflow_error Если стоимость не помещается в Money или исчерпаны ID.
         */
        const IngredientOrder& orderIngredient(const Id supplierId, const Id ingredientId,
            const Date& date, const Quantity quantity, const Money unitPrice);
        /**
         * @brief Добавляет заказ магазина с текущими ценами продукции.
         * @param shopId ID зарегистрированного магазина.
         * @param date Дата оформления.
         * @param items Пары «ID продукции, положительное количество штук», без повторов товара.
         * @return Константная ссылка на созданный заказ.
         * @throw std::invalid_argument Если ID равен нулю, список пуст, товар повторён или количество неположительно.
         * @throw std::out_of_range Если магазин или продукция не найдены.
         * @throw std::overflow_error Если стоимость не помещается в Money или исчерпаны ID.
         */
        const ShopOrder& placeShopOrder(const Id shopId, const Date& date,
            const std::vector<std::pair<Id, Quantity>>& items);
        /**
         * @brief Добавляет запись о фактическом производстве.
         * @param productId ID зарегистрированной продукции.
         * @param date Дата производства.
         * @param quantity Положительное количество штук.
         * @return Константная ссылка на партию.
         * @throw std::invalid_argument Если ID равен нулю или количество неположительно.
         * @throw std::out_of_range Если продукция не найдена.
         * @throw std::overflow_error Если исчерпан диапазон ID.
         */
        const ProductionBatch& recordProduction(const Id productId, const Date& date,
            const Quantity quantity);

        /**
         * @brief Отбирает заказы выбранному поставщику за период.
         * @param supplierId ID поставщика.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Коллекция невладеющих ссылок на заказы; пустая, если совпадений нет.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         */
        std::vector<std::reference_wrapper<const IngredientOrder>> getSupplierOrders(
            const Id supplierId, const Date& from, const Date& to) const;
        /**
         * @brief Считает количество выбранного сырья в заказах поставщику за период.
         * @param supplierId ID поставщика.
         * @param ingredientId ID сырья.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Количество в единицах сырья или ноль при отсутствии заказов.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         * @throw std::overflow_error Если результат не помещается в 64-битное целое.
         */
        Quantity getIngredientQuantity(const Id supplierId, const Id ingredientId,
            const Date& from, const Date& to) const;
        /**
         * @brief Считает стоимость выбранного сырья в заказах поставщику за период.
         * @param supplierId ID поставщика.
         * @param ingredientId ID сырья.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Сумма в копейках или ноль при отсутствии заказов.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         * @throw std::overflow_error Если результат не помещается в 64-битное целое.
         */
        Money getIngredientTotal(const Id supplierId, const Id ingredientId,
            const Date& from, const Date& to) const;

        /**
         * @brief Отбирает заказы выбранного магазина за период.
         * @param shopId ID магазина.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Коллекция невладеющих ссылок на заказы; пустая, если совпадений нет.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         */
        std::vector<std::reference_wrapper<const ShopOrder>> getShopOrders(
            const Id shopId, const Date& from, const Date& to) const;
        /**
         * @brief Суммирует стоимость всех заказов магазина за период.
         * @param shopId ID магазина.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Сумма в копейках или ноль при отсутствии заказов.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         * @throw std::overflow_error Если результат не помещается в 64-битное целое.
         */
        Money getShopOrdersTotal(const Id shopId, const Date& from, const Date& to) const;
        /**
         * @brief Находит различные товары в заказах магазина за период.
         * @param shopId ID магазина.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Упорядоченный список ID без повторов; пустой, если заказов нет.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         */
        std::vector<Id> getShopProductIds(const Id shopId, const Date& from, const Date& to) const;
        /**
         * @brief Считает заказанное магазином количество выбранного товара за период.
         * @param shopId ID магазина.
         * @param productId ID продукции.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Количество штук или ноль при отсутствии позиций.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         * @throw std::overflow_error Если результат не помещается в 64-битное целое.
         */
        Quantity getShopProductQuantity(const Id shopId, const Id productId,
            const Date& from, const Date& to) const;
        /**
         * @brief Считает стоимость выбранного товара в заказах магазина за период.
         * @param shopId ID магазина.
         * @param productId ID продукции.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Сумма в копейках по сохранённым ценам заказов или ноль.
         * @throw std::invalid_argument Если ID равен нулю или конец периода раньше начала.
         * @throw std::out_of_range Если указанный объект не найден.
         * @throw std::overflow_error Если результат не помещается в 64-битное целое.
         */
        Money getShopProductTotal(const Id shopId, const Id productId,
            const Date& from, const Date& to) const;

        /**
         * @brief Считает всё фактическое производство за период.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Общее количество штук или ноль при отсутствии партий.
         * @throw std::invalid_argument Если конец периода раньше начала.
         * @throw std::overflow_error Если количество не помещается в Quantity.
         */
        Quantity getProducedQuantity(const Date& from, const Date& to) const;
        /**
         * @brief Считает производство выбранного изделия за период.
         * @param productName Точное непустое название продукции с учётом регистра.
         * @param from Первая дата периода включительно.
         * @param to Последняя дата периода включительно.
         * @return Количество штук или ноль, если партий выбранного изделия нет.
         * @throw std::invalid_argument Если название пусто или период обратный.
         * @throw std::out_of_range Если продукция не найдена.
         * @throw std::overflow_error Если количество не помещается в Quantity.
         */
        Quantity getProducedQuantity(const std::string& productName,
            const Date& from, const Date& to) const;
    };
}
