---
name: stereometria-zadania-json
description: >-
  Projektowanie bazy zadań stereometrycznych (JSON), scenariuszy wizualizacji przestrzennej
  "krok po kroku", walidacji danych wejściowych oraz testów dla aplikacji do nauki stereometrii.
  Używaj tego skilla podczas tworzenia schematu JSON, pisania zadań zgodnych z podstawą
  programową (szkoła podstawowa i średnia/matura), implementacji trybu rozwiązywania zadań
  oraz testów jednostkowych i funkcjonalnych.
---

# Baza zadań JSON, Scenariusze Wizualizacji i Walidacja (`stereometria-zadania-json`)

Ten skill wspiera główny obszar odpowiedzialności **Macieja Raniszewskiego** określony w dokumentacji RPI i DPP (Etapy A, F, G, H):
- Projektowanie struktur danych (JSON) dla zadań i scenariuszy wizualizacji.
- Walidacja danych wejściowych oraz odpowiedzi użytkownika.
- Zgodność zadań z podstawą programową stereometrii (szkoły podstawowe i ponadpodstawowe / matura).
- Testowanie jednostkowe, integracyjne i funkcjonalne.

## 1. Zakres dydaktyczny (Podstawa programowa)

Zadania i modele muszą ściśle odpowiadać podstawie programowej szkół podstawowych (klasy VII–VIII) oraz ponadpodstawowych (poziom podstawowy i rozszerzony matury):

- **Bryły**:
  - Graniastosłupy proste i prawidłowe (sześcian, prostopadłościan, trójkątny, czworokątny, sześciokątny).
  - Ostrosłupy prawidłowe (trójkątny / czworościan foremny, czworokątny, sześciokątny).
  - Bryły obrotowe (walec, stożek, kula).
- **Kluczowe zagadnienia i relacje przestrzenne**:
  - Obliczanie pól powierzchni ($P_p, P_b, P_c$) i objętości ($V$).
  - Wyznaczanie długości przekątnych podstawy, przekątnych ścian bocznych i przekątnych głównych bryły.
  - Wysokości bryły ($H$) oraz wysokości ściany bocznej ($h_b$) — wykorzystanie twierdzenia Pitagorasa i funkcji trygonometrycznych w wyróżnionych trójkątach prostokątnych wewnątrz bryły.
  - **Kąty w przestrzeni** (najczęstsze źródło błędów uczniów):
    - Kąt nachylenia przekątnej graniastosłupa do płaszczyzny podstawy.
    - Kąt nachylenia krawędzi bocznej ostrosłupa do płaszczyzny podstawy.
    - Kąt nachylenia ściany bocznej ostrosłupa do płaszczyzny podstawy (kąt dwuścienny).
    - Kąt rozwarcia stożka oraz kąt nachylenia tworzącej stożka do podstawy.
  - **Przekroje brył płaszczyzną** (np. przekrój osiowy walca/stożka, przekrój sześcianu lub ostrosłupa płaszczyzną przechodzącą przez wybrane wierzchołki/krawędzie).

## 2. Wzorcowy schemat zadania JSON

Każde zadanie w katalogu `data/tasks/` powinno łączyć:
1. Metadane dydaktyczne (poziom edukacyjny, kategoria, trudność).
2. Konfigurację początkową bryły 3D (`solid`).
3. Kroki wizualizacji i rozwiązywania (`steps`), które prowadzą ucznia przez zadanie i podświetlają elementy w przestrzeni 3D.

