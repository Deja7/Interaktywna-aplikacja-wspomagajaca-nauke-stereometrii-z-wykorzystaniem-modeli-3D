---
name: pg-dokumentacja-projektowa
description: >-
  Prowadzenie i aktualizacja dokumentacji projektowej Politechniki Gdańskiej (WETI) dla
  przedmiotów Projekt Grupowy (DPP, DTP, Plakat) oraz Realizacja Projektu Informatycznego (RPI).
  Używaj tego skilla podczas analizowania dokumentów w docs/, przygotowywania notatek ze
  spotkań zespołu/z opiekunem, uzupełniania brakujących sekcji DPP/DTP oraz generowania
  raportów LaTeX na przedmiot RPI.
---

# Dokumentacja Projektowa PG WETI (`pg-dokumentacja-projektowa`)

Ten skill zawiera kontekst organizacyjny zespołu oraz wytyczne dotyczące dokumentacji znajdującej się w katalogu `docs/` dla dwóch powiązanych przedmiotów realizowanych na tym samym repozytorium.

## 1. Metryczka projektu i zespołu

- **Tytuł projektu**: Interaktywna aplikacja wspomagająca naukę stereometrii z wykorzystaniem modeli 3D
- **Kod grupy (SPG)**: `ID-716`
- **Opiekun projektu**: mgr inż. Sebastian Górski (`sebgorsk@pg.edu.pl`)
- **Koordynator wydziałowy PG**: dr inż. Sławomir Gajewski (`slawomir.gajewski@eti.pg.edu.pl`)
- **Katedra**:
  - W szablonie DPP wpisano: *Katedra Systemów i Sieci Radiokomunikacyjnych* (do weryfikacji z opiekunem, w RPI: *Katedra Inżynierii Oprogramowania*).
- **Skład zespołu**:
  1. **Dawid Deja** (`203180`, `s203180@student.pg.edu.pl`) — **Kierownik projektu**; grafika 3D (OpenGL/GLSL/SFML), kamera, modele brył, repozytorium GitHub.
  2. **Paweł Hiszpański** (`203455`, `s203455@student.pg.edu.pl`) — Architektura C++, silnik dynamicznych obliczeń matematycznych, raycasting/picking elementów brył.
  3. **Maciej Raniszewski** (`203773`, `s203773@student.pg.edu.pl`) — Struktury danych (JSON), baza zadań zgodna z podstawą programową, scenariusze wizualizacji, tryb rozwiązywania zadań, walidacja i testy.
  4. **Dawid Jezierski** (`203507`, `s203507@student.pg.edu.pl`) — Członek zespołu 5-osobowego (Projekt Grupowy ID-716).
  5. **Kacper Lubecki** (`203614`, `s203614@student.pg.edu.pl`) — Członek zespołu 5-osobowego (Projekt Grupowy ID-716).

> **Uwaga dot. dwóch przedmiotów**:
> - **Projekt Grupowy (ID-716)** jest realizowany w składzie **5-osobowym** (dokumenty `docs/DPP_wer. 1.00.docx`, `docs/DTP_wer. 1.00.docx`, `docs/Plakat.wer 1.00.docx`).
> - **RPI (Realizacja Projektu Informatycznego 2026/2027)** jest raportowany w składzie **3-osobowym** (Dawid Deja, Paweł Hiszpański, Maciej Raniszewski — dokumenty w `docs/RPI/`).

## 2. Stan i wymagania dla poszczególnych dokumentów w `docs/`

### A. `docs/DPP_wer. 1.00.docx` (Dokumentacja Procesu Projektowania)
Stan obecny (wersja z 05.11.2026, autor zmian: Paweł Hiszpański):
- **Wypełnione**:
  - Tabela 3.1 (skład 5-osobowy z mailami, ale brak wpisanych ról dla poz. 2–5).
  - Tabela 3.2 (opiekun i koordynator wydziałowy, brak Klienta i Koordynatora katedralnego).
  - Sekcja 5.1 (Opis etapów wytwarzania: Semestr I = Etapy A–D, Semestr II = Etapy E–H).
