#include "CppUnitTest.h"
#include "../ListLib/LinkedListLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace collections;

namespace ListTests
{
    TEST_CLASS(LinkedListIntTests)
    {
    public:

        // 1. Тест конструктора по умолчанию
        TEST_METHOD(DefaultConstructor_Success)
        {
            // Arrange & Act
            LinkedList<int> list;

            // Assert
            Assert::AreEqual(size_t(0), list.getCount());
            Assert::IsTrue(list.isEmpty());
        }

        // 2. Тест конструктора со списком инициализации
        TEST_METHOD(InitializerListConstructor_Success)
        {
            // Arrange
            LinkedList<int> list = { 10, 20, 30, 40, 50 };

            // Act
            size_t count = list.getCount();

            // Assert
            Assert::AreEqual(size_t(5), count);
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
            Assert::AreEqual(50, list[4]);
        }

        // 3. Тест конструктора копирования
        TEST_METHOD(CopyConstructor_Success)
        {
            // Arrange
            LinkedList<int> original = { 1, 2, 3 };

            // Act
            LinkedList<int> copy(original);

            // Assert
            Assert::AreEqual(original.getCount(), copy.getCount());
            Assert::AreEqual(original[0], copy[0]);
            Assert::AreEqual(original[1], copy[1]);
            Assert::AreEqual(original[2], copy[2]);
        }

        // 4. Тест конструктора перемещения
        TEST_METHOD(MoveConstructor_Success)
        {
            // Arrange
            LinkedList<int> source = { 5, 10, 15 };

            // Act
            LinkedList<int> destination(std::move(source));

            // Assert
            Assert::AreEqual(size_t(3), destination.getCount());
            Assert::AreEqual(5, destination[0]);
            Assert::AreEqual(10, destination[1]);
            Assert::AreEqual(15, destination[2]);
            // После перемещения source должен быть пустым
            Assert::AreEqual(size_t(0), source.getCount());
            Assert::IsTrue(source.isEmpty());
        }

        // 5. Тест оператора присваивания копированием
        TEST_METHOD(AssignmentOperator_Success)
        {
            // Arrange
            LinkedList<int> original = { 7, 8, 9 };
            LinkedList<int> target;

            // Act
            target = original;

            // Assert
            Assert::AreEqual(original.getCount(), target.getCount());
            Assert::AreEqual(original[0], target[0]);
            Assert::AreEqual(original[1], target[1]);
            Assert::AreEqual(original[2], target[2]);
        }

        // 6. Тест push_back
        TEST_METHOD(PushBack_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2 };

            // Act
            list.push_back(3);

            // Assert
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        // 7. Тест push_front
        TEST_METHOD(PushFront_Success)
        {
            // Arrange
            LinkedList<int> list = { 2, 3 };

            // Act
            list.push_front(1);

            // Assert
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
            Assert::AreEqual(3, list[2]);
        }

        // 8. Тест insert
        TEST_METHOD(Insert_Success)
        {
            // Arrange
            LinkedList<int> list = { 10, 30, 40 };

            // Act
            list.insert(1, 20);

            // Assert
            Assert::AreEqual(size_t(4), list.getCount());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(30, list[2]);
            Assert::AreEqual(40, list[3]);
        }

        // 9. Тест pop_back
        TEST_METHOD(PopBack_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2, 3 };

            // Act
            list.pop_back();

            // Assert
            Assert::AreEqual(size_t(2), list.getCount());
            Assert::AreEqual(1, list[0]);
            Assert::AreEqual(2, list[1]);
        }

        // 10. Тест pop_front
        TEST_METHOD(PopFront_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2, 3 };

            // Act
            list.pop_front();

            // Assert
            Assert::AreEqual(size_t(2), list.getCount());
            Assert::AreEqual(2, list[0]);
            Assert::AreEqual(3, list[1]);
        }

        // 11. Тест erase
        TEST_METHOD(Erase_Success)
        {
            // Arrange
            LinkedList<int> list = { 10, 20, 30, 40 };

            // Act
            list.erase(2);

            // Assert
            Assert::AreEqual(size_t(3), list.getCount());
            Assert::AreEqual(10, list[0]);
            Assert::AreEqual(20, list[1]);
            Assert::AreEqual(40, list[2]);
        }

        // 12. Тест remove
        TEST_METHOD(Remove_Success)
        {
            // Arrange
            LinkedList<int> list = { 5, 10, 15, 10, 20 };

            // Act
            bool removed = list.remove(10);

            // Assert
            Assert::IsTrue(removed);
            Assert::AreEqual(size_t(4), list.getCount());
            Assert::AreEqual(5, list[0]);
            Assert::AreEqual(15, list[1]);
            Assert::AreEqual(10, list[2]);
            Assert::AreEqual(20, list[3]);
        }

        // 13. Тест indexOf (существующий элемент)
        TEST_METHOD(IndexOf_Existing_Success)
        {
            // Arrange
            LinkedList<int> list = { 100, 200, 300, 400 };

            // Act
            int index = list.indexOf(300);

            // Assert
            Assert::AreEqual(2, index);
        }

        // 14. Тест indexOf (отсутствующий элемент)
        TEST_METHOD(IndexOf_NonExisting_ReturnsMinusOne)
        {
            // Arrange
            LinkedList<int> list = { 100, 200, 300 };

            // Act
            int index = list.indexOf(999);

            // Assert
            Assert::AreEqual(-1, index);
        }

        // 15. Тест setAt
        TEST_METHOD(SetAt_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2, 3, 4 };

            // Act
            list.setAt(2, 99);

            // Assert
            Assert::AreEqual(99, list[2]);
        }

        // 16. Тест оператора []
        TEST_METHOD(BracketOperator_Success)
        {
            // Arrange
            LinkedList<int> list = { 5, 6, 7, 8 };

            // Act
            list[1] = 60;

            // Assert
            Assert::AreEqual(60, list[1]);
        }

        // 17. Тест clear
        TEST_METHOD(Clear_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2, 3, 4, 5 };

            // Act
            list.clear();

            // Assert
            Assert::AreEqual(size_t(0), list.getCount());
            Assert::IsTrue(list.isEmpty());
        }

        // 18. Тест asString
        TEST_METHOD(AsString_Success)
        {
            // Arrange
            LinkedList<int> list = { 1, 2, 3, 4 };

            // Act
            std::string result = list.asString();

            // Assert
            Assert::AreEqual(std::string("[1 <-> 2 <-> 3 <-> 4]"), result);
        }

        // 19. Тест выхода за границы (исключение)
        TEST_METHOD(OutOfRangeIndex_ThrowsException)
        {
            // Arrange
            LinkedList<int> list = { 1, 2 };

            // Act
            auto func = [&]() { list[5]; };

            // Assert
            Assert::ExpectException<std::out_of_range>(func);
        }

        // 20. Тест pop_back из пустого списка (исключение)
        TEST_METHOD(PopBack_EmptyList_ThrowsException)
        {
            // Arrange
            LinkedList<int> list;

            // Act
            auto func = [&]() { list.pop_back(); };

            // Assert
            Assert::ExpectException<std::out_of_range>(func);
        }

        // 21. Тест pop_front из пустого списка (исключение)
        TEST_METHOD(PopFront_EmptyList_ThrowsException)
        {
            // Arrange
            LinkedList<int> list;

            // Act
            auto func = [&]() { list.pop_front(); };

            // Assert
            Assert::ExpectException<std::out_of_range>(func);
        }
    };
}
