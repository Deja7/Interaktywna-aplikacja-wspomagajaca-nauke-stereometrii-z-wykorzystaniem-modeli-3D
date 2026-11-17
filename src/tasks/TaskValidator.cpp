#include "tasks/TaskValidator.hpp"

#include <cmath>
#include <unordered_set>

namespace stereometria {

bool TaskValidator::isSupportedSolidType(const std::string& typeId) {
    static const std::unordered_set<std::string> kSupportedTypes = {
        "cube",
        "cuboid",
        "regular_tri_prism",
        "regular_quad_prism",
        "regular_hex_prism",
        "regular_tet_pyramid",
        "regular_tri_pyramid",
        "regular_quad_pyramid",
        "regular_hex_pyramid",
        "cylinder",
        "cone",
        "sphere"
    };
    return kSupportedTypes.find(typeId) != kSupportedTypes.end();
}

ValidationResult TaskValidator::validateTask(const Task& task) {
    ValidationResult result;

    if (task.id.empty()) {
        result.isValid = false;
        result.errors.push_back("Brak identyfikatora zadania (id).");
    }

    if (task.problemStatement.empty()) {
        result.isValid = false;
        result.errors.push_back("Brak tresci zadania (problem_statement).");
    }

    if (!isSupportedSolidType(task.solid.type)) {
        result.isValid = false;
        result.errors.push_back("Nieobsługiwany typ bryły: " + task.solid.type);
    }

    if (task.solid.initialDimensions.empty()) {
        result.isValid = false;
        result.errors.push_back("Brak wymiarow poczatkowych bryly (initial_dimensions).");
    }

    for (const auto& [dimName, dimValue] : task.solid.initialDimensions) {
        if (!std::isfinite(dimValue) || dimValue <= 0.0) {
            result.isValid = false;
            result.errors.push_back("Wymiar '" + dimName + "' musi byc dodatnia liczba rzeczywista.");
        }
    }

    if (task.solid.defaultOpacity < 0.0 || task.solid.defaultOpacity > 1.0) {
        result.isValid = false;
        result.errors.push_back("Parametr przezroczystosci (default_opacity) musi nalezec do przedzialu [0.0, 1.0].");
    }

    if (task.steps.empty()) {
        result.isValid = false;
        result.errors.push_back("Zadanie musi zawierac co najmniej jeden krok rozwiazania (steps).");
    }

    for (const auto& step : task.steps) {
        if (step.tolerance <= 0.0 || !std::isfinite(step.tolerance)) {
            result.isValid = false;
            result.errors.push_back("Niepoprawna tolerancja w kroku nr " + std::to_string(step.stepNumber));
        }
    }

    return result;
}

bool TaskValidator::checkNumericAnswer(const TaskStep& step, double userValue) {
    if (!std::isfinite(userValue)) {
        return false;
    }
    return std::abs(userValue - step.expectedValue) <= step.tolerance;
}

} // namespace stereometria
