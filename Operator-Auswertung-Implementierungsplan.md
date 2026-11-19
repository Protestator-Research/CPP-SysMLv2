# Implementierungsplan: Auswertung von Operatoren und Expressions

## Ausgangslage

Operator-Ausdrücke werden geparst und als Modellelemente abgelegt, aber weder an ihre Bibliotheksfunktion gebunden noch
ausgewertet.

| Bereich | Stand heute |
|---|---|
| Grammatik | `owned_expression` deckt alle Operatoren ab (`KerML.g4:246ff.`, analog `SysMLv2.g4`) |
| Listener | erzeugen `OperatorExpression` mit `operatorName` und Argumenten (`KerMlListenerImplementation.cpp:3645` `finishOperatorExpression`, `:3602` `attachExpression`; analog `SysMLv2ListenerImplementation.cpp:1438ff.`) |
| Bindung | `operatorName()` und `Expression::setFunction()` werden außerhalb von Modell und XMI nirgends verwendet; `1 + 2` kennt `DataFunctions::'+'` nicht |
| `->`-Aufrufe, Invocations | `instantiatedType` wird über `typeReference(...)` aufgelöst, `function` nicht gesetzt |
| Auswertung | kein Evaluator; `isModelLevelEvaluable` wird nie berechnet (Kommentar im Header: „populated by an importer or semantic evaluator") |
| Bibliothek | Operatorfunktionen in `resources/sysml.library/KerML/Function/*.kerml`, fast alle `abstract` ohne Rumpf |
| Literale | `LiteralInteger` = `std::int64_t`, `LiteralRational` = `double`, `LiteralBoolean`, `LiteralString`, `LiteralInfinity` |

Vom Listener vergebene Operatornamen: die Token der Binär- und Unäroperatoren (`+ - * / % ** ^ .. < > <= >= == != === !==
& and xor | or implies ?? not ~`), dazu `if`, `as`, `meta`, `istype`, `hastype`, `@`, `@@`, `all`, `[`, `,`, `#`, `.`, `->`.

## Ziel und Randbedingungen

- Jede `OperatorExpression` ist nach `Workspace::resolve()` an ihre Bibliotheksfunktion gebunden.
- Ein Evaluator berechnet den Wert einer Expression bzw. eines Features; Operatoren, benannte Funktionsaufrufe
  (`DataFunctions::'+'(1, 2)`) und `->`-Aufrufe laufen über denselben Weg.
- Die Auswertung wird an definierten Stellen automatisch angestoßen (Schritt 8) und ist als API direkt aufrufbar.
- Die generierten Modellklassen in `kerml/` und `sysml/` bleiben unverändert (kein `evaluate()` in den Klassen; sie stammen
  aus `abstract_syntax.json`).
- Bestehende öffentliche APIs und JSON-/XMI-Formate bleiben abwärtskompatibel. Ändert die Bindung die XMI-Ausgabe, wird das
  in Schritt 1 geprüft und entschieden, nicht stillschweigend hingenommen.
- Code, Kommentare und Konsolenausgaben auf Englisch.
- Vorgehen wie bisher: Umsetzung je Schritt durch Sonnet-Subagenten, Kontrolle je Schritt durch Opus-Subagenten, keine Commits.

### Nicht im Umfang

- Ausführung von Verhalten über die Zeit (Actions, States, Successions, Transitions).
- Lösen von Gleichungssystemen bzw. Constraints (nur Auswertung in Richtung der Bindungen).
- Vollständige `VectorFunctions`, `ComplexFunctions`, `OccurrenceFunctions` (Erweiterung über die Registry später möglich).

## Architektur

```
filehandling (sysmlv2parser)   Resolver: binds OperatorExpression -> library Function        (Schritt 1)
evaluation   (sysmlv2evaluation, neu)                                                         (Schritte 2-7)
    Value, Item                value model
    FunctionRegistry           qualified library function name -> native implementation
    EvaluationContext          target (featuring instance), parameter bindings, diagnostics, depth, cycle guard
    Evaluator                  dispatch on the Expression metaclass
check, Workspace, REST         callers                                                        (Schritt 8)
```

`sysmlv2evaluation` hängt nur von `kerml` (und für Schritt 7 von `sysml`) ab, nicht vom Parser. Damit ist es auch auf Modellen
nutzbar, die per XMI/JSON geladen wurden. Neue CMake-Option `BUILD_WITH_EVALUATION` (Standard `ON`), Verzeichnis `evaluation/`
mit `include/sysmlv2/evaluation/`, `src/`, `tests/`, Aufbau wie `check/CMakeLists.txt`.

## Schritte

### Schritt 1: Operator an Bibliotheksfunktion binden (Resolver)

- Neue private Datei `filehandling/src/sysmlv2/resolution/OperatorFunctions.{h,cpp}` nach dem Muster von
  `ImplicitGenerals.h`: `const char* operatorFunction(const std::string& operatorName, size_t argumentCount)` liefert den
  qualifizierten Namen.
  - `BaseFunctions`: `== != === !== [ # , all istype hastype @ @@ as meta`
  - `ControlFunctions`: `. if ?? and or implies`
  - `DataFunctions`: alle übrigen (`+ - * / % ** ^ .. < > <= >= not xor ~ | &`)
- Im Resolver nach der Namensauflösung: für jede `OperatorExpression` ohne `instantiatedType` die Funktion über den
  bestehenden Lookup holen und `setInstantiatedType` + `setFunction` setzen. Für `InvocationExpression` und `->`
  `setFunction` aus dem bereits aufgelösten `instantiatedType` ableiten, wenn dieser eine `Function` ist.
- Ist die Bibliothek nicht geladen, bleibt die Expression ungebunden (kein Fehler, kein „unresolved"-Eintrag; so wie bei den
  impliziten Generalisierungen).
- `replaceSource()` / erneutes `resolve()`: Bindung muss wiederholbar sein (idempotent).
- **Prüfen:** XMI-/JSON-Ausgabe vor/nach für die `valid`-Testdaten und die Standardbibliothek. Erscheinen neue Einträge
  (`instantiatedType`, `function`), mit den Referenz-XMI in `resources/sysml.library.xmi` vergleichen. Stimmen sie mit der
  Referenz überein, ist das eine Verbesserung (ggf. Einträge aus `conformance-test/expected_xmi_diffs.txt` entfernen),
  sonst die Bindung nur im Speicher halten und nicht serialisieren.
- Tests: je Operator ein Fall, der `function()->qualifiedName()` prüft; Fall ohne geladene Bibliothek.

### Schritt 2: Modul `evaluation` und Wertmodell

- CMake-Gerüst, Export-Makro `sysmlv2evaluation_global.h`, gtest-Ziel `sysmlv2evaluation-test`.
- `Value.h`:

```cpp
namespace SysMLv2::Evaluation {
    struct Quantity;  // step 7
    using Item = std::variant<bool, std::int64_t, double, std::string,
                              std::shared_ptr<KerML::Entities::Element>, Infinity /*, Quantity */>;
    // Every KerML value is a sequence; null is the empty sequence.
    class Value {
    public:
        const std::vector<Item>& items() const;
        bool isNull() const;
        // typed access for the single-item case, std::nullopt otherwise
        std::optional<bool> asBoolean() const;
        std::optional<std::int64_t> asInteger() const;
        std::optional<double> asReal() const;      // Integer is promoted
        std::optional<std::string> asString() const;
        std::string toString() const;               // locale independent
        nlohmann::json toJson() const;
    };
}
```

- `Diagnostic` (Schweregrad, Text, auslösendes Element) und `Result { Value value; std::vector<Diagnostic> diagnostics;
  bool ok() const; }`. Keine Exceptions über die Modulgrenze.
- Zahlenausgabe locale-unabhängig (siehe Commit `424ee7e3`), `std::to_chars` statt Streams.

### Schritt 3: `FunctionRegistry` und native Kernfunktionen

```cpp
using NativeFunction = std::function<Value(EvaluationContext&,
    const std::vector<std::shared_ptr<KerML::Entities::Expression>>& arguments)>;

class FunctionRegistry {
public:
    static FunctionRegistry withStandardFunctions();
    void registerFunction(const std::string& qualifiedName, NativeFunction implementation);
    // Looks up the function itself, then its generals (IntegerFunctions::'+' -> ... -> DataFunctions::'+').
    const NativeFunction* find(const std::shared_ptr<KerML::Entities::Function>& function) const;
};
```

- Argumente kommen unausgewertet an; ein Helfer `context.evaluate(argument)` wertet aus. Damit sind `if`, `and`, `or`,
  `implies`, `??` bedarfsgesteuert.
- Implementierung an der abstrakten Wurzel registrieren (`DataFunctions::'+'`), Typwahl zur Laufzeit:
  Integer∘Integer → Integer (`/` → Real, wie `IntegerFunctions::'/'` → `Rational`), sonst Real; `+` auf Strings = Verkettung;
  unäres `-`/`+` über fehlendes zweites Argument.
- Erster Satz: Arithmetik, Vergleiche, `== != === !==`, `not xor & |`, `and or implies`, `if`, `??`, `..`, `,`.
- Fehlerfälle als Diagnose und leerer Wert: Division durch null, Integer-Überlauf, unpassende Typen, falsche Anzahl
  Argumente, keine Implementierung registriert.
- Tests: Tabelle Ausdruck → erwarteter Wert, getrennt für Integer, Real, Boolean, String, gemischte Typen.

### Schritt 4: `Evaluator` für Expressions ohne Modellkontext

```cpp
class Evaluator {
public:
    explicit Evaluator(FunctionRegistry registry = FunctionRegistry::withStandardFunctions());
    Result evaluate(const std::shared_ptr<KerML::Entities::Expression>& expression,
                    const std::shared_ptr<KerML::Entities::Element>& target = nullptr) const;
    Result evaluate(const std::shared_ptr<KerML::Entities::Feature>& feature,
                    const std::shared_ptr<KerML::Entities::Element>& target = nullptr) const;
    FunctionRegistry& registry();
};
```

- Dispatch per `dynamic_pointer_cast`, speziellste Klasse zuerst: `LiteralBoolean/Integer/Rational/String/Infinity`,
  `NullExpression`, `OperatorExpression`, `InvocationExpression`. Übrige Typen vorerst Diagnose „not supported".
- Fallback für ungebundene `OperatorExpression` (Bibliothek nicht geladen oder Modell aus altem JSON): Suche über
  `operatorFunction(operatorName)`-Namen in der Registry. Die Tabelle aus Schritt 1 dafür in einen gemeinsam nutzbaren
  Header in `kerml` oder `evaluation` legen, nicht doppelt pflegen.
- `EvaluationContext`: Rekursionstiefe (Limit konfigurierbar, Standard 1000), Menge der gerade ausgewerteten Features
  (Zykluserkennung), Diagnosen.
- Tests: End-to-End über `Workspace` (Text parsen, `resolve()`, Feature per `find()` holen, auswerten), z. B.
  `attribute x = 2 * (3 + 4) ** 2;`, Präzedenz und Assoziativität, `if a ? b else c`.

### Schritt 5: Feature-Referenzen und Kontext

- `FeatureReferenceExpression`: Referent bestimmen, im Kontext `target` die wirksame Bindung suchen (Redefinitionen entlang
  der Spezialisierungskette, speziellste zuerst), deren `FeatureValue::value()` auswerten. `default`-Werte nur, wenn keine
  Redefinition bindet. Ohne Wert: leere Sequenz.
- `FeatureChainExpression` (`a.b.c`): linkes Ergebnis wird `target` für den nächsten Schritt; bei Sequenzen elementweise.
- `self`/`that` und Parameterreferenzen über Bindungen im `EvaluationContext`.
- `isModelLevelEvaluable` berechnen (KerML 8.4.4.9): Hilfsfunktion `isModelLevelEvaluable(expression)` im Modul; ob der
  Wert zusätzlich per `setIsModelLevelEvaluable` ins Modell geschrieben wird, entscheidet der XMI-Vergleich wie in Schritt 1.
- Tests: Redefinition in spezialisierter Definition, Usage mit überschriebenem Wert, zyklische Definition
  (`a = b; b = a;` → Diagnose statt Endlosschleife), Kette über Parts.

### Schritt 6: Benutzerdefinierte Funktionen und Sequenzen

- `InvocationExpression` auf eine `Function` mit Rumpf: Argumente an Parameter binden (positional und benannt; die Listener
  legen Argumente bereits als Parameter-Features mit Redefinition an, `KerMlListenerImplementation.cpp:2492ff.`), dann
  Result-Expression (`ResultExpressionMembership`) im neuen Kontext auswerten. Gilt auch für SysML `calc def`.
- Body-Expressions (`{ ... }`) als Funktionswerte für `->`-Aufrufe.
- `SelectExpression` (`.?`), `CollectExpression` (`.`), `IndexExpression` (`#`), `[`.
- Native Funktionen: `SequenceFunctions` (`size`, `isEmpty`, `notEmpty`, `includes`, `head`, `tail`, `last`, …),
  `ControlFunctions` (`collect`, `select`, `reject`, `forAll`, `exists`, `reduce`, …), `NumericalFunctions` (`sum`,
  `product`, `abs`, `min`, `max`), `RealFunctions`/`TrigFunctions` (`sqrt`, `floor`, `round`, `sin`, …),
  `StringFunctions`, `BooleanFunctions`.
- Tests: rekursive Funktion (Fakultät), `(1, 2, 3)->sum()`, `parts.mass->sum()`-artige Rollups, Tiefenlimit.

### Schritt 7: Klassifikation und Einheiten

- `istype`, `hastype`, `@`, `as`, `all`, `meta`, `@@`, `MetadataAccessExpression` auf Basis der Typen des ausgewerteten
  Elements (Spezialisierungshülle).
- Einheiten: `5 [kg]` ist `'['(5, kg)`. `Quantity { double value; std::shared_ptr<Element> unit; }` als weiteres `Item`.
  Stufe 1: gleiche Einheit → rechnen, verschiedene → Diagnose. Stufe 2 (optional, eigener Unterschritt): Umrechnung über
  `ISQ`/`SI` (`unitConversion`, Präfixe) und Dimensionsprüfung bei `*` und `/`.
- Die bestehende Fehlermeldung „Unit in place of Multiplicity" (Commit `7cff3f73`) darf nicht kollidieren.

### Schritt 8: Automatischer Aufruf

- **Check** (`check/src/Checker.cpp`): neue, per Option abschaltbare Diagnosegruppe:
  - Constraints, Invarianten und `assert constraint`, die modell-evaluierbar sind und `false` ergeben;
  - `require constraint` in erfüllten Requirements (`satisfy`), soweit auswertbar;
  - Multiplizitätsgrenzen als Ausdruck (`[1..n]`), Verletzung bei bekannter Anzahl;
  - Auswertungsfehler (Division durch null, Typfehler) als Warnung.
  Nicht auswertbare Ausdrücke erzeugen keine Meldung.
- **Filter**: `filter`-Bedingungen von Paketen und gefilterte Imports (`import A::*[@Safety];`) über den Evaluator; betrifft
  `Resolver`/Sichtbarkeit, daher hinter einer Workspace-Option und mit Vorher/Nachher-Vergleich der Bibliotheksauflösung.
- **Komfort-API**: freie Funktion `SysMLv2::Evaluation::evaluate(workspace, "Pkg::part.mass")` in einem kleinen Adapter, der
  von `sysmlv2parser` und `sysmlv2evaluation` abhängt (kein Zyklus zwischen den Bibliotheken).
- **CLI/C-API** von `sysmlv2check`: Ergebnisfeld für ausgewertete Werte nur ergänzen, bestehende Felder unverändert.
- REST und Python-Bindings: nicht Teil dieses Plans, nur prüfen, dass die neuen Header dafür geeignet sind (keine Templates
  in der öffentlichen API außer `std`-Containern).

### Schritt 9: Tests, Doku, Abschluss

- Testdaten unter `conformance-test/testdata/evaluation/{kerml,sysml}/` mit erwarteten Werten als Kommentar oder
  Begleitdatei (`<name>.expected.json`), ein Treiber im `sysmlv2evaluation-test`.
- Standardbibliothek vollständig laden und alle modell-evaluierbaren Feature-Werte auswerten: kein Absturz, keine
  Endlosschleife, Laufzeit im Bericht nennen.
- Parse-/Resolve-Zeit der Standardbibliothek vor/nach Schritt 1 messen.
- Bestehende Tests (`conformance-test`, `check`, `kerml/tests`) bleiben grün; `expected_*.txt` nur mit Begründung ändern.
- README: Abschnitt „Evaluation" mit Beispiel und Liste der unterstützten Funktionen; Doxygen-Kommentare an der
  öffentlichen API.
- Windows/MSVC und Emscripten-Build des `check`-Moduls berücksichtigen (Export-Makros, `/bigobj`, keine
  plattformspezifischen Mathefunktionen).

## Stand

### Schritt 1: umgesetzt (2026-11-11, nicht committet)

- Tabelle `KerML::operatorFunctions` / `operatorFunctionName()` in `kerml/include/kerml/kernel/expressions/OperatorFunctions.h`
  (39 Einträge, inkl. `collect` und `select`, die die Klassenkonstruktoren als Operatornamen setzen).
- Bindung in `Workspace::Impl::bindFunctions()`, aufgerufen in `resolve()` nach `resolver.run()`; Lookup über
  `Resolver::findLibraryElement()` (niedrigste Quellebene, wie bei den impliziten Generalisierungen).
- Jedes `resolve()` bindet neu (folgt ersetzter/entfernter Bibliothek); Aufrufe je Quelle einmal gelistet.
- **XMI:** Ausgabe unverändert (`instantiatedType`/`function` sind abgeleitet und werden nicht geschrieben), per Test abgesichert.
- **JSON (Entscheidung 1):** `serializeToJson()` liefert für gebundene Operatoren `instantiatedType` und `function` als
  `{"@id": ...}` des Bibliothekselements (vorher `null`). Entschieden am 2026-11-11: bleibt so, per Test festgehalten.
- Tests: `conformance-resolution` 137, `conformance-xmi` 304, `conformance-abstract-syntax` 97, `conformance-library` 94,
  `conformance-syntax` 164, `conformance-test` 488, alle bestanden (Debug, GCC). Header zusätzlich mit clang `-Werror` geprüft.

Erkenntnisse für die Folgeschritte:

- `Element::qualifiedName()` ist für aus Text geparste Modelle `nullopt`. Die Registry (Schritt 3) kann sich nicht darauf
  stützen; entweder den Namen über die Besitzkette berechnen (wie `ConformanceTest::qualifiedNameOf`) oder die Registry
  beim Laden über `operatorFunctions` und Elementidentität aufbauen.
- Aufrufe, deren Typ ein Feature ist (`CalculationUsage`, `Expression`, ...; 21 in der Bibliothek), haben bewusst noch kein
  `function`. Schritt 6 muss die Funktion über den Typ des Features bestimmen.
- Liegen Bibliothek und Nutzermodell auf derselben Quellebene, kann ein Nutzerpaket namens `DataFunctions` die Bindung
  übernehmen (gleiches Verhalten wie bei impliziten Generalisierungen).
- Nicht gemessen: inkrementelles `replaceSource()` + `resolve()` im Release-Build; macOS-, Windows- und WASM-Build.

### Schritte 2 und 3: umgesetzt (2026-11-11, nicht committet)

- Modul `evaluation/` (`sysmlv2evaluation`, `SysMLv2::Evaluation`), hängt nur von `kerml` ab. Option `BUILD_WITH_EVALUATION`
  (Standard `ON`), in `conanfile.py` als `with_evaluation`.
- Öffentliche Header: `Value.h`, `Diagnostic.h`, `EvaluationContext.h`, `FunctionRegistry.h`, `QualifiedName.h`.
- Abweichungen vom ursprünglichen Entwurf:
  - Zwei Funktionsarten: `NativeFunction` (Argumente unausgewertet) und `StrictFunction` (Werte, per Wert übergeben).
  - `EvaluationContext` hat einen Auswertungs-Hook (`setExpressionEvaluator`); der Evaluator aus Schritt 4 hängt sich dort ein.
  - `EvaluationContext::enterElement()` führt das „aktuelle Element"; Diagnosen ohne Element bekommen es automatisch.
  - `FunctionRegistry::lookup()` meldet, ob ein Treffer geerbt ist (für Schritt 6: eigener Rumpf vor geerbter Implementierung).
  - `qualifiedNameOf()` berechnet Namen über die Besitzkette (stimmt für alle 39 Tabelleneinträge mit der Bibliothek überein).
- Registriert (26): DataFunctions `+ - * / % ** ^ < > <= >= not xor | & ..`, BaseFunctions `== != === !== ,`,
  ControlFunctions `if and or implies ??`. Nicht registriert (13): `~ [ # all istype hastype @ @@ as meta . collect select`.
- Festgelegte Semantik:
  - Integer `/` Integer ergibt Real; Integer-Überlauf, Division/Modulo durch null und nicht endliche Ergebnisse sind Fehler.
  - Leerer Operand ergibt leeres Ergebnis ohne Meldung; falscher Typ oder falsche Anzahl ist ein Fehler.
  - Integer und Real werden exakt verglichen; `Value::operator==` ist dagegen strukturell (Integer 2 ≠ Real 2.0).
  - Bewusst großzügiger als die Bibliothek: Real `%`, negativer Integer-Exponent ergibt Real, `==` auf Sequenzen.
  - `,` läuft verschachtelte Sequenzliterale iterativ ab (kein Tiefenlimit, lineare Laufzeit).
  - Zahlenausgabe: ein Codepfad ohne `std::to_chars`, kürzeste rundreisefähige Darstellung, immer mit `.` oder `e`.
- Tests: `sysmlv2evaluation-test` 51, `conformance-resolution` 137, `conformance-test` 488, alle bestanden (Debug, GCC);
  Modul und Tests zusätzlich unter Address-/UB-Sanitizer und mit clang `-Werror` geprüft.

Erkenntnisse für die Folgeschritte:

- Der KerML-Listener liefert die Argumente von `if`, `and`, `??`, unärem `-` und `..` als einfache Ausdrücke in
  Quellreihenfolge. `if` ohne `else` ist ein Syntaxfehler. Für den SysML-Listener ist das noch nicht geprüft (Schritt 4).
- Der Typoperand von `istype`, `as`, `@`, `all` kommt als `InstantiationExpression`-Argument an, der Rumpf von `.?` als
  einfaches `Expression`-Argument (Schritte 6 und 7).
- `FunctionRegistry::lookup()` baut je Knoten einen Namen (ca. 19 µs für eine Kette mit 7 Knoten). Der Evaluator sollte
  das Ergebnis je `Function` cachen.
- Tiefenlimit 1000 gegen die Windows-Stackgröße (1 MB) bei rekursiven Funktionen in Schritt 6 messen.
- `FETCHCONTENT_FULLY_DISCONNECTED=ON` steht seit dem Neukonfigurieren in `build/Debug/CMakeCache.txt` (Sandbox ohne GitHub).
- Nicht geprüft: MSVC, macOS, Emscripten, `conan create`, Konfiguration mit `BUILD_WITH_EVALUATION=OFF`.

### Schritt 4: umgesetzt (2026-11-12, nicht committet)

- `Evaluator` (`Evaluator.h`, pimpl, verschiebbar): `evaluate(expression, target)` und `evaluateFeatureValue(feature, target)`;
  `EvaluationOptions{maxDepth, maxSequenceLength}`; `Result` mit `ok()` und `failed`.
- Wertet Literale, `NullExpression`, Operator- und Aufrufausdrücke über die native Registry aus – für Textmodelle, für XMI
  in Pilot-Form und für XMI aus dem eigenen `XmiWriter` (gemeinsamer Helfer `argumentsOf` in `src/Arguments.{h,cpp}`).
- Abweichungen vom ursprünglichen Entwurf:
  - Standard-Tiefenlimit 256 statt 1000 (GCC `-O0`, 1-MB-Stack, ca. zweifache Reserve; MSVC und Emscripten nicht gemessen).
  - Lookup-Cache lebt nur für einen Aufruf; die Registry wird je Aufruf per `shared_ptr` gehalten.
  - Nach einer Fehlerdiagnose ist das Ergebnis immer leer; Tiefenüberschreitung wird einmal gemeldet.
  - Benannte Argumente normaler Aufrufe werden schon jetzt nach Parameternamen geordnet (`'-'(y = 1, x = 10)` = 9);
    unbekannte, doppelte oder lückenhafte Namen und die Pfeilform werden abgelehnt. Vorgezogen aus Schritt 6.
  - Benutzerfunktionen, die eine Funktion mit nativer Implementierung spezialisieren und irgendwo in der Kette einen eigenen
    Rumpf oder umgeordnete Parameter haben, geben „not supported yet" statt des Werts der Oberfunktion (bis Schritt 6).
- Noch nicht unterstützt, jeweils mit sauberer Diagnose: Feature-Referenzen, Feature-Ketten, `select`/`collect`/Index,
  Klassifikationsoperatoren, Benutzerfunktionen, `TriggerInvocationExpression`-artige Unterklassen.
- Bibliotheksdurchlauf: Text 1168 auswertbare Features, XMI 2223; Text gegen XMI 2897 verglichen, 1148 beidseitig
  auswertbar, 0 Abweichungen, 2 benannte Ausnahmen (`Actions::WhileLoopAction::untilTest` / `whileTest`).
- Drei Opus-Prüfrunden, alle Befunde nachgearbeitet.

### Parser- und Resolver-Korrekturen aus der Prüfung von Schritt 4 (2026-11-12, nicht committet)

- Integer-Literale außerhalb int64 und Multiplizitätsgrenzen außerhalb uint32: Fehler mit Position statt `0` bzw.
  „internal: stoll" (`parser/LiteralText.h`, beide Listener). Nicht ganzzahlige Grenzen (`[2.5]`) geben eine Warnung.
- String-Escapes (`\' \" \b \f \t \n \r \\`) werden gelesen und dekodiert; ungültige Escapes sind Fehler. Dasselbe für
  Namen in Hochkommas (`'it\'s'`). `LiteralString::value()` enthält den dekodierten Text.
- Grammatik (`KerML.g4`, `SysMLv2.g4`, Parser mit `tools/antlr-4.13.2-complete.jar` neu erzeugt, SysML jetzt mit Visitor):
  `STRING_VALUE`, `UNRESTRICTED_NAME`, iterative `sequence_expression_list` (Modell unverändert), `membership_import`
  (`::` nur noch vor `*`/`**`), Mehrdeutigkeit um `package` in `start_element`/`package_body` beseitigt.
  Bibliothek lädt dadurch in ca. 20 s statt 32 s (Debug).
- Sehr lange/tiefe Texte: `Resolver::visit`, `lookupRecursive`, `XmiWriter::collect`/`emit` iterativ; `resolve()` läuft auf
  dem großen Stack. Grenzen in `Workspace.cpp`, dokumentiert in `Workspace.h` und `README.md`:
  - Parser-Rekursion 10000 und Parse-Baum-Tiefe 200000 bei 512 MB Stack, skaliert mit dem tatsächlich erhaltenen Stack
    (512 → 128 → 32 MB, sonst gemessener Reststack des Aufrufers; WebAssembly: vorsichtige 1-MB-Werte).
  - Vorausschau-Budget ohne Uhr: 1 000 000 Einheiten je Entscheidung, 60 je Token plus 10 000 000 je Text.
  - Drei Fehlermeldungen: „nesting too deep", „text too large for the stack", „look-ahead budget exceeded".
  - Nach abgelehntem oder auffälligem Parse wird der ANTLR-Cache der Sprache geleert (Reader/Writer-Sperre je Sprache).
  - Feature-Ketten: ab 512 Gliedern werden weitere Glieder nicht aufgelöst (eine Warnung).
- Nebenbei behoben: kubische Laufzeit der KerML-Sichtbarkeitssuche und von `detail::checkCollection` (Anhängen an Listen),
  quadratischer Speicher der XMI-Id-Schlüssel (Ids bitgleich, Festwert-Test), Test-Hook in
  `sysmlv2/detail/WorkspaceTesting.h` (nicht installiert).
- Tests (2026-11-12, Debug, GCC, nacheinander, alle bestanden): `conformance-lexer` 32, `conformance-syntax` 180,
  `conformance-library` 94, `conformance-abstract-syntax` 97, `conformance-xmi` 307, `conformance-resolution` 137,
  `conformance-robustness` 118, `conformance-evaluation` 49, `conformance-test` 516, `sysmlv2evaluation-test` 112.

Offene Folgepunkte (nicht Teil dieses Plans, noch nicht begonnen):

- `~Workspace` gibt die Modelle nicht frei (zyklische `shared_ptr`, ca. 160 MB je 1 MB Text); hoher Speicher je Token.
- `import a::*::**` wird abgelehnt (war schon vorher so).
- WebAssembly-Grenzen nicht im Browser gemessen; Windows- und Emscripten-Zweige des Stack-Codes nur gelesen, nie gebaut.
- XMI-Ausgabe mit Standard-Einrückung ist bei sehr tiefen Modellen quadratisch groß.
- Die letzte Sonnet-Runde (13 Punkte aus der dritten Prüfung) wurde nicht noch einmal von Opus gegengeprüft.
- `RealFunctions::'+'(1,2)` liefert Integer 3; `SIPrefixes::zebi/yobi` laufen in den Integer-Überlauf.
- `filehandling/resources/grammars/gen/` (unversionierte Java-Ausgabe) und leere Punkt-Dateien im Repo-Wurzelverzeichnis
  (`.bashrc`, `.gitconfig`, …) nicht committen.

### Schritt 5: umgesetzt (2026-11-12, nicht committet)

- Feature-Referenzen: Wert = wirksame Bindung des Referenten im Kontext. Kandidaten sind der Referent, alles, was er
  (transitiv) redefiniert, und jedes Feature im Abschluss des Ziels, das eines davon redefiniert. Gebundene Werte zuerst
  (speziellster gewinnt), dann der speziellste `default`. Zwei unabhängige gebundene Werte: Fehler „ambiguous".
- Kontext ist ein Navigationsweg (innerste Instanz zuerst), nicht ein einzelnes Ziel: `myCar.transmission.input` sieht die
  Redefinitionen von `myCar`, auch über Aliase (`ref part driverSeat = seat`). Der öffentliche Parameter `target` bleibt
  ein Element; ein explizit übergebenes verschachteltes Ziel sieht nur die Werte der Definition (dokumentiert).
- Ohne `target` gilt der besitzende Typ des Features als Kontext (beide Einstiegspunkte gleich); `self` ist dann der Typ
  als Stellvertreter für „irgendeine Instanz". Auf Paketebene: Fehler „'self' has no target".
- Ketten `a.b.c`: elementweise, flach, mit `maxSequenceLength`; vom Parser unaufgelöste Glieder werden per Name im Ziel
  gesucht (ohne geerbte private Member), sonst Fehler.
- `self`/`that` über die Redefinitionskette erkannt (`Base::Anything::self`, `Base::things::that`); `that` ungebunden: Fehler.
  `EvaluationContext`: `enterTarget`, `target`, `bind`, `binding`.
- Zyklen: eine Diagnose „cyclic definition: a -> b -> a", Schlüssel ist (Feature, Weg).
- Abweichungen vom Plan:
  - Ein Feature ohne Wert ergibt das Element selbst statt der leeren Sequenz, wenn es kein reines Attribut ist:
    Enum-Literale, alle `*Usage` außer `AttributeUsage`/`ReferenceUsage`, Features mit Class-Typ. Unbelegte Attribute
    bleiben leer. Sonst wären `engine == transmission` und `Col::red == Col::green` wahr.
  - Warnung (Wert bleibt gültig), wenn ein gebundener Wert einen gebundenen Wert überschreibt oder ein speziellerer
    `default` wegen eines gebundenen Werts ignoriert wird.
  - `evaluateFeatureValue(feature, target)`: Fehler, wenn das Ziel nicht zum Besitzer des Features passt.
- `isModelLevelEvaluable(expression)` (`ModelLevelEvaluable.h`): syntaktische Regel nach KerML 8.4.4.9, aus der Erinnerung
  des Prüfers rekonstruiert; Funktionen gelten als auswertbar, wenn sie Operatorfunktionen sind oder in einem der 17
  `LibraryPackage`s unter `KerML/Function/` liegen. Das Bibliotheks-XMI enthält keine Vergleichswerte; ins Modell wird
  nichts geschrieben.
- Bibliotheksdurchlauf: Text 3071 von 3347 auswertbar (Schritt 4: 1168), XMI 7615 von 8482 (2223); Text gegen XMI 2897
  verglichen, 2741 beidseitig auswertbar, 0 Abweichungen, 1 benannte Ausnahme (`Actions::AcceptAction::acceptedMessage`:
  im Pilot-XMI fehlt die implizite Redefinition des anonymen Accept-Schritts).
- Echte Selbstbezüge in der Bibliothek (fest im Test verankert): `ShapeItems::RightTriangularPrism::rf::width`
  (`rf.width`, vermutlich Tippfehler für `ff.width`), `StatePerformance::isRunToCompletion`/`runToCompletionScope`.
- Tests (2026-11-12, selbst gelaufen): `sysmlv2evaluation-test` 120, `conformance-evaluation` 128, alle bestanden.
  Zwei Opus-Prüfrunden; die letzte Nacharbeit wurde nicht noch einmal von Opus gegengeprüft.

Offen aus Schritt 5:

- Erledigt (2026-11-12, vom Nutzer freigegeben): `XmiWriter` schreibt den Referenten einer `FeatureReferenceExpression`
  und das Ziel einer `FeatureChainExpression` als einfache `Membership` (erstes `ownedRelationship`, `memberElement` als
  Id oder `href` mit `xsi:type`). Nur Ergänzungen in der Ausgabe, keine bestehende Id ändert sich, zweimaliges Schreiben
  ist identisch, unaufgelöste Referenten schreiben nichts. Das Modell im Speicher bleibt unverändert (JSON unverändert).
  Text → XMI → Einlesen wertet Referenzen, Redefinitionen, Ketten, typisierte Aliase und Enum-Vergleiche gleich aus.
  Tests (selbst gelaufen, alle bestanden): `conformance-lexer` 32, `conformance-syntax` 180, `conformance-library` 94,
  `conformance-abstract-syntax` 97, `conformance-xmi` 317, `conformance-resolution` 137, `conformance-robustness` 118,
  `conformance-evaluation` 131, `conformance-test` 516, `sysmlv2evaluation-test` 120. Eine Opus-Prüfrunde; die
  Nacharbeit dazu wurde nicht erneut gegengeprüft.
- Bekannte Lücke nach dem XMI-Round-Trip (per Test festgehalten): Ketten, deren Ziel der Parser nicht auflöst –
  berechneter linker Operand (`(q1, q2).r`, `(w.m).i.z`, `f(x).y`, `v#(1).z`) oder untypisiertes Feature
  (`ref part x = e; x.power`) – werten aus Text per Namenssuche aus, aus zurückgelesenem XMI geben sie den Fehler
  „the feature chain has no target feature in the model". Empfohlene Behebung (eigene Aufgabe, nicht begonnen): der
  Resolver löst das Kettenziel im statischen Ergebnistyp des linken Operanden auf.
- `XmiReader` setzt `referent()`/`targetFeature()` nicht; nur die Ein-Feature-Form des Kettenziels wird geschrieben.
- Resolver: ein Benutzerfeature namens `self` wird auf `Base::Anything::self` aufgelöst statt auf das lokale Feature.
- `that`-Bindung durch den Aufrufer ist nach exaktem Feature geschlüsselt (Schritt 6).
- `evaluate(expression, target)` prüft nicht, ob das Ziel zum Ausdruck passt.

## Reihenfolge und Abhängigkeiten

| Schritt | hängt ab von | Ergebnis nutzbar als |
|---|---|---|
| 1 | – | gebundene Operatoren im Modell |
| 2, 3 | – (parallel zu 1) | Registry mit Tests ohne Parser |
| 4 | 1, 2, 3 | Auswertung konstanter Ausdrücke |
| 5 | 4 | Auswertung von Feature-Werten im Modell |
| 6 | 5 | Funktionen, Rollups |
| 7 | 5 | Typprüfungen, Größen mit Einheit |
| 8 | 5 (Check), 7 (Filter) | automatische Auswertung |
| 9 | laufend, Abschluss nach 8 | – |

Nach Schritt 5 ist ein sinnvoller Zwischenstand erreicht, der für sich nutzbar ist.

## Risiken

- **XMI-/JSON-Diffs durch die Bindung** (Schritt 1): entschärft durch den Vergleich mit den Referenz-XMI.
- **Kontextsemantik bei Redefinitionen** (Schritt 5) ist der fachlich schwierigste Teil; zuerst die einfachen Fälle
  (Definition → Usage → Redefinition) abdecken und mit Tests festhalten, verschachtelte Featuring-Kontexte danach.
- **Rational vs. Real**: `LiteralRational` ist `double`; exakte Brüche gibt es nicht. `1/3 * 3 == 1` kann `false` sein.
  Vergleich von Reals in Tests mit Toleranz, Verhalten im README nennen.
- **Laufzeit im Resolver** durch zusätzliche Lookups je Operator: Funktionszeiger je Operatorname einmal pro `resolve()`
  cachen.
- **Filter-Auswertung** ändert, welche Elemente importiert werden; deshalb hinter Option und zuletzt.

## Offene Entscheidungen

1. Bindung serialisieren (`function`/`instantiatedType` in XMI/JSON) oder nur im Speicher? Vorschlag: nach dem Vergleich in
   Schritt 1 entscheiden, Standard „wie Referenz-XMI".
2. Einheitenumrechnung (Schritt 7, Stufe 2) in diesem Plan oder als eigener Folgeplan? Vorschlag: Folgeplan.
3. Check-Diagnosen aus Schritt 8 standardmäßig an oder aus? Vorschlag: an, als Warnung, per Option abschaltbar.
4. Modulname/Namespace: `evaluation/`, `sysmlv2evaluation`, `SysMLv2::Evaluation`.
