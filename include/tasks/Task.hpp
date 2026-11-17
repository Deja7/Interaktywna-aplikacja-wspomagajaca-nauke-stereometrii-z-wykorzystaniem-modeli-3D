#pragma once

#include <array>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace stereometria {

/**
 * @brief Konfiguracja podświetlenia elementów 3D w pojedynczym kroku zadania.
 */
struct StepVisualization {
    std::vector<std::string> highlightFaces;    // np. ["base"]
    std::vector<std::string> highlightSegments; // np. ["height_SO", "half_diagonal_AO"]
    std::vector<std::string> highlightAngles;   // np. ["angle_lateral_edge_base"]
    std::optional<std::array<std::string, 3>> helperTriangle; // np. {"A", "O", "S"}
};

/**
 * @brief Pojedynczy krok scenariusza rozwiązania zadania ("krok po kroku").
 */
struct TaskStep {
    int stepNumber{1};
    std::string instruction;
    StepVisualization visualization;
    std::string interactionType{"numeric_input"}; // "numeric_input" lub "select_element"
    std::string targetParameter;                  // np. "d", "H", "V"
    double expectedValue{0.0};
    double tolerance{0.05};
    std::string formulaHint;
};

/**
 * @brief Konfiguracja początkowa modelu 3D powiązanego z zadaniem.
 */
struct TaskSolidConfig {
    std::string type; // np. "regular_quad_pyramid"
    std::unordered_map<std::string, double> initialDimensions;
    double defaultOpacity{0.35};
};

/**
 * @brief Struktura reprezentująca zadanie stereometryczne wczytane z pliku JSON.
 */
struct Task {
    std::string id;
    std::string title;
    std::string educationLevel; // "primary", "secondary_basic", "secondary_extended"
    std::string topic;
    int difficulty{1};
    std::string problemStatement;
    TaskSolidConfig solid;
    std::vector<TaskStep> steps;
};

} // namespace stereometria
