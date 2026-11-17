# Interaktywna aplikacja wspomagająca naukę stereometrii z wykorzystaniem modeli 3D

**Projekt Grupowy (`ID-716`) / Realizacja Projektu Informatycznego (`RPI 2026/2027`)**  
**Wydział ETI, Politechnika Gdańska** | **Opiekun:** mgr inż. Sebastian Górski

---

## 1. Co gdzie jest w repozytorium (Mapa plików)

### Katalog `docs/` – Dokumentacja projektowa i specyfikacja
- `docs/DPP_wer. 1.00.docx` – **Dokumentacja Procesu Projektowania** (uzupełniona o cel i założenia, role 5-osobowego zespołu, komunikację, analizę ryzyka, harmonogram Etapów A–H, podział zadań oraz wymagania minimalne MVP).
- `docs/DTP_wer. 1.00.docx` – **Dokumentacja Techniczna Projektu** (szablon wzorcowy PG do uzupełniania w trakcie implementacji).
- `docs/Plakat.wer 1.00.docx` – **Szablon plakatu projektowego** (wstępnie wpisany skład i temat).
- `docs/RPI/RPI (1).pdf` – **Raport 1 na przedmiot RPI** (*Organizacja i infrastruktura projektu*).
- `docs/zakres_stereometrii_i_format_json.md` – **Specyfikacja Etapu A**: tabela obsługiwanych brył z podstawy programowej, ich parametrów oraz wspólny słownik identyfikatorów elementów 3D (wierzchołków, odcinków, kątów i trójkątów pomocniczych), łączący moduł JSON z silnikiem 3D i modułem Pickingu.

### Katalog `data/tasks/` – Baza zadań stereometrycznych (JSON)
- `data/tasks/ostrostup_czworokatny_kat_01.json` – przykładowe zadanie maturalne (ostrosłup prawidłowy czworokątny, kąt nachylenia krawędzi bocznej do podstawy $\alpha = 45^\circ$, trójkąt prostokątny $AOS$).
- `data/tasks/graniastoslup_przekatna_01.json` – przykładowe zadanie z graniastosłupem prawidłowym czworokątnym (przekątna główna $D$, trójkąt prostokątny $ACC'$).

### Katalogi `include/` oraz `src/` – Szkielet kodu C++17 (`CMakeLists.txt`)
- `CMakeLists.txt` – plik budowania CMake (biblioteka logiki `stereometria_core` + aplikacja `Stereometria3D`).
- `include/solids/Solid3D.hpp` – abstrakcyjna klasa bazowa dla wszystkich brył 3D (wspólny interfejs dla wymiarów, pól powierzchni, objętości oraz nazwanych wierzchołków, odcinków i kątów).
- `include/tasks/Task.hpp` – struktury C++ odpowiadające zadaniu wczytanemu z JSON-a (`Task`, `TaskStep`, `StepVisualization`).
- `include/tasks/TaskValidator.hpp` i `src/tasks/TaskValidator.cpp` – walidator spójności zadań JSON (dodatnie wymiary, zakres przezroczystości, wspierane bryły) oraz weryfikator odpowiedzi liczbowych ucznia z tolerancją $\epsilon$.
- `src/main.cpp` – punkt wejścia aplikacji testujący walidację przykładowego zadania.

### Katalog `scripts/` – Narzędzia pomocnicze i prototyp wizualny
- `scripts/preview_tasks_3d.html` – **interaktywny prototyp 3D w przeglądarce** (otwierany dwuklikiem, bez instalacji). Pozwala obracać bryłę myszką, zmieniać przezroczystość ścian (*alpha blending*) i przełączać kroki zadania z JSON-a.
- `scripts/validate_tasks.py` – skrypt Pythona sprawdzający poprawność wszystkich plików `.json` w `data/tasks/` (`python scripts/validate_tasks.py`).

### Katalog `.agents/skills/` – Skille dla asystenta AI
- `stereometria-arch-cpp` – wytyczne architektury C++, OpenGL i klas `Solid3D`.
- `stereometria-zadania-json` – wytyczne tworzenia zadań JSON, podstawy programowej i testów.
- `pg-dokumentacja-projektowa` – wytyczne prowadzenia dokumentacji `DPP`, `DTP` i `RPI`.

---

## 2. Jak działa koncepcja zadań i zaznaczania elementów na bryle

Każda bryła w `Solid3D.hpp` posiada nazwane elementy (wierzchołki `A, B, C, S, O`, odcinki np. `height_SO`, `base_diagonal_AC` oraz kąty np. `angle_lateral_edge_base`). Dzięki temu ta sama struktura JSON obsługuje **dwa tryby pracy ucznia**:
1. **Tryb samodzielnego zaznaczania (eksploracja / Picking)**: uczeń sam klika myszką w boki, przekątne i kąty na modelu 3D, żeby zauważyć trójkąt prostokątny i wyznaczyć szukany wymiar, a lista elementów w JSON-ie (`visualization`) służy jako **klucz odpowiedzi** do sprawdzenia, czy uczeń zaznaczył właściwe elementy.
2. **Tryb podpowiedzi („krok po kroku”)**: jeśli uczeń potrzebuje pomocy, aplikacja podświetla na bryle 3D odcinki, kąt i trójkąt pomocniczy zapisane w sekcji `visualization` danego kroku.

---

## 3. Ściąga na pierwsze spotkanie (co po kolei pokazać i ustalić)

### Co pokazać (3–5 minut):
1. **Prototyp 3D w przeglądarce (`scripts/preview_tasks_3d.html`)** – obrócić ostrosłup, zmienić przezroczystość i przeklikać Kroki 1–3, pokazując jak JSON steruje elementami na bryle 3D (jako podpowiedź lub klucz do sprawdzania zaznaczeń ucznia).
2. **Specyfikację brył i formatu JSON (`docs/zakres_stereometrii_i_format_json.md` + `data/tasks/`)** – zaproponowany podział brył z podstawy programowej i ustandaryzowane nazwy wierzchołków/odcinków.
3. **Szkielet C++ (`include/solids/Solid3D.hpp`, `include/tasks/Task.hpp`)** – propozycja interfejsu łączącego grafikę 3D (Dawid), matematykę/picking (Paweł) oraz bazę zadań JSON (Maciej).
4. **Uzupełnione `docs/DPP_wer. 1.00.docx`** – wstępnie wypełnione punkty 1–8 wymagane na I semestr.

### Co ustalić z zespołem i opiekunem:
1. **Podział ról dla całej 5-osobowej grupy w DPP** – potwierdzenie zadań dla Dawida Jezierskiego i Kacpera Lubeckiego w Tabeli 3.1 i Pkt 6.1 DPP.
2. **Biblioteka okienkowa i UI** – ostateczna decyzja: `SFML` czy `GLFW + Dear ImGui` (pod kątem bocznego panelu wymiarów i treści zadań).
3. **Formalności w Tabeli 3.2 DPP** – dopytanie opiekuna o nazwisko *Koordynatora katedralnego*, wpis w polu *Klient* oraz właściwą nazwę katedry w nagłówku tabeli.