- **Do uzupełnienia w Semestrze I**:
  - **Metryczka na str. 1**: Usunięcie znaczników `{...}`, wpisanie osoby odpowiedzialnej za dokument, pierwszego wiersza historii zmian.
  - **Pkt 1.2 Odbiorcy i 1.3 Terminologia**: Usunięcie komentarzy szablonowych `{...}` i wpisanie właściwych definicji.
  - **Pkt 2 Cel i założenia projektu (2.1, 2.2)**: Przeniesienie i rozszerzenie opisu problemu, celu i założeń (część jest już gotowa w raporcie RPI pkt 1).
  - **Pkt 3.1 Tabela 3.1**: Uzupełnienie kolumny *Rola w projekcie* dla wszystkich 5 członków zespołu.
  - **Pkt 3.3 Infrastruktura komunikacyjna**: Opis spotkań z opiekunem, klientem oraz wewnątrz zespołu (Discord, Messenger, GitHub, okienka między zajęciami — można zaadaptować z RPI pkt 4).
  - **Pkt 3.4 Zarządzanie jakością**: Opis code review (Pull Requesty na GitHubie), testów jednostkowych/integracyjnych oraz weryfikacji dokumentacji przed wgraniem do SPG.
  - **Pkt 4 Analiza ryzyka (Tabela 4.1)**: Zastąpienie przykładowego wiersza z szablonu realnymi ryzykami projektu (np. problemy z wydajnością/kompatybilnością OpenGL, opóźnienia w integracji silnika 3D z bazą JSON, choroba/nieobecność członka zespołu, zbyt szeroki zakres zadań matematycznych).
  - **Pkt 5 Harmonogram prac (tabela)**: Dodanie tabeli z datami początkowymi, końcowymi i wykonawcami dla Etapów A–D (Semestr I) oraz E–H (Semestr II).
  - **Pkt 6 Planowany podział zadań i ról (6.1)**: Rozpisanie zadań i przypisanie ich do całej 5-osobowej grupy.
  - **Pkt 7 Wymagania dla produktu i kryteria akceptacji (7.1–7.3)**: Ogólny opis produktu, wymagania minimalne i warunki odbioru.
  - **Pkt 9 Raport aktywności zespołu (9.1, 9.2, ...)**: Bieżące dopisywanie krótkich notatek po każdym spotkaniu zespołu i spotkaniu z opiekunem (data, uczestnicy, co zrobiono, wnioski i plan na kolejny tydzień).

### B. `docs/DTP_wer. 1.00.docx` (Dokumentacja Techniczna Projektu)
Stan obecny: Czysty szablon wzorcowy 1/2025 (niewypełniona nawet metryczka).
- Wymaga uzupełnienia metryczki (ID-716, kierownik, opiekun, daty) oraz sukcesywnego opisywania architektury (diagram klas `Solid3D`, specyfikacja formatu JSON, opis potoku renderowania i algorytmu raycastingu) zgodnie z zaleceniami opiekuna.

### C. `docs/RPI/` (Raporty na przedmiot Realizacja Projektu Informatycznego)
- Tworzone w systemie **LaTeX (Overleaf)**.
- Konwencja nazewnictwa zadeklarowana w raporcie 1: `RPI_2026_[TytulRaportu]_v[X.Y].pdf` (obecny plik `docs/RPI/RPI (1).pdf` warto docelowo nazwać zgodnie z tą konwencją).
- Każdy raport RPI zawiera sekcję **Wykorzystanie AI i wnioski** (opis użycia AI, przykładowe prompty i outputy, krytyczna refleksja).

## 3. Wzorzec notatki ze spotkania do Pkt 9 DPP

Po każdym spotkaniu zespołu lub konsultacjach z opiekunem przygotuj zwięzłą notatkę wg poniższego formatu:

```markdown
### 9.X Spotkanie z opiekunem / Spotkanie projektowe zespołu dnia DD.MM.2026 r.
- **Uczestnicy**: Dawid Deja, Paweł Hiszpański, Maciej Raniszewski, Dawid Jezierski, Kacper Lubecki (+ mgr inż. Sebastian Górski)
- **Podsumowanie wykonanych prac**: [2–3 zdania o tym, co powstało od poprzedniego spotkania]
- **Ustalenia i wnioski**: [kluczowe decyzje architektoniczne, organizacyjne lub wymagania opiekuna]
- **Plan prac na kolejny okres**: [konkretne zadania przypisane do osób na najbliższe 1–2 tygodnie]
```
