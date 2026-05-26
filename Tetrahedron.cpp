#define _USE_MATH_DEFINES
#include "Tetrahedron.h"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <limits>

namespace geometry {
    Tetrahedron::Tetrahedron() {}

    Tetrahedron::Tetrahedron(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
        vertices.push_back(p1);
        vertices.push_back(p2);
        vertices.push_back(p3);
        vertices.push_back(p4);

        if (!isValidTetrahedron()) {
            throw std::invalid_argument("Некорректные вершины для правильного тетраэдра");
        }
    }

    Tetrahedron::Tetrahedron(const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2,
        const double x3, const double y3, const double z3,
        const double x4, const double y4, const double z4) {
        vertices.push_back(Point(x1, y1, z1));
        vertices.push_back(Point(x2, y2, z2));
        vertices.push_back(Point(x3, y3, z3));
        vertices.push_back(Point(x4, y4, z4));

        if (!isValidTetrahedron()) {
            throw std::invalid_argument("Некорректные вершины для правильного тетраэдра");
        }
    }

    Tetrahedron::Tetrahedron(const Point& center, double edgeLength, SphereType sphereType) {
        if (edgeLength <= 0) {
            throw std::invalid_argument("Длина ребра тетраэдра должна быть положительным числом");
        }

        double h = edgeLength * std::sqrt(6.0) / 3.0;
        double rBase = edgeLength * std::sqrt(3.0) / 3.0;

        Point v1, v2, v3, v4;

        if (sphereType == SphereType::Circumscribed) {
            double radius = edgeLength * std::sqrt(6.0) / 4.0;
            v1 = Point(center.getX(), center.getY(), center.getZ() + radius);
            v2 = Point(center.getX(), center.getY() + rBase, center.getZ() - radius / 3.0);
            v3 = Point(center.getX() + edgeLength / 2.0, center.getY() - rBase / 2.0, center.getZ() - radius / 3.0);
            v4 = Point(center.getX() - edgeLength / 2.0, center.getY() - rBase / 2.0, center.getZ() - radius / 3.0);
        }
        else {
            double radius = edgeLength * std::sqrt(6.0) / 12.0;
            v1 = Point(center.getX(), center.getY(), center.getZ() + h - radius);
            v2 = Point(center.getX(), center.getY() + rBase, center.getZ() - radius);
            v3 = Point(center.getX() + edgeLength / 2.0, center.getY() - rBase / 2.0, center.getZ() - radius);
            v4 = Point(center.getX() - edgeLength / 2.0, center.getY() - rBase / 2.0, center.getZ() - radius);
        }

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v4);

        if (!isValidTetrahedron()) {
            throw std::invalid_argument("Не удалось создать корректный тетраэдр с заданными параметрами");
        }
    }

    Tetrahedron::Tetrahedron(const Tetrahedron& other) : vertices(other.vertices) {}

    Tetrahedron& Tetrahedron::operator=(const Tetrahedron& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }

    bool Tetrahedron::isValidTetrahedron() const {
        if (vertices.size() != VERTEX_COUNT) {
            return false;
        }

        std::vector<double> edges;
        for (size_t i = 0; i < vertices.size(); ++i) {
            for (size_t j = i + 1; j < vertices.size(); ++j) {
                double dist = vertices[i].distanceTo(vertices[j]);
                if (dist <= 0) {
                    return false;
                }
                edges.push_back(dist);
            }
        }

        double firstEdge = edges[0];
        for (size_t i = 1; i < edges.size(); ++i) {
            if (std::abs(edges[i] - firstEdge) > 1e-6) {
                return false;
            }
        }

        return true;
    }

    double Tetrahedron::getEdgeLength() const {
        if (vertices.size() != VERTEX_COUNT) {
            return 0.0;
        }
        return vertices[0].distanceTo(vertices[1]);
    }

    double Tetrahedron::getSurfaceArea() const {
        if (vertices.size() != VERTEX_COUNT) {
            return 0.0;
        }

        double edge = getEdgeLength();
        return std::sqrt(3.0) * edge * edge;
    }

    double Tetrahedron::getVolume() const {
        if (vertices.size() != VERTEX_COUNT) {
            return 0.0;
        }

        double edge = getEdgeLength();
        return std::sqrt(2.0) * edge * edge * edge / 12.0;
    }

    std::string Tetrahedron::ToString() const {
        std::stringstream ss;
        ss << "Tetrahedron: ";
        for (size_t i = 0; i < vertices.size(); ++i) {
            ss << "v" << (i + 1) << "=" << vertices[i];
            if (i < vertices.size() - 1) {
                ss << ", ";
            }
        }
        ss << ", Edge=" << getEdgeLength();
        ss << ", SurfaceArea=" << getSurfaceArea();
        ss << ", Volume=" << getVolume();
        return ss.str();
    }

    void Tetrahedron::read(std::istream& is) {
        std::vector<Point> newVertices;
        newVertices.resize(VERTEX_COUNT);

        char bracket, comma1, comma2;
        double x, y, z;

        for (size_t i = 0; i < VERTEX_COUNT; ++i) {
            is >> bracket >> x >> comma1 >> y >> comma2 >> z >> bracket;
            newVertices[i] = Point(x, y, z);
        }

        vertices = newVertices;
        if (!isValidTetrahedron()) {
            throw std::invalid_argument("Некорректные вершины для правильного тетраэдра при чтении");
        }
    }

    bool Tetrahedron::operator==(const Tetrahedron& other) const {
        if (vertices.size() != other.vertices.size()) {
            return false;
        }

        for (size_t i = 0; i < vertices.size(); ++i) {
            if (vertices[i] != other.vertices[i]) {
                return false;
            }
        }
        return true;
    }

    bool Tetrahedron::operator!=(const Tetrahedron& other) const {
        return !(*this == other);
    }

    std::vector<Point> Tetrahedron::getVertices() const {
        return vertices;
    }

    std::string Tetrahedron::ToString(const Tetrahedron& tetrahedron) {
        return tetrahedron.ToString();
    }

    Tetrahedron Tetrahedron::readFromStream(std::istream& is) {
        Tetrahedron tetrahedron;
        tetrahedron.read(is);
        return tetrahedron;
    }

    Tetrahedron Tetrahedron::createFromCircumscribedSphere(const Point& center, double edgeLength) {
        return Tetrahedron(center, edgeLength, SphereType::Circumscribed);
    }

    Tetrahedron Tetrahedron::createFromInscribedSphere(const Point& center, double edgeLength) {
        return Tetrahedron(center, edgeLength, SphereType::Inscribed);
    }
}
