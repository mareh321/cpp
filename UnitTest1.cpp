#include "CppUnitTest.h"

#include "Matrix.h"
#include "Generator.h"
#include "RandomGenerator.h"
#include "IStreamGenerator.h"
#include "ConstGenerator.h"
#include "Exercise.h"
#include "Task1.h"
#include "Task2.h"

#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::algebra;

namespace UnitTests
{
    /**
     * @brief Модульные тесты шаблонного класса Matrix
     */
    TEST_CLASS(MatrixTests)
    {
    public:
        /**
         * @brief Проверка конструктора по умолчанию (создание пустой матрицы)
         */
        TEST_METHOD(DefaultConstructor_ShouldCreateEmptyMatrix)
        {
            Matrix<int> m;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
            Assert::AreEqual(static_cast<size_t>(0), m.getCols());
            Assert::IsTrue(m.empty());
            Assert::AreEqual(std::string(""), m.toString());
        }

        /**
         * @brief Проверка конструктора с заданными размерами (нулевая инициализация)
         */
        TEST_METHOD(SizeConstructor_ShouldCreateZeroMatrix)
        {
            Matrix<int> m(2, 3);
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(3), m.getCols());
            Assert::IsFalse(m.empty());
            Assert::AreEqual(0, m[0][0]);
            Assert::AreEqual(0, m[0][2]);
            Assert::AreEqual(0, m[1][0]);
            Assert::AreEqual(0, m[1][2]);
        }

        /**
         * @brief Проверка конструктора с заполнением константным значением
         */
        TEST_METHOD(ValueConstructor_ShouldFillWithValue)
        {
            Matrix<int> m(2, 2, 5);
            Assert::AreEqual(5, m[0][0]);
            Assert::AreEqual(5, m[0][1]);
            Assert::AreEqual(5, m[1][0]);
            Assert::AreEqual(5, m[1][1]);
        }

        /**
         * @brief Проверка конструктора с заполнением от генератора
         */
        TEST_METHOD(GeneratorConstructor_ShouldFillFromGenerator)
        {
            ConstGenerator gen(42);
            Matrix<int> m(2, 2, gen);
            Assert::AreEqual(42, m[0][0]);
            Assert::AreEqual(42, m[0][1]);
            Assert::AreEqual(42, m[1][0]);
            Assert::AreEqual(42, m[1][1]);
        }

        /**
         * @brief Проверка конструктора копирования (глубокое копирование)
         */
        TEST_METHOD(CopyConstructor_ShouldCreateDeepCopy)
        {
            Matrix<int> original(2, 2, 7);
            Matrix<int> copy(original);

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original.getCols(), copy.getCols());
            Assert::AreEqual(original[0][0], copy[0][0]);

