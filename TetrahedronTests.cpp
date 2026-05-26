#include "CppUnitTest.h"
#include "../TetrahedronLib/Tetrahedron.h"
#include "../TetrahedronLib/Point.h"
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geometry;

namespace Tests
{
    TEST_CLASS(PointTests)
    {
    public:
        // 1. Тест конструктора по умолчанию
        TEST_METHOD(DefaultConstructor_Success)
        {
            // Arrange & Act
            Point p;

            // Assert
            Assert::AreEqual(0.0, p.getX());
            Assert::AreEqual(0.0, p.getY());
            Assert::AreEqual(0.0, p.getZ());
        }

        // 2. Тест конструктора с параметрами
        TEST_METHOD(ParameterizedConstructor_Success)
        {
            // Arrange
            double x = 3.5;
            double y = 7.2;
            double z = 1.8;

            // Act
            Point p(x, y, z);

            // Assert
            Assert::AreEqual(x, p.getX());
            Assert::AreEqual(y, p.getY());
            Assert::AreEqual(z, p.getZ());
        }

        // 3. Тест метода distanceTo
        TEST_METHOD(DistanceTo_Success)
        {
            // Arrange
            Point p1(0, 0, 0);
            Point p2(3, 4, 0);
            double expected1 = 5.0;

            Point p3(1, 2, 2);
            Point p4(4, 6, 10);
            double expected2 = std::sqrt(89.0);

            // Act
            double dist1 = p1.distanceTo(p2);
            double dist2 = p3.distanceTo(p4);

            // Assert
            Assert::AreEqual(expected1, dist1, 1e-6);
            Assert::AreEqual(expected2, dist2, 1e-6);
        }

        // 4. Тест оператора ==
        TEST_METHOD(EqualityOperator_Success)
        {
            // Arrange
            Point p1(2.5, 3.5, 4.5);
            Point p2(2.5, 3.5, 4.5);
            Point p3(2.5, 4.0, 4.5);

            // Act & Assert
            Assert::IsTrue(p1 == p2);
            Assert::IsFalse(p1 == p3);
        }

        // 5. Тест оператора !=
        TEST_METHOD(InequalityOperator_Success)
        {
            // Arrange
            Point p1(2.5, 3.5, 4.5);
            Point p2(2.5, 3.5, 4.5);
            Point p3(2.5, 4.0, 4.5);

            // Act & Assert
            Assert::IsFalse(p1 != p2);
            Assert::IsTrue(p1 != p3);
        }

        // 6. Тест оператора вывода <<
        TEST_METHOD(OutputStreamOperator_Success)
        {
            // Arrange
            Point p(3.14, 2.71, 1.41);
            std::stringstream ss;

            // Act
            ss << p;
            std::string result = ss.str();

            // Assert
            Assert::IsTrue(result.find("(") != std::string::npos);
            Assert::IsTrue(result.find(")") != std::string::npos);
        }

        // 7. Тест оператора ввода >>
        TEST_METHOD(InputStreamOperator_Success)
        {
            // Arrange
            Point p;
            std::stringstream ss("(15.5, 20.3, 25.7)");
            double expectedX = 15.5;
            double expectedY = 20.3;
            double expectedZ = 25.7;

            // Act
            ss >> p;

            // Assert
            Assert::AreEqual(expectedX, p.getX());
            Assert::AreEqual(expectedY, p.getY());
            Assert::AreEqual(expectedZ, p.getZ());
        }
    };

