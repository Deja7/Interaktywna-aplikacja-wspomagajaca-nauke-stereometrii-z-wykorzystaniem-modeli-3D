#include "solids/Solid3D.hpp"
#include "tasks/Task.hpp"
#include "tasks/TaskValidator.hpp"

#include <iostream>

int main() {
    using namespace stereometria;

    // Przykładowa instancja zadania (odpowiadająca data/tasks/ostrostup_czworokatny_kat_01.json)
    Task sampleTask;
    sampleTask.id = "matura_pp_ostrostup_01";
    sampleTask.title = "Objetosc ostroslupa prawidlowego czworokatnego z katem krawedzi bocznej";
    sampleTask.educationLevel = "secondary_basic";
    sampleTask.topic = "pyramids_angles";
    sampleTask.difficulty = 2;
    sampleTask.problemStatement =
        "W ostroslupie prawidlowym czworokatnym dlugosc krawedzi podstawy wynosi a = 6, "
        "a krawedz boczna tworzy z plaszczyzna podstawy kat alpha = 45 stopni. "
        "Oblicz objetosc tego ostroslupa.";

    sampleTask.solid.type = "regular_quad_pyramid";
    sampleTask.solid.initialDimensions = {{"a", 6.0}, {"H", 4.24264}};
    sampleTask.solid.defaultOpacity = 0.35;

    TaskStep step1;
    step1.stepNumber = 1;
    step1.instruction = "Oblicz dlugosc przekatnej podstawy d (kwadratu o boku a = 6).";
    step1.visualization.highlightFaces = {"base"};
    step1.visualization.highlightSegments = {"base_edge_AB", "base_diagonal_AC"};
    step1.visualization.helperTriangle = std::array<std::string, 3>{"A", "B", "C"};
    step1.targetParameter = "d";
    step1.expectedValue = 8.48528;
    step1.tolerance = 0.05;
    step1.formulaHint = "d = a * sqrt(2)";
    sampleTask.steps.push_back(step1);

    ValidationResult validation = TaskValidator::validateTask(sampleTask);
    std::cout << "[Stereometria3D] Walidacja zadania '" << sampleTask.id << "': "
              << (validation.isValid ? "OK" : "BLAD") << "\n";

    double testStudentAnswer = 8.49;
    bool stepOk = TaskValidator::checkNumericAnswer(sampleTask.steps[0], testStudentAnswer);
    std::cout << "[Stereometria3D] Test odpowiedzi ucznia (d = " << testStudentAnswer
              << "): " << (stepOk ? "POPRAWNA" : "BLEDNA") << "\n";

    return validation.isValid && stepOk ? 0 : 1;
}
