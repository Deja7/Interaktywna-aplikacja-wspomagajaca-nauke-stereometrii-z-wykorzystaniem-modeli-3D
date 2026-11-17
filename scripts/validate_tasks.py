#!/usr/bin/env python3
"""
Skrypt walidujący pliki zadań JSON w katalogu data/tasks/
oraz symulujący przejście przez kroki zadania.
"""
import glob
import json
import math
import sys

SUPPORTED_SOLIDS = {
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
    "sphere",
}


def validate_task_file(filepath: str) -> list[str]:
    errors = []
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            task = json.load(f)
    except Exception as e:
        return [f"Błąd parsowania JSON: {e}"]

    for req_key in ("id", "title", "problem_statement", "solid", "steps"):
        if req_key not in task:
            errors.append(f"Brak wymaganego klucza '{req_key}'")

    solid = task.get("solid", {})
    solid_type = solid.get("type", "")
    if solid_type not in SUPPORTED_SOLIDS:
        errors.append(f"Nieobsługiwany typ bryły: '{solid_type}'")

    dims = solid.get("initial_dimensions", {})
    if not dims:
        errors.append("Brak wymiarów początkowych (initial_dimensions)")
    for k, v in dims.items():
        if not isinstance(v, (int, float)) or v <= 0:
            errors.append(f"Wymiar '{k}' musi być dodatni (otrzymano: {v})")

    opacity = solid.get("default_opacity", 0.35)
    if not (0.0 <= opacity <= 1.0):
        errors.append(f"Przezroczystość (default_opacity) poza zakresem [0, 1]: {opacity}")

    steps = task.get("steps", [])
    if not steps:
        errors.append("Lista kroków (steps) jest pusta")

    for step in steps:
        snum = step.get("step_number", "?")
        tol = step.get("tolerance", 0)
        if tol <= 0:
            errors.append(f"Krok {snum}: tolerancja musi być > 0")

    return errors


def main() -> int:
    files = sorted(glob.glob("data/tasks/*.json"))
    if not files:
        print("Brak plików JSON w data/tasks/")
        return 1

    print("=" * 72)
    print(f"WALIDACJA BAZY ZADAŃ STEREOMETRYCZNYCH ({len(files)} plików)")
    print("=" * 72)

    all_ok = True
    for path in files:
        errs = validate_task_file(path)
        with open(path, "r", encoding="utf-8") as f:
            task = json.load(f)

        status = "POPRAWNY" if not errs else "BŁĘDY"
        print(f"\n[{status}] Plik: {path}")
        print(f"  ID:    {task.get('id')}")
        print(f"  Tytuł: {task.get('title')}")
        print(f"  Bryła: {task.get('solid', {}).get('type')} | Wymiary: {task.get('solid', {}).get('initial_dimensions')}")
        print(f"  Treść: {task.get('problem_statement')}")
        if errs:
            all_ok = False
            for e in errs:
                print(f"  [!] {e}")
        else:
            for step in task.get("steps", []):
                vis = step.get("visualization", {})
                print(
                    f"    -> Krok {step['step_number']}: szukane '{step['target_parameter']}' = {step['expected_value']} "
                    f"(±{step['tolerance']}) | Wzór: {step.get('formula_hint')}"
                )
                print(
                    f"       Podświetlenie 3D: odcinki={vis.get('highlight_segments')}, "
                    f"kąty={vis.get('highlight_angles')}, trójkąt={vis.get('show_helper_triangle')}"
                )

    print("\n" + "=" * 72)
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
