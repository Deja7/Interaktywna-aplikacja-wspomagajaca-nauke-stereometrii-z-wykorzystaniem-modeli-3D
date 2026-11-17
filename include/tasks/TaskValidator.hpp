#pragma once

#include "tasks/Task.hpp"
#include <string>
#include <vector>

namespace stereometria {

struct ValidationResult {
    bool isValid{true};
    std::vector<std::string> errors;
};

/**
 * @brief Walidator danych wejściowych zadań JSON oraz odpowiedzi użytkownika.
 */
class TaskValidator {
public:
    /// Sprawdza spójność wczytanego zadania (wymiary > 0, poprawny typ bryły, niepuste kroki)
    static ValidationResult validateTask(const Task& task);

    /// Sprawdza, czy dany identyfikator typu bryły należy do wspieranych w podstawie programowej
    static bool isSupportedSolidType(const std::string& typeId);

    /// Weryfikuje odpowiedź liczbową ucznia dla danego kroku z uwzględnieniem tolerancji
    static bool checkNumericAnswer(const TaskStep& step, double userValue);
};

} // namespace stereometria
