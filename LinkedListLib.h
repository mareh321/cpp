#pragma once
#include <iostream>
#include <string>
#include <initializer_list>
#include <sstream>
#include <stdexcept>
#include "ListNode.h"

namespace collections {
    /**
     * @brief Класс линейного двусвязного списка
     * @tparam T тип данных, хранящихся в списке
     */
    template<typename T>
    class LinkedList {
    private:
        ListNode<T>* first;
        ListNode<T>* last;
        size_t count;

        /**
         * @brief Копирует содержимое другого списка
         * @param other - список для копирования
         */
        void cloneFrom(const LinkedList<T>& other) {
            ListNode<T>* current = other.first;
            while (current != nullptr) {
                push_back(current->value);
                current = current->nextNode;
            }
        }

    public:
        /**
         * @brief Конструктор по умолчанию
         */
        LinkedList() : first(nullptr), last(nullptr), count(0) {}

        /**
         * @brief Конструктор со списком инициализации
         * @param init - список инициализации
         */
        LinkedList(const std::initializer_list<T> init)
            : first(nullptr), last(nullptr), count(0) {
            for (const auto& val : init) {
                push_back(val);
            }
        }

        /**
         * @brief Конструктор копирования
         * @param other - другой список
         */
        LinkedList(const LinkedList<T>& other)
            : first(nullptr), last(nullptr), count(0) {
            cloneFrom(other);
        }

        /**
         * @brief Конструктор перемещения
         * @param other - другой список
         */
        LinkedList(LinkedList<T>&& other) noexcept
            : first(other.first), last(other.last), count(other.count) {
            other.first = nullptr;
            other.last = nullptr;
            other.count = 0;
        }

        /**
         * @brief Деструктор
         */
        ~LinkedList() {
            clear();
        }

        /**
         * @brief Оператор присваивания копированием
         * @param other - другой список
         * @return ссылка на текущий объект
         */
        LinkedList<T>& operator=(const LinkedList<T>& other) {
            if (this != &other) {
                clear();
                cloneFrom(other);
            }
            return *this;
        }

        /**
         * @brief Оператор присваивания перемещением
         * @param other - другой список
         * @return ссылка на текущий объект
         */
        LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
            if (this != &other) {
                clear();
                first = other.first;
                last = other.last;
                count = other.count;
                other.first = nullptr;
                other.last = nullptr;
                other.count = 0;
            }
            return *this;
        }