            // Изменение оригинала не должно влиять на копию
            original[0][0] = 99;
            Assert::AreEqual(99, original[0][0]);
            Assert::AreEqual(7, copy[0][0]);
        }

        /**
         * @brief Проверка конструктора перемещения
         */
        TEST_METHOD(MoveConstructor_ShouldTransferData)
        {
            Matrix<int> original(2, 2, 7);
            Matrix<int> moved(std::move(original));

            Assert::AreEqual(static_cast<size_t>(2), moved.getRows());
            Assert::AreEqual(static_cast<size_t>(2), moved.getCols());
            Assert::AreEqual(7, moved[0][0]);
        }

        /**
         * @brief Проверка оператора присваивания копированием
         */
        TEST_METHOD(CopyAssignment_ShouldCopyContent)
        {
            Matrix<int> original(2, 2, 3);
            Matrix<int> copy;
            copy = original;

            Assert::AreEqual(original.getRows(), copy.getRows());
            Assert::AreEqual(original[0][0], copy[0][0]);

            // Проверка самоприсваивания
            copy = copy;
            Assert::AreEqual(3, copy[0][0]);
        }

        /**
         * @brief Проверка оператора присваивания перемещением
         */
        TEST_METHOD(MoveAssignment_ShouldTransferContent)
        {
            Matrix<int> original(2, 2, 11);
            Matrix<int> target;
            target = std::move(original);

            Assert::AreEqual(static_cast<size_t>(2), target.getRows());
            Assert::AreEqual(11, target[0][0]);
        }

        /**
         * @brief Проверка оператора доступа по индексу (чтение и запись)
         */
        TEST_METHOD(IndexOperator_ShouldReturnRow)
        {
            Matrix<int> m(2, 2, 7);
            Assert::AreEqual(7, m[0][0]);
            m[0][0] = 42;
            Assert::AreEqual(42, m[0][0]);
            Assert::AreEqual(7, m[1][1]);
        }

        /**
         * @brief Проверка генерации исключения при выходе индекса строки за границы
         */
        TEST_METHOD(IndexOperator_OutOfRange_ShouldThrow)
        {
            Matrix<int> m(2, 2);
            auto func = [&m]() { (void)m[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        /**
         * @brief Проверка сдвига влево (удаление первых строк)
         */
        TEST_METHOD(ShiftLeft_ShouldRemoveFirstRows)
        {
            Matrix<int> m(3, 2, 1);
            m << 1;
            Assert::AreEqual(static_cast<size_t>(2), m.getRows());
            Assert::AreEqual(static_cast<size_t>(2), m.getCols());
        }

        /**
         * @brief Проверка сдвига влево на количество строк больше или равное текущему
         */
        TEST_METHOD(ShiftLeft_MoreThanRows_ShouldResultEmpty)
        {
            Matrix<int> m(2, 2, 1);
            m << 5;
            Assert::AreEqual(static_cast<size_t>(0), m.getRows());
            Assert::IsTrue(m.empty());
        }

        /**
         * @brief Проверка сдвига вправо (добавление пустых строк в начало)
         */
        TEST_METHOD(ShiftRight_ShouldAddEmptyRows)
        {
            Matrix<int> m(2, 2, 1);
            m >> 1;
            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(0, m[0][0]);
            Assert::AreEqual(0, m[0][1]);
            Assert::AreEqual(1, m[1][0]);
        }

        /**
         * @brief Проверка строкового представления матрицы
         */
        TEST_METHOD(ToString_ShouldContainAllElements)
        {
            Matrix<int> m(2, 2, 5);
            std::string s = m.toString();
            Assert::IsTrue(s.find("5") != std::string::npos);
        }

        /**
         * @brief Проверка заполнения матрицы через IStreamGenerator
         */
        TEST_METHOD(Fill_WithIStreamGenerator_ShouldFillFromStream)
        {
            std::istringstream input("1 2 3 4");
            IStreamGenerator gen(input);
            Matrix<int> m(2, 2);
            m.fill(gen);

            Assert::AreEqual(1, m[0][0]);
            Assert::AreEqual(2, m[0][1]);
            Assert::AreEqual(3, m[1][0]);
            Assert::AreEqual(4, m[1][1]);
        }

        /**
         * @brief Проверка вставки строки после указанной позиции
         */
        TEST_METHOD(InsertRow_ShouldInsertAfterPosition)
        {
            Matrix<int> m(2, 2, 1);
            std::vector<int> row = { 9, 9 };
            m.insertRow(0, row);

            Assert::AreEqual(static_cast<size_t>(3), m.getRows());
            Assert::AreEqual(9, m[1][0]);
            Assert::AreEqual(9, m[1][1]);
            Assert::AreEqual(1, m[2][0]);
        }
    };

    /**
     * @brief Модульные тесты Задачи 1 (Вариант 8)
     */
    TEST_CLASS(Task1Tests)
    {
    public:
        /**
         * @brief Замена максимального элемента каждого столбца нулем (обычная матрица 3x3)
         */
        TEST_METHOD(ReplaceColumnMaxWithZero_NormalMatrix)
        {
            Matrix<int> m(3, 3);
            m[0][0] = 1; m[0][1] = 8; m[0][2] = 3;
            m[1][0] = 9; m[1][1] = 2; m[1][2] = 7;
            m[2][0] = 4; m[2][1] = 5; m[2][2] = 6;

            Task1 task(m);
            task.solve();

            // Столбец 0: максимум 9 (строка 1) -> 0
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[1][0]);
            Assert::AreEqual(4, task.getMatrix()[2][0]);

            // Столбец 1: максимум 8 (строка 0) -> 0
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(2, task.getMatrix()[1][1]);
            Assert::AreEqual(5, task.getMatrix()[2][1]);

            // Столбец 2: максимум 7 (строка 1) -> 0
            Assert::AreEqual(3, task.getMatrix()[0][2]);
            Assert::AreEqual(0, task.getMatrix()[1][2]);
            Assert::AreEqual(6, task.getMatrix()[2][2]);
        }

        /**
         * @brief Замена максимального элемента при наличии нескольких одинаковых максимумов в столбце
         */
        TEST_METHOD(ReplaceColumnMaxWithZero_MultipleMaxInColumn)
        {
            Matrix<int> m(3, 2);
            m[0][0] = 10; m[0][1] = 3;
            m[1][0] = 5;  m[1][1] = 7;
            m[2][0] = 10; m[2][1] = 7;

            Task1 task(m);
            task.solve();

            // Столбец 0: максимумы 10 в строках 0 и 2 -> оба становятся 0
            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(5, task.getMatrix()[1][0]);
            Assert::AreEqual(0, task.getMatrix()[2][0]);

            // Столбец 1: максимумы 7 в строках 1 и 2 -> оба становятся 0
            Assert::AreEqual(3, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[1][1]);
            Assert::AreEqual(0, task.getMatrix()[2][1]);
        }

        /**
         * @brief Замена максимального элемента при отрицательных значениях в столбце
         */
        TEST_METHOD(ReplaceColumnMaxWithZero_NegativeValues)
        {
            Matrix<int> m(2, 2);
            m[0][0] = -10; m[0][1] = -5;
            m[1][0] = -2;  m[1][1] = -20;

            Task1 task(m);
            task.solve();

            // Столбец 0: максимум -2 (строка 1) -> 0
            Assert::AreEqual(-10, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[1][0]);

            // Столбец 1: максимум -5 (строка 0) -> 0
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(-20, task.getMatrix()[1][1]);
        }

        /**
         * @brief Замена максимума в матрице из одной строки (все элементы становятся 0)
         */
        TEST_METHOD(ReplaceColumnMaxWithZero_SingleRowMatrix)
        {
            Matrix<int> m(1, 3);
            m[0][0] = 5; m[0][1] = -2; m[0][2] = 10;

            Task1 task(m);
            task.solve();

            Assert::AreEqual(0, task.getMatrix()[0][0]);
            Assert::AreEqual(0, task.getMatrix()[0][1]);
            Assert::AreEqual(0, task.getMatrix()[0][2]);
        }

        /**
         * @brief Работа с пустой матрицей не приводит к ошибкам
         */
        TEST_METHOD(EmptyMatrix_ShouldNotChange)
        {
            Matrix<int> m;
            Task1 task(m);
            task.solve();
            Assert::AreEqual(static_cast<size_t>(0), task.getMatrix().getRows());
        }

        /**
         * @brief Описание задачи не является пустым
         */
        TEST_METHOD(Description_ShouldNotBeEmpty)
        {
            Matrix<int> m(1, 1);
            Task1 task(m);
            Assert::IsFalse(task.description().empty());
        }

        /**
         * @brief Полиморфный вызов через базовый указатель Exercise*
         */
        TEST_METHOD(PolymorphicCall_ThroughExerciseBasePointer)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 5; m[0][1] = 1;
            m[1][0] = 2; m[1][1] = 9;

            std::unique_ptr<Exercise> ex = std::make_unique<Task1>(m);
            ex->solve();

            Assert::AreEqual(0, ex->getMatrix()[0][0]);
            Assert::AreEqual(0, ex->getMatrix()[1][1]);
        }
    };

    /**
     * @brief Модульные тесты Задачи 2 (Вариант 8)
     */
    TEST_CLASS(Task2Tests)
    {
    public:
        /**
         * @brief Вставка первой строки после строки с максимальным по модулю элементом
         */
        TEST_METHOD(InsertFirstRowAfterMaxAbsRows_NormalMatrix)
        {
            Matrix<int> m(3, 3);
            m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;       // Первая строка
            m[1][0] = 4; m[1][1] = -99; m[1][2] = 6;    // Максимум по модулю (-99)
            m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

            Task2 task(m);
            task.solve();

            // Было 3 строки, после 1-й вставилась копия 0-й -> стало 4 строки
            Assert::AreEqual(static_cast<size_t>(4), task.getMatrix().getRows());

            // Строка 0: [1, 2, 3]
            Assert::AreEqual(1, task.getMatrix()[0][0]);
            Assert::AreEqual(2, task.getMatrix()[0][1]);
            Assert::AreEqual(3, task.getMatrix()[0][2]);

            // Строка 1: [4, -99, 6]
            Assert::AreEqual(4, task.getMatrix()[1][0]);
            Assert::AreEqual(-99, task.getMatrix()[1][1]);
            Assert::AreEqual(6, task.getMatrix()[1][2]);

            // Строка 2 (вставленная копия первой строки): [1, 2, 3]
            Assert::AreEqual(1, task.getMatrix()[2][0]);
            Assert::AreEqual(2, task.getMatrix()[2][1]);
            Assert::AreEqual(3, task.getMatrix()[2][2]);

            // Строка 3: [7, 8, 9]
            Assert::AreEqual(7, task.getMatrix()[3][0]);
            Assert::AreEqual(8, task.getMatrix()[3][1]);
            Assert::AreEqual(9, task.getMatrix()[3][2]);
        }

        /**
         * @brief Максимум по модулю находится в первой строке
         */
        TEST_METHOD(InsertFirstRow_MaxAbsInFirstRow)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 100; m[0][1] = 5;  // Максимум по модулю здесь
            m[1][0] = 1;   m[1][1] = 2;

            Task2 task(m);
            task.solve();

            // После строки 0 вставляется строка 0 -> размер 3
            Assert::AreEqual(static_cast<size_t>(3), task.getMatrix().getRows());

            Assert::AreEqual(100, task.getMatrix()[0][0]);
            Assert::AreEqual(5, task.getMatrix()[0][1]);

            Assert::AreEqual(100, task.getMatrix()[1][0]);
            Assert::AreEqual(5, task.getMatrix()[1][1]);

            Assert::AreEqual(1, task.getMatrix()[2][0]);
            Assert::AreEqual(2, task.getMatrix()[2][1]);
        }

        /**
         * @brief Максимум по модулю присутствует в нескольких строках (вставка после каждой)
         */
        TEST_METHOD(InsertFirstRow_MultipleRowsWithMaxAbs)
        {
            Matrix<int> m(3, 2);
            m[0][0] = 1;   m[0][1] = 2;    // Первая строка
            m[1][0] = -50; m[1][1] = 0;    // Содержит максимум по модулю
            m[2][0] = 10;  m[2][1] = 50;   // Содержит максимум по модулю

            Task2 task(m);
            task.solve();

            // Было 3 строки, вставка после двух строк -> стало 5 строк
            Assert::AreEqual(static_cast<size_t>(5), task.getMatrix().getRows());

            // После строки 1 (теперь строка 2): [1, 2]
            Assert::AreEqual(1, task.getMatrix()[2][0]);
            Assert::AreEqual(2, task.getMatrix()[2][1]);

            // После строки 2 (теперь строка 4): [1, 2]
            Assert::AreEqual(1, task.getMatrix()[4][0]);
            Assert::AreEqual(2, task.getMatrix()[4][1]);
        }

        /**
         * @brief Матрица из одной строки
         */
        TEST_METHOD(InsertFirstRow_SingleRowMatrix)
        {
            Matrix<int> m(1, 2);
            m[0][0] = 7; m[0][1] = 3;

            Task2 task(m);
            task.solve();

            // После строки 0 вставляется её копия -> размер 2
            Assert::AreEqual(static_cast<size_t>(2), task.getMatrix().getRows());
            Assert::AreEqual(7, task.getMatrix()[1][0]);
            Assert::AreEqual(3, task.getMatrix()[1][1]);
        }

        /**
         * @brief Пустая матрица не изменяется
         */
        TEST_METHOD(EmptyMatrix_ShouldNotChange)
        {
            Matrix<int> m;
            Task2 task(m);
            task.solve();
            Assert::AreEqual(static_cast<size_t>(0), task.getMatrix().getRows());
        }

        /**
         * @brief Описание задачи не является пустым
         */
        TEST_METHOD(Description_ShouldNotBeEmpty)
        {
            Matrix<int> m(1, 1);
            Task2 task(m);
            Assert::IsFalse(task.description().empty());
        }

        /**
         * @brief Полиморфный вызов через базовый указатель Exercise*
         */
        TEST_METHOD(PolymorphicCall_ThroughExerciseBasePointer)
        {
            Matrix<int> m(2, 2);
            m[0][0] = 1; m[0][1] = 2;
            m[1][0] = 8; m[1][1] = 3;

            std::unique_ptr<Exercise> ex = std::make_unique<Task2>(m);
            ex->solve();

            Assert::AreEqual(static_cast<size_t>(3), ex->getMatrix().getRows());
            Assert::AreEqual(1, ex->getMatrix()[2][0]);
            Assert::AreEqual(2, ex->getMatrix()[2][1]);
        }
    };

    /**
     * @brief Модульные тесты генераторов
     */
    TEST_CLASS(GeneratorTests)
    {
    public:
        /**
         * @brief RandomGenerator возвращает значение в заданном диапазоне
         */
        TEST_METHOD(RandomGenerator_ShouldReturnValueInRange)
        {
            RandomGenerator gen(-5, 5);
            for (size_t i = 0; i < 100; ++i)
            {
                int v = gen.generate();
                Assert::IsTrue(v >= -5 && v <= 5);
            }
        }

        /**
         * @brief RandomGenerator выбрасывает invalid_argument при некорректном диапазоне (min > max)
         */
        TEST_METHOD(RandomGenerator_InvalidRange_ShouldThrow)
        {
            auto func = []() { RandomGenerator gen(10, 5); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        /**
         * @brief IStreamGenerator считывает числа из входного потока
         */
        TEST_METHOD(IStreamGenerator_ShouldReadFromStream)
        {
            std::istringstream input("42 -7 13");
            IStreamGenerator gen(input);

            Assert::AreEqual(42, gen.generate());
            Assert::AreEqual(-7, gen.generate());
            Assert::AreEqual(13, gen.generate());
        }

        /**
         * @brief ConstGenerator всегда возвращает заданное константное значение
         */
        TEST_METHOD(ConstGenerator_ShouldReturnConstant)
        {
            ConstGenerator gen(99);
            Assert::AreEqual(99, gen.generate());
            Assert::AreEqual(99, gen.generate());
        }
    };
}