```json
{
  "id": "matura_pp_ostrostup_01",
  "title": "Objętość ostrosłupa prawidłowego czworokątnego z kątem krawędzi bocznej",
  "education_level": "secondary_basic",
  "topic": "pyramids_angles",
  "difficulty": 2,
  "problem_statement": "W ostrosłupie prawidłowym czworokątnym długość krawędzi podstawy wynosi a = 6, a krawędź boczna tworzy z płaszczyzną podstawy kąt α = 45°. Oblicz objętość tego ostrosłupa.",
  "solid": {
    "type": "regular_quad_pyramid",
    "initial_dimensions": {
      "a": 6.0,
      "H": 4.24264
    },
    "default_opacity": 0.35
  },
  "steps": [
    {
      "step_number": 1,
      "instruction": "Wskaż lub oblicz długość przekątnej podstawy d (kwadratu o boku a = 6).",
      "visualization": {
        "highlight_faces": ["base"],
        "highlight_segments": ["base_diagonal_AC"],
        "highlight_angles": [],
        "show_helper_triangle": null
      },
      "interaction_type": "numeric_input",
      "target_parameter": "d",
      "expected_value": 8.48528,
      "tolerance": 0.05,
      "formula_hint": "d = a * sqrt(2)"
    },
    {
      "step_number": 2,
      "instruction": "Zauważ trójkąt prostokątny utworzony przez wysokość ostrosłupa H, połowę przekątnej podstawy (d/2) oraz krawędź boczną. Ponieważ kąt α = 45°, wyznacz wysokość H.",
      "visualization": {
        "highlight_faces": [],
        "highlight_segments": ["height_SO", "half_diagonal_AO", "lateral_edge_AS"],
        "highlight_angles": ["angle_lateral_edge_base"],
        "show_helper_triangle": ["A", "O", "S"]
      },
      "interaction_type": "numeric_input",
      "target_parameter": "H",
      "expected_value": 4.24264,
      "tolerance": 0.05,
      "formula_hint": "tg(45°) = H / (d/2) => H = d / 2"
    },
    {
      "step_number": 3,
      "instruction": "Oblicz objętość ostrosłupa ze wzoru V = (1/3) * Pp * H.",
      "visualization": {
        "highlight_faces": ["base"],
        "highlight_segments": ["height_SO"],
        "highlight_angles": [],
        "show_helper_triangle": null
      },
      "interaction_type": "numeric_input",
      "target_parameter": "V",
      "expected_value": 50.91168,
      "tolerance": 0.1,
      "formula_hint": "V = (1/3) * a^2 * H"
    }
  ]
}
```

## 3. Reguły walidacji danych i odpowiedzi

1. **Walidacja schematu JSON przy ładowaniu**:
   - Sprawdzenie obecności wymaganych pól (`id`, `problem_statement`, `solid.type`, `steps`).
   - Weryfikacja, czy `solid.type` należy do wspieranych typów brył.
   - Weryfikacja dodatniości wymiarów początkowych (`> 0`) oraz zakresu `default_opacity` $\in [0.0, 1.0]$.
   - Sprawdzenie, czy wszystkie identyfikatory w `visualization` (`highlight_segments`, `highlight_angles`, wierzchołki trójkąta pomocniczego) istnieją w definicji danego typu bryły.
2. **Walidacja odpowiedzi ucznia (Tryb rozwiązywania zadań)**:
   - Porównywanie wartości zmiennoprzecinkowych z zadaną tolerancją: $|x_{\text{user}} - x_{\text{expected}}| \le \text{tolerance}$.
   - Obsługa zarówno postaci dziesiętnej (np. `8.49`), jak i prostych wyrażeń z pierwiastkiem, jeśli parser wejścia na to pozwala (np. `6*sqrt(2)`).
   - Obsługa kroków interaktywnych typu `"select_element"` (współpraca z modułem pickingu Pawła — sprawdzenie, czy kliknięty przez ucznia element ma ID zgodne z `expected_element_id`).

## 4. Testowanie jednostkowe i funkcjonalne

Przy tworzeniu lub modyfikacji bazy zadań i walidatorów zawsze uwzględniaj:
- **Testy jednostkowe walidatora JSON**: poprawne pliki zadań, brakujące klucze, ujemne wymiary, nieistniejące ID krawędzi/kątów.
- **Testy wzorów matematycznych brył**: dla każdej bryły zestaw przypadków referencyjnych (np. sześcian $a=2 \Rightarrow V=8, P_c=24, d=2\sqrt{3}$).
- **Testy przypadków brzegowych**: bardzo małe/duże wymiary, zaokrąglenia zmiennoprzecinkowe.
