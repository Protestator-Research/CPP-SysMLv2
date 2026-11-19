# Implementierungsplan: Windows-CI durchgängig mit C++20

**Status:** freigegeben und umgesetzt, noch nicht committet

## Ausgangslage

Fehlgeschlagener Job: [`build-windows` in „Main Branch Artifactory Upload“](https://github.com/Protestator-Research/CPP-SysMLv2/actions/runs/42048115391/job/127316535930), Commit `d029b9a7`, Schritt `prepare dependencies`, Exit-Code 6.

## Ursache

- Conan erkennt MSVC mit `compiler.cppstd=14`.
- `antlr4-cppruntime/4.13.2` verlangt mindestens C++17 und bricht sonst über `check_min_cppstd` ab.
- Exit-Code 6 ist bei Conan `ERROR_INVALID_CONFIGURATION`, das passt zu diesem Abbruch.
- Die Commits `c14f387a` und `65dceb8a` haben den `sed`-Befehl im Profil durch Kommandozeilen-Parameter ersetzt. In `mainbuild.yml` und `tagbuild.yml` wurden dabei aber nur die `conan create`-Aufrufe umgestellt, nicht die beiden `conan install`-Aufrufe.
- `CMakeLists.txt` setzt `CMAKE_CXX_STANDARD 20` bereits. Das Projekt selbst braucht also keine Änderung, nur der Conan-Aufruf.

Der genaue Log-Text ist ohne GitHub-Anmeldung nicht einsehbar. Die Ursache ist deshalb aus Exit-Code, Rezept und Workflow-Dateien abgeleitet.

## Änderungen

Der von dir als fehleranfällig entfernte `sed`-Befehl kommt nicht zurück. Überall werden dieselben Parameter wie in `build.yml` verwendet:

```
-pr:b=default -pr:h=default -s:h compiler.cppstd=20
```

Betroffen ist jeweils nur der Job `build-windows`.

| Datei | Zeile | Schritt | Änderung |
|---|---|---|---|
| `.github/workflows/mainbuild.yml` | 84 | `prepare dependencies` | Parameter an `conan install .. --build missing` anhängen |
| `.github/workflows/mainbuild.yml` | 95 | `deploy and package binaries` | Parameter an `conan install --requires=...` anhängen |
| `.github/workflows/tagbuild.yml` | 84 | `prepare dependencies` | Parameter an `conan install .. --build missing` anhängen |
| `.github/workflows/tagbuild.yml` | 95 | `deploy and package binaries` | Parameter an `conan install --requires=...` anhängen |
| alle drei Workflows (`build.yml`: 72–73, `mainbuild.yml` und `tagbuild.yml`: 76–77) | | `prepare runner` | Auskommentierte `sed`-Zeile entfernen und den Kommentar an das neue Vorgehen anpassen (auf Englisch) |

Zeile 95 ist nötig, obwohl sie im aktuellen Lauf noch gar nicht erreicht wurde: Ohne die Parameter würde der Deploy-Schritt mit C++14 auflösen und am selben antlr4-Check scheitern. Der Fehler würde also nur einen Schritt später wieder auftreten.

## Nicht Teil dieses Plans

- **Linux- und WASM-Jobs:** Sie laufen erfolgreich und bleiben unverändert.
- **Andere Windows-Fehler:** Es gibt zwei weitere Fehler mit anderen Exit-Codes, deren Ursache noch offen ist. C++14 lässt sich hier als Ursache ausschließen, weil beide Läufe die C++20-Parameter schon verwenden:
  - „Building Command“ auf `main` (`d029b9a7`): `build sysmlv2lib` mit Exit-Code 1
  - „Building Command“ auf `AddingProgrammingLanguagesSupport` (`31c2bb98`): `test` mit Exit-Code 8

## Risiko

Da `build.yml` mit `main` denselben Code baut und dort `build sysmlv2lib` fehlschlägt, wird `mainbuild.yml` nach diesem Fix voraussichtlich an `conan create` scheitern. Der Job kommt dann weiter als bisher, wird aber vermutlich noch nicht grün. Für diesen Fehler brauche ich den Log-Text.

## Umsetzung und Prüfung

1. Ein Sonnet-Agent setzt die Tabelle um.
2. Ein Opus-Agent prüft den Diff. Zusätzlich wird geprüft:
   - Alle Workflows sind gültiges YAML.
   - Jeder `conan install`, `conan create` und `conan build` in den `build-windows`-Jobs trägt die Parameter.
   - Die Linux- und WASM-Jobs sind unverändert.
3. Es wird nichts committet und nichts gepusht.

**Grenze der Prüfung:** Lokal lässt sich der MSVC-Build unter Linux nicht ausführen. Ob der Fix wirkt, zeigt erst ein CI-Lauf nach deinem Push.
