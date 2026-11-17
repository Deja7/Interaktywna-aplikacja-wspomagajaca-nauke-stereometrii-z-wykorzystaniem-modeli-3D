#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace stereometria {

struct Vec3 {
    double x{0.0};
    double y{0.0};
    double z{0.0};
};

struct NamedSegment {
    std::string id;          // np. "height_SO", "base_diagonal_AC"
    std::string startVertex; // np. "S"
    std::string endVertex;   // np. "O"
    double length{0.0};
};

struct NamedAngle {
    std::string id;          // np. "angle_lateral_edge_base"
    std::string vertexA;     // np. "O"
    std::string apexVertex;  // wierzchołek kąta, np. "A"
    std::string vertexB;     // np. "S"
    double degrees{0.0};
};

/**
 * @brief Abstrakcyjna klasa bazowa dla wszystkich brył stereometrycznych (Etap B).
 *
 * Stanowi kontrakt pomiędzy:
 * - modułem matematycznym/geometrycznym (obliczenia wymiarów, pól, objętości),
 * - modułem renderowania 3D (wierzchołki, krawędzie, przezroczystość),
 * - modułem zadań JSON i pickingu (nazwane elementy bryły).
 */
class Solid3D {
public:
    virtual ~Solid3D() = default;

    /// Zwraca identyfikator typu bryły zgodny ze schematem JSON (np. "regular_quad_pyramid")
    virtual std::string getTypeId() const = 0;

    /// Zwraca polską nazwę bryły do wyświetlenia w UI
    virtual std::string getDisplayName() const = 0;

    /// Ustawia wymiar wejściowy (np. "a" = 6.0, "H" = 4.24) i przelicza geometrię
    bool setDimension(const std::string& name, double value) {
        if (value <= 0.0) {
            return false;
        }
        dimensions_[name] = value;
        updateGeometry();
        return true;
    }

    const std::unordered_map<std::string, double>& getDimensions() const {
        return dimensions_;
    }

    /// Przelicza współrzędne wierzchołków 3D, długości odcinków i miary kątów
    virtual void updateGeometry() = 0;

    /// Obliczenia podstawowe wymagane przez podstawę programową
    virtual double getBaseArea() const = 0;         // Pp
    virtual double getLateralSurfaceArea() const = 0; // Pb
    virtual double getTotalSurfaceArea() const = 0; // Pc
    virtual double getVolume() const = 0;           // V

    /// Dostęp do nazwanych elementów dla modułu wizualizacji krok-po-kroku oraz pickingu
    const std::unordered_map<std::string, Vec3>& getVertices() const { return vertices_; }
    const std::vector<NamedSegment>& getSegments() const { return segments_; }
    const std::vector<NamedAngle>& getAngles() const { return angles_; }

protected:
    std::unordered_map<std::string, double> dimensions_;
    std::unordered_map<std::string, Vec3> vertices_;
    std::vector<NamedSegment> segments_;
    std::vector<NamedAngle> angles_;
};

} // namespace stereometria
