# Implementierungsplan: `TestCheck.cpp` unter Windows kompilierbar machen

**Status:** freigegeben und umgesetzt, noch nicht committet

## Ausgangslage

Fehlgeschlagener Job: [`build-windows` in „Building Command“](https://github.com/Protestator-Research/CPP-SysMLv2/actions/runs/42192133346/job/127806463864), Commit `3d04c692`, Schritt `build sysmlv2lib`, Exit-Code 1.

## Ursache

`build.yml` baut mit `with_check=True` und damit auch das Ziel `sysmlv2check-test`. Dessen Quelldatei `check/tests/TestCheck.cpp` verwendet POSIX-Code ohne Plattform-Abfrage:

| Zeile | Stelle | Problem unter MSVC |
|---|---|---|
| 14 | `#include <sys/wait.h>` | Header existiert nicht |
| 469, 474 | `popen`, `pclose` | Unter MSVC heißen sie `_popen` und `_pclose` |
| 648, 650 | `WEXITSTATUS` | Makro existiert nicht |
| 468, 646, 650 | `/dev/null` und ungeschützter Programmpfad im Befehl | Scheitert erst zur Laufzeit |
| `SysmlPruefeCli`-Test | `std::tmpnam` als Pfad der Eingabedatei | Unsicher und auf Windows unzuverlässig |

**Sicherheit der Diagnose:** Der Job-Log bestätigt die Ursache (Log-Zeile 158554 im Schritt `build sysmlv2lib`):

```
check\tests\TestCheck.cpp(14,10): error C1083: Cannot open include file: 'sys/wait.h': No such file or directory
```

Das ist der einzige Compilerfehler im Log. Der Branch `AddingProgrammingLanguagesSupport` (`31c2bb98`) enthält denselben `main`-Stand, hat diese Stelle angepasst und kommt unter Windows bis zum Schritt `test`.

## Änderungen

Betroffen ist nur `check/tests/TestCheck.cpp`. Der Code wird wörtlich aus `31c2bb98` übernommen, damit ein späterer Merge des Branchs möglichst konfliktfrei bleibt.

1. **Includes:** `<sys/wait.h>` kommt hinter `#ifdef _WIN32`. Unter Windows stehen dort stattdessen die Makros `popen`, `pclose` und `WEXITSTATUS`. Dazu kommt `<filesystem>`.
2. **Hilfsfunktionen im anonymen Namespace:** `NULL_DEVICE` (`NUL` oder `/dev/null`) und `cliCommand()` für das korrekte Quoten unter `cmd.exe`.
3. **Test `StdoutHoldsOnlyResponseLinesWithTheirIds`:** Die Eingabedatei entsteht über `std::filesystem::temp_directory_path()` statt `std::tmpnam`, und der Befehl läuft über `cliCommand()`.
4. **Test `UnusableArgumentsEndWithExitCodeTwo`:** Beide Befehle laufen über `cliCommand()` und `NULL_DEVICE`.

## Nicht Teil dieses Plans

- **Python-Arbeit aus dem Branch:** `runCli()`, `nameOf()`, `<set>`, `<sstream>` und die `SysmlModell`-Tests hängen an Funktionen, die es auf `main` noch nicht gibt (zum Beispiel `--modell`).
- **Alle anderen Dateien:** Workflows, `conanfile.py` und die CMake-Dateien bleiben unverändert.

## Risiko

- **Compilerfehler:** Alle anderen 20 Ziele wurden laut Log vor dem Abbruch fertig gebaut, nur `sysmlv2check-test` fehlt. MSVC bricht bei `<sys/wait.h>` sofort ab, der Rest von `TestCheck.cpp` ist also noch ungeprüft. Der Branch kompiliert diese Stellen aber bereits unter Windows.
- **Der Job wird vermutlich noch nicht grün:** Der Branch scheitert unter Windows im Schritt `test` mit Exit-Code 8. Das deutet auf fehlschlagende Tests hin, die dann vermutlich auch auf `main` auftreten. Dafür brauche ich den Log.

## Umsetzung und Prüfung

1. Ein Sonnet-Agent setzt die Änderungen um.
2. Ein Opus-Agent prüft den Diff. Zusätzlich wird geprüft:
   - Der Diff enthält nur die vier genannten Punkte und stimmt dort wörtlich mit `31c2bb98` überein.
   - `sysmlv2check-test` kompiliert unter Linux und läuft erfolgreich. Falls der lokale Build das nicht hergibt, steht das ausdrücklich im Bericht.
3. Es wird nichts committet und nichts gepusht.

**Grenze der Prüfung:** MSVC lässt sich hier unter Linux nicht ausführen. Lokal lässt sich nur zeigen, dass Linux nicht kaputtgeht; ob der Windows-Build durchläuft, zeigt erst ein CI-Lauf nach deinem Push.
