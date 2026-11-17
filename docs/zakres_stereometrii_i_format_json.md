# Zakres materiału ze stereometrii (MVP) oraz specyfikacja formatu JSON zadań

Dokument przygotowany w ramach **Etapu A** (*Konfiguracja środowiska, wybór technologii i analiza wymagań*) jako wspólny kontrakt między:
- **Modułem Zadań i Scenariuszy JSON** (Maciej Raniszewski),
- **Silnikiem Geometryczno-Matematycznym i Pickingiem** (Paweł Hiszpański),
- **Modułem Renderowania 3D i Kamery** (Dawid Deja).

---

## 1. Zakres brył zgodnie z podstawą programową (Szkoła podstawowa kl. VII–VIII oraz Szkoła średnia / Matura)

| Kategoria | Identyfikator typu (`solid.type`) | Nazwa bryły | Wymiary wejściowe (`initial_dimensions`) | Obliczane parametry wyjściowe |
| :--- | :--- | :--- | :--- | :--- |
| **Graniastosłupy** | `cube` | Sześcian | `a` (krawędź) | $P_p, P_b, P_c, V, d_p$ (przekątna ściany), $D$ (przekątna główna) |
| | `cuboid` | Prostopadłościan | `a`, `b` (podstawa), `H` (wysokość) | $P_p, P_b, P_c, V, d_p, D, \alpha$ (kąt nachylenia $D$ do podstawy) |
| | `regular_tri_prism` | Graniastosłup prawidłowy trójkątny | `a` (krawędź podstawy), `H` (wysokość) | $P_p, P_b, P_c, V, h_p$ (wysokość podstawy), $d_b$ (przekątna ściany bocznej) |
| | `regular_quad_prism` | Graniastosłup prawidłowy czworokątny | `a` (krawędź podstawy), `H` (wysokość) | $P_p, P_b, P_c, V, d_p, D, \alpha$ |
| | `regular_hex_prism` | Graniastosłup prawidłowy sześciokątny | `a` (krawędź podstawy), `H` (wysokość) | $P_p, P_b, P_c, V, d_{kr}, d_{dl}$ (przekątne podstawy i bryły) |
| **Ostrosłupy** | `regular_tet_pyramid` | Czworościan foremny | `a` (krawędź) | $P_p, P_c, V, h_p, H$ |
| | `regular_tri_pyramid` | Ostrosłup prawidłowy trójkątny | `a` (podstawa), `H` (wysokość bryły) | $P_p, P_b, P_c, V, h_p, h_b$ (wys. ściany bocznej), $k$ (krawędź boczna), $\alpha, \beta$ |
| | `regular_quad_pyramid` | Ostrosłup prawidłowy czworokątny | `a` (podstawa), `H` (wysokość bryły) | $P_p, P_b, P_c, V, d_p, h_b, k, \alpha$ (krawędź-podstawa), $\beta$ (ściana-podstawa) |
| | `regular_hex_pyramid` | Ostrosłup prawidłowy sześciokątny | `a` (podstawa), `H` (wysokość bryły) | $P_p, P_b, P_c, V, h_b, k, \alpha, \beta$ |
| **Bryły obrotowe** | `cylinder` | Walec | `r` (promień), `H` (wysokość) | $P_p, P_b, P_c, V, d_{os}$ (przekątna przekroju osiowego) |
| | `cone` | Stożek | `r` (promień), `H` (wysokość) | $P_p, P_b, P_c, V, l$ (tworząca), $\alpha$ (kąt nachylenia $l$), $\varphi$ (kąt rozwarcia) |
| | `sphere` | Kula | `r` (promień) | $P_c, V$ |

---

## 2. Standardowe identyfikatory elementów bryły (kontrakt JSON <-> Silnik 3D)

Aby plik JSON z zadaniem mógł nakazać silnikowi 3D podświetlenie konkretnego odcinka, ściany lub kąta w danym kroku rozwiązania, przyjmujemy spójne nazewnictwo:

### Wierzchołki (`vertices`)
- Podstawa dolna: `"A"`, `"B"`, `"C"`, `"D"` (oraz `"E"`, `"F"` dla sześciokąta).
- Podstawa górna (w graniastosłupach): `"A'"`, `"B'"`, `"C'"`, `"D'"`.
- Wierzchołek główny ostrosłupa / stożka: `"S"`.
- Środek podstawy (spodek wysokości $H$): `"O"`.
- Środek krawędzi podstawy (np. $BC$, potrzebny do kąta ściany bocznej $\beta$): `"M"`.

### Odcinki nazwane (`highlight_segments`)
- `"base_edge_AB"` – krawędź podstawy $a$.
- `"base_diagonal_AC"` – przekątna podstawy $d$.
- `"half_diagonal_AO"` – połowa przekątnej podstawy ($d/2$, promień okręgu opisanego $R$).
- `"inradius_OM"` – promień okręgu wpisanego w podstawę $r$ (od środka $O$ do środka boku $M$).
- `"height_SO"` / `"height_main"` – wysokość główna bryły $H$.
- `"lateral_edge_AS"` / `"lateral_edge_AA'"` – krawędź boczna.
- `"slant_height_SM"` – wysokość ściany bocznej $h_b$ (lub tworząca stożka $l$).
- `"main_diagonal_AC'"` – przekątna główna graniastosłupa $D$.

### Kąty nazwane (`highlight_angles`)
- `"angle_lateral_edge_base"` – kąt $\alpha$ między krawędzią boczną a płaszczyzną podstawy ($\sphericalangle OAS$).
- `"angle_lateral_face_base"` – kąt $\beta$ nachylenia ściany bocznej do płaszczyzny podstawy ($\sphericalangle OMS$).
- `"angle_main_diagonal_base"` – kąt nachylenia przekątnej głównej graniastosłupa do płaszczyzny podstawy ($\sphericalangle C'AC$).
- `"angle_cone_apex"` – kąt rozwarcia stożka $\varphi$.

### Trójkąty pomocnicze wewnątrz bryły (`show_helper_triangle`)
Tablica 3 identyfikatorów wierzchołków, pomiędzy którymi renderer rysuje półprzezroczysty, wyróżniony trójkąt prostokątny wraz z oznaczeniem kąta prostego, np.:
- `["A", "O", "S"]` – trójkąt prostokątny: połowa przekątnej podstawy + wysokość ostrosłupa + krawędź boczna.
- `["M", "O", "S"]` – trójkąt prostokątny: promień okręgu wpisanego $r$ + wysokość ostrosłupa $H$ + wysokość ściany bocznej $h_b$.
- `["A", "C", "C'"]` – trójkąt prostokątny: przekątna podstawy + wysokość graniastosłupa + przekątna główna.
