# Implementierungsplan: Windows-Tests in `build.yml` grün bekommen

**Status:** freigegeben und umgesetzt, noch nicht committet

## Ausgangslage

Lauf: [`build-windows` in „Building Command“](https://github.com/Protestator-Research/CPP-SysMLv2/actions/runs/42202505286), Commit `142b1fcc`, Schritt `test`, Exit-Code 8. Der Build läuft durch, 8 von 10 Testprogrammen bestehen. Dieselben zwei Fehler treten auch im Branch `AddingProgrammingLanguagesSupport` auf (`31c2bb98`).

## Fehler 1: `sysmlv2check` stürzt ab

**Betroffener Test:** `SysmlPruefeContext.RunsOfPrefixOperatorsAreLimitedAndDoNotOverflowTheStack` schaltet die Limits ab und prüft 8000 Präfix-Operatoren in Folge.

**Ursache:** Das Parsen läuft auf einem eigenen Thread mit 512 MB Stack, der Rest aber auf dem Hauptthread. Der hat unter Windows standardmäßig 1 MB, unter Linux meist 8 MB. Unter Linux mit `ulimit -s` nachgestellt (Debug, GCC):

| Stack | Ergebnis |
|---|---|
| 8 MB, 4 MB | besteht |
| 2 MB, 1 MB, 512 KB | Segfault |

In einer temporären Kopie habe ich die Stellen nacheinander behoben. Mit 1 MB Stack läuft der Hauptthread nacheinander an drei Stellen über:

1. `Resolver::Impl::visit` in `Workspace::resolve` ([Resolver.cpp:316](filehandling/src/sysmlv2/resolution/Resolver.cpp:316))
2. `assignQualifiedNames` in [Checker.cpp](check/src/Checker.cpp)
3. Beim Prozessende: Der Abbau des statischen ANTLR-Caches (`SysMLv2ParserStaticData`) läuft rekursiv über die `PredictionContext`-Ketten. Der Test meldet zu diesem Zeitpunkt schon `[ PASSED ]`, der Prozess stürzt erst danach ab.

Die dritte Stelle liegt im generierten Parser-Code und in der ANTLR-Laufzeit und lässt sich nicht einfach durch Verschieben auf einen anderen Thread beheben.

## Fehler 2: `XmiExportTextLibrary.ReferencesIntoTheLibraryAreHrefs`

**Ursache (sehr wahrscheinlich):** [TestXmiExport.cpp:459](conformance-test/src/xmi/TestXmiExport.cpp:459) erwartet `href="../`. Der Test schreibt aber nach `fs::temp_directory_path()`, die Bibliothek liegt unter `D:\a\...`. Auf einem anderen Laufwerk schreibt [XmiWriter.cpp:655](filehandling/src/sysmlv2/xmi/XmiWriter.cpp:655) absichtlich `file:///D:/...`, und die übrigen Prüfungen des Tests bestehen damit.

Dass `TEMP` auf dem Runner auf `C:` zeigt, steht nicht im Log, sondern ist Erfahrungswissen. Liegt die Ursache woanders, schlägt der Test auch nach der Änderung weiter fehl; er verdeckt also nichts.

## Änderungen

### 1. `check/CMakeLists.txt`: größerer Stack für beide Programme

```cmake
if(MSVC)
    # The main thread only has 1 MB by default. With raised limits, resolving, the checks and the destruction of the ANTLR cache
    # at exit recurse once per nesting level of the text on that thread.
    target_link_options(sysmlv2check-cli PRIVATE /STACK:16777216)
endif()
```

Dasselbe gilt für `sysmlv2check-test` im Block `if(BUILD_TESTING)`. Der Kommentar steht nur einmal.

- **Warum beide Programme:** Auch das Kommandozeilenprogramm kann die Limits hochsetzen (`--max-tiefe`).
- **Warum 16 MB:** Unter Linux reichten 4 MB im Debug-Build. MSVC hat andere Stack-Rahmen, deshalb ist Reserve eingeplant. Der Speicher wird nur reserviert und erst bei Bedarf belegt.
- **Linux und WASM:** Sie bleiben durch `if(MSVC)` unverändert.

### 2. `conformance-test/src/xmi/TestXmiExport.cpp`, Zeile 459

Die Erwartung richtet sich nach derselben Regel wie der Writer (`lexically_relative` liefert leer, wenn kein relativer Pfad möglich ist):

```cpp
// A library on another drive than the temporary directory cannot be reached by a relative path: the writer uses a file URI then.
const bool relativeHref = !fs::absolute(SYSML_LIBRARY_XMI_DIR).lexically_normal().lexically_relative(fs::absolute(directory.path()).lexically_normal()).empty();
EXPECT_NE(xml.find(relativeHref ? "href=\"../" : "href=\"file:///"), std::string::npos);
```

Der Rest des Tests bleibt unverändert.

## Nicht Teil dieses Plans

- **Bibliotheks-Nutzer mit hochgesetzten Limits:** Die Linker-Option wirkt nur auf die beiden Programme. Eine fremde Anwendung mit 1 MB Hauptthread, die `maxNestingDepth` stark erhöht, kann unter Windows weiter abstürzen. Mit dem Standard (`maxNestingDepth = 64`) werden solche Texte vorher abgelehnt.
- **Der vollständige Code-Fix:** `Workspace::resolve` und `Checker::check` auf den großen Stack zu legen, ist in der Kopie erprobt und behebt die Stellen 1 und 2. Stelle 3 bleibt dabei bestehen und bräuchte einen Eingriff in den generierten Parser oder einen gezielten Abbau des Caches. Das wäre eine eigene Aufgabe.
- **`TEMP` im Workflow umbiegen:** Das würde Fehler 2 nur in der CI verdecken.
- **`.github/workflows`:** Die Workflows bleiben unverändert.

## Risiko

- **16 MB sind unter MSVC nicht gemessen.** Der Wert ist aus den Linux-Messungen abgeleitet. Reicht er nicht, stürzt derselbe Test weiter ab, und der Wert muss erhöht werden.
- **Der Test hat ein Zeitlimit von 10 s** (`maxParseMillis`) und erlaubt die Antwort `zeitueberschreitung`. Das ist ausdrücklich vorgesehen und kein Fehler.

## Umsetzung und Prüfung

1. Ein Sonnet-Agent setzt die beiden Änderungen um.
2. Ein Opus-Agent prüft den Diff. Zusätzlich wird in einem temporären Verzeichnis unter Linux geprüft:
   - `sysmlv2check-test` baut und besteht.
   - `conformance-xmi` baut, und `XmiExportTextLibrary.*` besteht.
   - Der neue Test-Zweig wird für Linux geprüft (dort gilt weiter `href="../`). Den `file:///`-Zweig kann Linux nicht auslösen, weil es keine Laufwerke hat.
3. Es wird nichts committet und nichts gepusht.

**Grenze der Prüfung:** MSVC und `/STACK` lassen sich hier nicht ausführen. Lokal lässt sich nur zeigen, dass Linux nicht kaputtgeht; ob beide Windows-Tests bestehen, zeigt erst ein CI-Lauf nach deinem Push.