        /**
         * @brief Оператор сдвига влево (вывод в поток)
         * @param os - поток вывода
         * @param list - список для вывода
         * @return ссылка на поток вывода
         */
        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& list) {
            os << list.asString();
            return os;
        }

        /**
         * @brief Оператор сдвига вправо (ввод из потока)
         * @param is - поток ввода
         * @param list - список для ввода
         * @return ссылка на поток ввода
         */
        template<typename U>
        friend std::istream& operator>>(std::istream& is, LinkedList<U>& list) {
            list.clear();
            U val;
            while (is >> val) {
                list.push_back(val);
                if (is.peek() == '\n' || is.peek() == EOF) break;
            }
            return is;
        }

        /**
         * @brief Вставка элемента в конец списка
         * @param val - значение элемента
         */
        void push_back(const T& val) {
            ListNode<T>* newNode = new ListNode<T>(val);
            if (first == nullptr) {
                first = last = newNode;
            }
            else {
                last->nextNode = newNode;
                newNode->prevNode = last;
                last = newNode;
            }
            ++count;
        }

        /**
         * @brief Вставка элемента в начало списка
         * @param val - значение элемента
         */
        void push_front(const T& val) {
            ListNode<T>* newNode = new ListNode<T>(val);
            if (first == nullptr) {
                first = last = newNode;
            }
            else {
                newNode->nextNode = first;
                first->prevNode = newNode;
                first = newNode;
            }
            ++count;
        }

        /**
         * @brief Вставка элемента по индексу
         * @param index - позиция для вставки
         * @param val - значение элемента
         */
        void insert(const size_t index, const T& val) {
            if (index > count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (index == 0) {
                push_front(val);
                return;
            }
            if (index == count) {
                push_back(val);
                return;
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }

            ListNode<T>* newNode = new ListNode<T>(val);
            newNode->nextNode = current;
            newNode->prevNode = current->prevNode;
            current->prevNode->nextNode = newNode;
            current->prevNode = newNode;
            ++count;
        }

        /**
         * @brief Удаление элемента из конца списка
         */
        void pop_back() {
            if (isEmpty()) {
                throw std::out_of_range("Список пуст");
            }

            if (count == 1) {
                delete first;
                first = last = nullptr;
            }
            else {
                ListNode<T>* temp = last;
                last = last->prevNode;
                last->nextNode = nullptr;
                delete temp;
            }
            --count;
        }

        /**
         * @brief Удаление элемента из начала списка
         */
        void pop_front() {
            if (isEmpty()) {
                throw std::out_of_range("Список пуст");
            }

            if (count == 1) {
                delete first;
                first = last = nullptr;
            }
            else {
                ListNode<T>* temp = first;
                first = first->nextNode;
                first->prevNode = nullptr;
                delete temp;
            }
            --count;
        }

        /**
         * @brief Удаление элемента по индексу
         * @param index - позиция элемента
         */
        void erase(const size_t index) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            if (index == 0) {
                pop_front();
                return;
            }
            if (index == count - 1) {
                pop_back();
                return;
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }

            current->prevNode->nextNode = current->nextNode;
            current->nextNode->prevNode = current->prevNode;
            delete current;
            --count;
        }

        /**
         * @brief Удаление элемента по значению (первое вхождение)
         * @param val - значение для удаления
         * @return true, если элемент найден и удален
         */
        bool remove(const T& val) {
            int idx = indexOf(val);
            if (idx != -1) {
                erase(idx);
                return true;
            }
            return false;
        }

        /**
         * @brief Поиск элемента по значению
         * @param val - значение для поиска
         * @return индекс элемента или -1, если не найден
         */
        int indexOf(const T& val) const {
            ListNode<T>* current = first;
            size_t idx = 0;
            while (current != nullptr) {
                if (current->value == val) {
                    return static_cast<int>(idx);
                }
                current = current->nextNode;
                ++idx;
            }
            return -1;
        }

        /**
         * @brief Изменение элемента по индексу
         * @param index - позиция элемента
         * @param val - новое значение
         */
        void setAt(const size_t index, const T& val) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }
            current->value = val;
        }

        /**
         * @brief Оператор доступа по индексу (неконстантный)
         * @param index - позиция элемента
         * @return ссылка на элемент
         */
        T& operator[](const size_t index) {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }
            return current->value;
        }

        /**
         * @brief Оператор доступа по индексу (константный)
         * @param index - позиция элемента
         * @return константная ссылка на элемент
         */
        const T& operator[](const size_t index) const {
            if (index >= count) {
                throw std::out_of_range("Индекс выходит за пределы списка");
            }

            ListNode<T>* current = first;
            for (size_t i = 0; i < index; ++i) {
                current = current->nextNode;
            }
            return current->value;
        }

        /**
         * @brief Получение размера списка
         * @return количество элементов
         */
        size_t getCount() const {
            return count;
        }

        /**
         * @brief Проверка, пуст ли список
         * @return true, если список пуст
         */
        bool isEmpty() const {
            return count == 0;
        }

        /**
         * @brief Очистка списка
         */
        void clear() {
            ListNode<T>* current = first;
            while (current != nullptr) {
                ListNode<T>* temp = current;
                current = current->nextNode;
                delete temp;
            }
            first = last = nullptr;
            count = 0;
        }

        /**
         * @brief Сериализация в строку
         * @return строковое представление списка
         */
        std::string asString() const {
            std::stringstream ss;
            ss << "[";
            ListNode<T>* current = first;
            while (current != nullptr) {
                ss << current->value;
                if (current->nextNode != nullptr) {
                    ss << " <-> ";
                }
                current = current->nextNode;
            }
            ss << "]";
            return ss.str();
        }

        /**
         * @brief Получение указателя на начало списка
         * @return указатель на первый элемент списка
         */
        ListNode<T>* getFirst() const {
            return first;
        }
    };
}
