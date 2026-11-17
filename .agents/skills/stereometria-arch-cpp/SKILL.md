---
name: stereometria-arch-cpp
description: >-
  Architektura C++, silnik graficzny 3D (OpenGL, GLSL, SFML/GLFW), hierarchia klas brył
  oraz silnik obliczeń matematycznych dla projektu "Interaktywna aplikacja wspomagająca
  naukę stereometrii z wykorzystaniem modeli 3D". Używaj tego skilla podczas projektowania
  architektury kodu, konfiguracji CMake/Visual Studio, implementacji klas brył, kamery,
  renderowania, pickingu lub obliczeń geometrycznych.
---

# Architektura i implementacja C++ / 3D (`stereometria-arch-cpp`)

Ten skill definiuje założenia techniczne, architekturę modułową oraz konwencje kodowania w projekcie **Interaktywna aplikacja wspomagająca naukę stereometrii z wykorzystaniem modeli 3D** (Projekt Grupowy ID-716 / RPI 2026/2027).

## 1. Stos technologiczny i ograniczenia

- **Język i standard**: C++17 / C++20 (kompilator MSVC w Visual Studio + wieloplatformowy `CMakeLists.txt`).
- **Okno i kontekst 3D**: `SFML` lub `GLFW` + `OpenGL` (GLSL) + opcjonalnie `GLM` (matematyka wektorowa/macierzowa) i `Dear ImGui` (boczny panel właściwości / UI edukacyjne).
- **Format danych**: `JSON` (np. biblioteka `nlohmann/json` do wczytywania bazy zadań i scenariuszy wizualizacji).
- **Ograniczenia sprzętowe**: Płynne renderowanie 3D (60 FPS) z obsługą przezroczystości (*alpha blending*) na typowym sprzęcie szkolnym.

## 2. Podział na 3 główne moduły (zgodnie z DPP i RPI)

Architektura systemu dzieli się na trzy ściśle współpracujące warstwy odpowiadające podziałowi prac w zespole:

1. **Moduł Graficzny 3D i Kamera (`src/renderer/`, `src/camera/`)** *(odpowiedzialność główna: Dawid Deja)*
   - Potok renderowania OpenGL + shadery GLSL.
   - Kamera orbitalna: płynny obrót w 3 osiach, przybliżanie/oddalanie (*zoom*), przesuwanie (*pan*).
   - Renderowanie siatek brył (ściany z *alpha blending*, krawędzie widoczne/ukryte, wyróżnione przekroje, odcinki i łuki kątów).
2. **Silnik Geometryczno-Matematyczny i Picking (`src/math/`, `src/solids/`, `src/interaction/`)** *(odpowiedzialność główna: Paweł Hiszpański)*
   - Polimorficzna hierarchia klas brył bazująca na abstrakcyjnej klasie `Solid3D`.
   - Dynamiczne przeliczanie parametrów przy zmianie wymiarów w czasie rzeczywistym: pola powierzchni ($P_p, P_b, P_c$), objętość ($V$), przekątne, wysokości, kąty (między krawędzią a płaszczyzną, między ścianami).
   - Selekcja elementów w przestrzeni 3D (*raycasting / picking*): wierzchołki, krawędzie, ściany, przekątne, kąty.
3. **Moduł Edukacyjny, Baza Zadań JSON i Walidacja (`src/tasks/`, `data/tasks/`, `tests/`)** *(odpowiedzialność główna: Maciej Raniszewski)*
   - Wczytywanie i walidacja zadań z plików JSON.
   - Silnik scenariuszy „krok po kroku" — nakładanie na model 3D pomocniczych elementów wizualnych (np. wyróżnienie trójkąta prostokątnego z wysokością bryły i promieniem podstawy, rysowanie płaszczyzny przekroju).
   - Tryb rozwiązywania zadań: weryfikacja pośrednich i końcowych odpowiedzi ucznia (z tolerancją zmiennoprzecinkową $\epsilon$) oraz interakcji na modelu.

## 3. Polimorficzny model brył (`Solid3D`)

Wszystkie bryły dziedziczą po wspólnej klasie bazowej (Etap B w DPP):

- `Solid3D` (klasa abstrakcyjna):
  - Przechowuje nazwane parametry wymiarowe (np. `a`, `b`, `h`, `r`), listę nazwanych wierzchołków 3D, krawędzi, ścian oraz odcinków specjalnych (wysokości, przekątne).
  - Udostępnia interfejs:
    - `updateGeometry()` — przelicza współrzędne wierzchołków, siatkę trójkątów oraz wartości matematyczne po zmianie wymiarów.
    - `getVolume()`, `getTotalSurfaceArea()`, `getLateralSurfaceArea()`, `getBaseArea()`.
    - `getNamedElements()` — zwraca słownik elementów bryły (wierzchołki, odcinki, ściany, kąty), do których może odwoływać się plik JSON z zadaniem oraz moduł pickingu.
- Klasy pochodne (zgodne z podstawą programową):
  - **Graniastosłupy (`Prism`)**: Sześcian (`Cube`), Prostopadłościan (`Cuboid`), Graniastosłup prawidłowy trójkątny, czworokątny, sześciokątny (`RegularPrism`).
  - **Ostrosłupy (`Pyramid`)**: Ostrosłup prawidłowy trójkątny (w tym czworościan foremny), czworokątny, sześciokątny (`RegularPyramid`).
  - **Bryły obrotowe (`SolidOfRevolution`)**: Walec (`Cylinder`), Stożek (`Cone`), Kula (`Sphere`).

## 4. Rekomendowana struktura katalogów repozytorium

```text
├── CMakeLists.txt
├── docs/                  # Dokumentacja PG (DPP, DTP, Plakat) oraz RPI
├── data/
│   └── tasks/             # Baza zadań stereometrycznych w formacie JSON
├── include/               # Pliki nagłówkowe (.hpp)
│   ├── solids/            # Hierarchia klas Solid3D
│   ├── math/              # Obliczenia geometryczne i walidacja
│   ├── renderer/          # OpenGL, shadery, kamera
│   ├── interaction/       # Raycasting / picking elementów
│   └── tasks/             # Parser JSON, silnik scenariuszy, sprawdzanie odpowiedzi
├── src/                   # Implementacja (.cpp)
├── assets/
│   └── shaders/           # Shadery GLSL (.vert, .frag)
└── tests/                 # Testy jednostkowe i integracyjne (np. Catch2 / GoogleTest)
```

## 5. Zasady pracy nad kodem

1. **Separacja logiki od renderowania**: Klasy w `solids/`, `math/` oraz `tasks/` nie powinny bezpośrednio wywoływać funkcji OpenGL — dzięki temu można je testować jednostkowo w izolacji (bez otwierania okna graficznego).
2. **Walidacja danych wejściowych (Etap H)**: Każda zmiana wymiaru bryły lub wczytanie zadania musi odrzucać wartości niedodatnie ($\le 0$), `NaN`/`Inf` oraz geometrycznie sprzeczne konfiguracje.
3. **Spójność identyfikatorów elementów**: Nazwy wierzchołków i odcinków w klasach `Solid3D` (np. `"diagonal_main"`, `"height_main"`, `"angle_diag_base"`) muszą być ustandaryzowane, aby moduł zadań JSON i moduł pickingu operowały na tych samych identyfikatorach.