    TEST_CLASS(TetrahedronTests)
    {
    public:
        // 8. Тест конструктора по умолчанию
        TEST_METHOD(DefaultConstructor_Success)
        {
            // Arrange & Act
            Tetrahedron t;

            // Assert
            Assert::IsTrue(true);
        }

        // 9. Тест конструктора с точками
        TEST_METHOD(ConstructorWithPoints_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            double expectedSurface = std::sqrt(3.0) * 8.0;
            double expectedVolume = std::sqrt(2.0) * std::pow(std::sqrt(8.0), 3) / 12.0;

            // Act
            Tetrahedron t(p1, p2, p3, p4);

            // Assert
            Assert::AreEqual(expectedSurface, t.getSurfaceArea(), 1e-6);
            Assert::AreEqual(expectedVolume, t.getVolume(), 1e-6);
        }

        // 10. Тест конструктора с координатами
        TEST_METHOD(ConstructorWithCoordinates_Success)
        {
            // Arrange
            double expectedSurface = std::sqrt(3.0) * 8.0;

            // Act
            Tetrahedron t(1, 1, 1, 1, -1, -1, -1, 1, -1, -1, -1, 1);

            // Assert
            Assert::AreEqual(expectedSurface, t.getSurfaceArea(), 1e-6);
        }

        // 11. Тест конструктора копирования
        TEST_METHOD(CopyConstructor_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron original(p1, p2, p3, p4);

            // Act
            Tetrahedron copy(original);

            // Assert
            Assert::IsTrue(original == copy);
        }

        // 12. Тест оператора присваивания
        TEST_METHOD(AssignmentOperator_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron original(p1, p2, p3, p4);
            Tetrahedron assigned;

            // Act
            assigned = original;

            // Assert
            Assert::IsTrue(original == assigned);
        }

        // 13. Тест оператора ==
        TEST_METHOD(EqualityOperator_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t1(p1, p2, p3, p4);
            Tetrahedron t2(p1, p2, p3, p4);
            Tetrahedron t3(Point(0, 0, 0), 2.0, SphereType::Circumscribed);

            // Act & Assert
            Assert::IsTrue(t1 == t2);
            Assert::IsFalse(t1 == t3);
        }

        // 14. Тест оператора !=
        TEST_METHOD(InequalityOperator_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t1(p1, p2, p3, p4);
            Tetrahedron t2(p1, p2, p3, p4);
            Tetrahedron t3(Point(0, 0, 0), 2.0, SphereType::Circumscribed);

            // Act & Assert
            Assert::IsFalse(t1 != t2);
            Assert::IsTrue(t1 != t3);
        }

        // 15. Тест getSurfaceArea (Edge=1)
        TEST_METHOD(GetSurfaceArea_Edge1_Success)
        {
            // Arrange
            Tetrahedron t(Point(0, 0, 0), 1.0, SphereType::Circumscribed);
            double expected = std::sqrt(3.0);

            // Act
            double result = t.getSurfaceArea();

            // Assert
            Assert::AreEqual(expected, result, 1e-6);
        }

        // 16. Тест getSurfaceArea (Edge=2)
        TEST_METHOD(GetSurfaceArea_Edge2_Success)
        {
            // Arrange
            Tetrahedron t(Point(0, 0, 0), 2.0, SphereType::Inscribed);
            double expected = 4.0 * std::sqrt(3.0);

            // Act
            double result = t.getSurfaceArea();

            // Assert
            Assert::AreEqual(expected, result, 1e-6);
        }

        // 17. Тест getVolume (Edge=1)
        TEST_METHOD(GetVolume_Edge1_Success)
        {
            // Arrange
            Tetrahedron t(Point(0, 0, 0), 1.0, SphereType::Circumscribed);
            double expected = std::sqrt(2.0) / 12.0;

            // Act
            double result = t.getVolume();

            // Assert
            Assert::AreEqual(expected, result, 1e-6);
        }

        // 18. Тест getVolume (Edge=2)
        TEST_METHOD(GetVolume_Edge2_Success)
        {
            // Arrange
            Tetrahedron t(Point(0, 0, 0), 2.0, SphereType::Inscribed);
            double expected = std::sqrt(2.0) * 8.0 / 12.0;

            // Act
            double result = t.getVolume();

            // Assert
            Assert::AreEqual(expected, result, 1e-6);
        }

        // 19. Тест метода ToString
        TEST_METHOD(ToString_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);

            // Act
            std::string result = t.ToString();

            // Assert
            Assert::IsTrue(result.find("Tetrahedron") != std::string::npos);
            Assert::IsTrue(result.find("v1=") != std::string::npos);
            Assert::IsTrue(result.find("v2=") != std::string::npos);
            Assert::IsTrue(result.find("v3=") != std::string::npos);
            Assert::IsTrue(result.find("v4=") != std::string::npos);
        }

        // 20. Тест некорректных вершин (исключение)
        TEST_METHOD(InvalidVertices_ThrowsException)
        {
            // Act
            auto func = []() {
                Tetrahedron t(0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3);
                };

            // Assert
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 21. Тест отрицательной длины ребра (исключение)
        TEST_METHOD(NegativeEdgeLength_ThrowsException)
        {
            // Act
            auto func = []() {
                Tetrahedron t(Point(0, 0, 0), -1.0, SphereType::Circumscribed);
                };

            // Assert
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 22. Тест нулевой длины ребра (исключение)
        TEST_METHOD(ZeroEdgeLength_ThrowsException)
        {
            // Act
            auto func = []() {
                Tetrahedron t(Point(0, 0, 0), 0.0, SphereType::Circumscribed);
                };

            // Assert
            Assert::ExpectException<std::invalid_argument>(func);
        }

        // 23. Тест полиморфизма
        TEST_METHOD(Polymorphism_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);
            double expectedSurface = std::sqrt(3.0) * 8.0;

            // Act
            RegularSolid* solid = &t;
            double result = solid->getSurfaceArea();

            // Assert
            Assert::AreEqual(expectedSurface, result, 1e-6);
        }

        // 24. Тест создания через описанную сферу
        TEST_METHOD(CreateFromCircumscribedSphere_Success)
        {
            // Arrange
            Point center(1.0, 2.0, 3.0);
            double edgeLength = 2.0;
            double expected = edgeLength * edgeLength * std::sqrt(3.0);

            // Act
            Tetrahedron t = Tetrahedron::createFromCircumscribedSphere(center, edgeLength);

            // Assert
            Assert::AreEqual(expected, t.getSurfaceArea(), 1e-6);
        }

        // 25. Тест создания через вписанную сферу
        TEST_METHOD(CreateFromInscribedSphere_Success)
        {
            // Arrange
            Point center(1.0, 2.0, 3.0);
            double edgeLength = 3.0;
            double expected = edgeLength * edgeLength * std::sqrt(3.0);

            // Act
            Tetrahedron t = Tetrahedron::createFromInscribedSphere(center, edgeLength);

            // Assert
            Assert::AreEqual(expected, t.getSurfaceArea(), 1e-6);
        }

        // 26. Тест getVertices
        TEST_METHOD(GetVertices_Success)
        {
            // Arrange
            Point p1(1, 1, 1);
            Point p2(1, -1, -1);
            Point p3(-1, 1, -1);
            Point p4(-1, -1, 1);
            Tetrahedron t(p1, p2, p3, p4);

            // Act
            std::vector<Point> verts = t.getVertices();

            // Assert
            Assert::AreEqual(size_t(4), verts.size());
        }
    };
}
