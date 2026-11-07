#pragma once
namespace collections {
/**
* @brief Класс узла двусвязного списка
* @tparam T тип данных, хранящихся в узле
*/
template<typename T>
class ListNode {
private:  
    T value;
    ListNode<T>* nextNode;
    ListNode<T>* prevNode;
    

    template<typename U>
    friend class LinkedList;

public:
    /**
    * @brief Конструктор узла
    * @param val - значение для хранения в узле
    */
    explicit ListNode(const T& val) : value(val), nextNode(nullptr), prevNode(nullptr) {}
};
}
