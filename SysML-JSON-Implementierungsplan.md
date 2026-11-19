# Implementierungsplan: JSON-Serialisierung und -Deserialisierung für alle SysML-v2-Elemente

Stand: 2026-10-25, Branch `AddingJsonParsingToAllElements` (Basis: Commit `e7fed0a3`).
Status: **Entwurf, wartet auf Freigabe.** Nichts wird committet.

Ausführung: Ein **Sonnet-Runner** setzt die Arbeitspakete (AP) um, **Opus** prüft nach jedem Prüfpunkt (🔍).
Der Runner geht nur nach einem bestandenen Prüfpunkt zum nächsten AP weiter.

---

## 1. Ausgangslage (was es schon gibt)

| Bereich | Stand |
|---|---|
| KerML (78 Metaklassen) | JSON fertig. Generator `kerml/tools/generate_json.py` schreibt Blöcke zwischen `BEGIN GENERATED JSON` / `END GENERATED JSON` in Header und `.cpp` und fügt `clearUnresolvedJsonReferences("<prop>")` in die Referenz-Setter ein. |
| Hilfsfunktionen | `kerml/src/kerml/model/JsonSupport.h` (privat, nur Header): `Json::reference`, `value`, `readBool/readString/readInt/readEnum`, `readReferences`, `looksLikeJson`, … |
| Fabrik | `KerML::Entities::createElementFromJson` / `createElementsFromJson` (`kerml/model/ElementFactory.h`). Unbekannte `@type` (also **alle SysML-Typen**) landen als einfaches `Element` über `Element::fromJson()`. |
| Verlinkung | `linkElements` / `rebuildDerivedProperties` (`ElementLinker`) arbeiten mit `dynamic_pointer_cast` → funktionieren auch für SysML-Unterklassen. |
| SysML (93 Klassen, 89 konkret, 5 Enums) | **Komplett generiert** von `sysml/tools/generate_abstract_syntax.py` (schreibt ganze Dateien neu, `--check` vergleicht ganze Dateien). Bisher kein JSON. |
| SysML-Eigenschaften | 21 gespeicherte (Bool, String, 5 SysML-Enums, `VisibilityKind`, 2 Referenzen), 197 abgeleitete: „Derived view“ (berechnet, nur Getter) und „Derived snapshot“ (Getter + Setter). |
| REST | `rest-api/.../SysMLv2Deserializer.cpp:60` ruft die KerML-Fabrik; `sysmlv2rest` linkt `sysml` heute **nicht**. |
| Tests | `conformance-test/src/TestKerMLJson.cpp` (GoogleTest, Makro-Liste aller konkreten Klassen, Round-Trip, Fabrik, Linking). |

Alle drei Generatoren sind aktuell (`--check` → verified).

## 2. Ziel

Jede SysML-Metaklasse verhält sich bei JSON exakt wie die KerML-Klassen:

1. `X(const std::string& nameOrJson)`: JSON (beginnt mit `{`) → befüllen, sonst deklarierter Name.
2. `serializeToJson()`: alle Eigenschaften (gespeichert + abgeleitet) inkl. aller Basisklassen; Referenzen nur als `{"@id": "<uuid>"}`; `@type` = SysML-Metaklasse.
3. `deserializeAndPopulate()` (protected): gespeicherte Werte + abgeleitete Referenzen mit Setter (Snapshots); Referenzen nur als IDs.
4. `resolveJsonReferences(lookup)`: IDs → Objekte über die Setter, ein `try` je Eigenschaft.
5. Fabrik erzeugt aus `"@type": "PartUsage"` ein echtes `SysMLv2::Entities::PartUsage`; REST nutzt sie.

Format wie bisher (SysML v2 API & Services, REST/HTTP PSM): `@id`, `@type`, Eigenschaftsnamen des Metamodells, Enum-Literale in OMG-Schreibweise (`"timeslice"`, `"do"`, `"entry"`, …).

## 3. Architekturentscheidungen (bitte mit freigeben)

**E1 – JSON-Code direkt in `sysml/tools/generate_abstract_syntax.py` erzeugen.**
Ein zweiter Generator mit Markern (wie bei KerML) würde von `generate_abstract_syntax.py` überschrieben, und dessen `--check` würde scheitern. Der SysML-Generator kennt Typen, Setter und Getter ohnehin aus dem Manifest, also braucht es kein Header-Parsing. Die JSON-Logik kommt in ein eigenes Python-Modul `sysml/tools/json_codegen.py`, das `generate_abstract_syntax.py` importiert. So bleibt das Hauptskript übersichtlich.

**E2 – Hilfsfunktionen wiederverwenden, nicht kopieren.**
`sysml` bekommt `target_include_directories(sysml PRIVATE ${PROJECT_SOURCE_DIR}/kerml/src)` und ein neues, generiertes `sysml/src/sysml/model/JsonSupport.h`, das `<kerml/model/JsonSupport.h>` einbindet und `Json::literal/value/readEnum` (auch für `std::optional<…>`) für `PortionKind`, `RequirementConstraintKind`, `StateSubactionKind`, `TransitionFeatureKind`, `TriggerKind` ergänzt. Es wird nichts installiert und keine öffentliche API geändert.
*Alternative:* `JsonSupport.h` nach `kerml/include/kerml/model/detail/` verschieben (dann öffentlich).

**E3 – Eigene SysML-Fabrik, REST linkt `sysml`.**
Neu: `sysml/include/sysml/model/ElementFactory.h` mit `SysMLv2::Entities::createElementFromJson` / `createElementsFromJson`. Zuerst kommt die (generierte) SysML-Tabelle der 89 konkreten Klassen, danach als Fallback die KerML-Fabrik. `createElementsFromJson` ruft danach `KerML::Entities::linkElements`. `sysmlv2rest` linkt zusätzlich `sysml` (es entsteht kein Zyklus: `sysml` hängt nur von `kerml` und `sysmlv2interfaces` ab), und `SysMLv2Deserializer` ruft die SysML-Fabrik.
*Alternative:* Registrierungs-Hook in `kerml` (`registerElementCreator`). Das ist flexibler, aber mit statischen Initialisierern anfälliger.

**E4 – Gleiches Muster wie KerML (Basen rekursiv, `json.update`).**
Das ist konsistent und leicht zu prüfen. Bekannte Kosten: Bei Rauten-Vererbung wird z. B. `SuccessionFlowUsage` über ~62 Basisaufrufe serialisiert. Das wird akzeptiert. Eine Optimierung über einen „visited set“ gehört nicht zu dieser Aufgabe und wird nur notiert.

**E5 – Abgeleitete SysML-Eigenschaften werden nicht in `rebuildDerivedProperties` nachberechnet.**
Snapshots (z. B. `PartUsage::partDefinition`) werden aus JSON gelesen, wenn sie vorhanden sind, und sonst nicht. Views werden ohnehin berechnet. Eine semantische Auswertung gehört nicht zu dieser Aufgabe (siehe `sysml/README.md`, „Semantic boundary“).

## 4. Generierungsregeln (Spezifikation für den Runner)

Für jede SysML-Klasse `n` (auch abstrakte; der String-Konstruktor nur für konkrete Klassen):

**Header** (innerhalb der Klasse, nach den Properties, mit denselben Doxygen-Kommentaren wie in den KerML-Blöcken, Text angepasst):
`explicit X(const std::string& nameOrJson);` (nur für konkrete Klassen), `std::string serializeToJson() override;`, `void resolveJsonReferences(const std::function<std::shared_ptr<KerML::Entities::Element>(const boost::uuids::uuid&)>& lookup) override;`, `protected: void deserializeAndPopulate(const std::string& jsonString) override;`.

**Basen**: `n['bases']` in Manifest-Reihenfolge (KerML oder SysML, korrekt qualifiziert über `cpp()`), **ohne** `Representation`.

**String-Konstruktor**: `X::X(const std::string& nameOrJson) : X() { if (Json::looksLikeJson(nameOrJson)) { deserializeAndPopulate(nameOrJson); captureJsonSource(nameOrJson); } else { setDeclaredName(nameOrJson); } }`. `_dType` setzt bereits `X()`.

**serializeToJson**: `json = parse(Base0::serializeToJson())`, für die weiteren Basen `json.update(parse(Bi::serializeToJson()))`, danach **jede** eigene Eigenschaft über `X::prop()`:
- Referenz (einzeln/Liste): `Json::reference(unresolvedJsonReferences("prop"), X::prop())`
- Skalar/Enum (auch `std::optional`, leer → `null`): `Json::value(X::prop())`
- Abschluss: `return applyJsonSource(json.dump(JSON_INTENT));`

**deserializeAndPopulate**: zuerst alle `Bi::deserializeAndPopulate(jsonString)`, dann:
- gespeicherte Skalare/Enums: `Json::readBool/readString/readEnum` → Setter, `catch (std::invalid_argument&)` ignorieren
- Referenzen **mit Setter** (gespeichert + Snapshot): `Json::readReferences` → `setUnresolvedJsonReferences("prop", ids)`
- abgeleitete Skalare und Views: ignorieren

**resolveJsonReferences**: zuerst alle Basen, dann je Referenz mit Setter derselbe Block wie in `generate_json.py` (einzeln / Liste, Liste nur vollständig). Zieltyp ist `KerML::Entities::T` oder `SysMLv2::Entities::T`.

**Setter-Hook**: Jeder generierte Referenz-Setter beginnt mit `clearUnresolvedJsonReferences("prop");`.

**Namenskollisionen** (gefunden: `Expose.visibility`, `Expose.isImportAll`, `ConnectionDefinition.isSufficient`, `TransitionUsage.source/target`, `AssignmentActionUsage.referent`, `FlowDefinition.flowEnd`):
- Der Generator prüft für jede Klasse die gesamte Vererbungslinie. Teilen sich zwei Referenz-Eigenschaften mit Setter denselben Schlüssel, aber mit verschiedenen Typen, bricht er mit `SystemExit` ab.
- `Expose`: Die Setter leiten schon an `Import` weiter, also werden für `Expose` keine eigenen Lese- und Schreibzeilen erzeugt (das erledigt `Import`).
- `ConnectionDefinition.isSufficient` hat ein eigenes Member, das `Type::isSufficient` verdeckt. Serialisiert wird der SysML-Wert (er überschreibt den Typ-Wert). Beim Lesen werden **beide** Setter aufgerufen (`ConnectionDefinition::setIsSufficient` und `Type::setIsSufficient`). Das bekommt einen Kommentar im Generator.
- `TransitionUsage.source/target`, `referent`, `flowEnd`: Diese Klassen sind keine KerML-Klassen mit gleichnamiger Eigenschaft, es gibt also keine Kollision im Objekt. Nur der Check muss das bestätigen.

**Includes in `.cpp`**: `<nlohmann/json.hpp>`, `"../model/JsonSupport.h"`, `<kerml/KerML.h>` bzw. die nötigen Header der Referenztypen.

**Fabrik**: Der Generator erzeugt `sysml/src/sysml/model/ElementFactory.cpp` (Tabelle `"Name" → make_shared<Name>(json)`) und den Header aus E3. Beide kommen in die CMake-Liste.

## 5. Arbeitspakete

### AP0 – Baseline (Runner)
- `cmake --preset Debug` und Build mit `conformance-test` sowie `sysml`. `ctest -R conformance-regression` ausführen und das Ergebnis notieren.
- Alle drei `--check` ausführen.
- **Ergebnis:** kurzer Bericht (Build-Zeit, grüne und rote Tests vorher).

### AP1 – JSON-Hilfen für SysML (Runner)
- `json_codegen.py` (Grundgerüst) und das generierte `sysml/src/sysml/model/JsonSupport.h` (E2) mit Enum-Mapping. Die Literale kommen aus `abstract_syntax.json`, `do_` wird zu `"do"`.
- CMake: PRIVATE-Include `kerml/src` für das Ziel `sysml`.
- **Abnahme:** `sysml` kompiliert, `generate_abstract_syntax.py --check` verified.

### AP2 – Generator für Klassen-JSON (Runner)
- Regeln aus Abschnitt 4 in `json_codegen.py` umsetzen und in `generate_abstract_syntax.py` einhängen. Danach Generator laufen lassen.
- Kollisions-Check und die Sonderfälle `Expose` und `ConnectionDefinition` umsetzen.
- **Abnahme:** `sysml` baut ohne neue Warnungen (`-Wall -Wextra -Wpedantic`), `--check` verified, `generate_json.py --check` und `generate_xmi_bindings.py --check` weiterhin verified (die XMI-Bindings dürfen sich nicht ändern; falls doch, begründen).

### 🔍 Prüfpunkt A (Opus)
Opus prüft Generator-Diff und Stichproben des generierten Codes: `PartUsage`, `Expose`, `ConnectionDefinition`, `PortConjugation`, `ConjugatedPortTyping`, `TriggerInvocationExpression`, `OccurrenceUsage` (optional `portionKind`), `SuccessionFlowUsage` (Raute).
Kriterien: Basenliste vollständig und ohne `Representation`, Namespaces korrekt, kein Lesen von Views, Snapshot-Referenzen gelesen, Setter-Hooks vorhanden, Enum-Literale gemäß OMG, Kollisionsbehandlung.

### AP3 – Fabrik und REST (Runner)
- SysML-Fabrik (E3) generieren, `ElementFactory.h` in `SysML.h` aufnehmen.
- `rest-api/CMakeLists.txt`: `sysml` linken. `SysMLv2Deserializer.cpp`: `SysMLv2::Entities::createElementFromJson`. Kommentar Zeile 55–57 anpassen.
- Prüfen, ob `deserializeJsonArray` auch `createElementsFromJson`/`linkElements` nutzt, und gegebenenfalls auf SysML umstellen.
- **Abnahme:** Gesamter Build grün.

### AP4 – Tests (Runner)
Neue Datei `conformance-test/src/TestSysMLJson.cpp` (in CMake eintragen, `/bigobj` wie bei KerML), mit `TestKerMLJson.cpp` als Vorlage:
1. `SYSML_CONCRETE_CLASSES(X)`-Makro mit allen 89 konkreten Klassen. Als Test generieren oder gegen `metaclasses()` abgleichen, damit keine Klasse fehlt.
2. Round-Trip jeder konkreten Klasse (`serialize → X(json) → discardSourceJson → serialize` gleich).
3. Default-konstruiert → gültiges JSON, `@type` korrekt.
4. Fabrik: `@type` → richtige C++-Klasse (`dynamic_pointer_cast`); KerML-Typ über die SysML-Fabrik → KerML-Klasse; unbekannter Typ → `Element`.
5. Spezifische Werte: `isVariation`, `isIndividual`, `portionKind` (gesetzt und leer), `reqId`, alle 5 Enums inkl. `"do"`, `isParallel`, `Expose.visibility/isImportAll`, `ConnectionDefinition.isSufficient`.
6. Referenzen: `PortConjugation.originalPortDefinition`, `ConjugatedPortTyping.conjugatedPortDefinition` und ein Snapshot (z. B. `PartUsage.partDefinition`): unaufgelöst Round-Trip, aufgelöst per `lookup`, Setter überschreibt eingelesene ID, abgelehnte Referenz bricht andere nicht ab.
7. Batch: kleines Modell (Package → PartDefinition → PartUsage mit FeatureTyping, OwningMembership) über `createElementsFromJson`; `owner`/`ownedElement`/`ownedFeature`/`ownedPart` sind danach korrekt.
8. Fehlerfälle: kaputtes JSON, fehlende oder ungültige `@id`, falsche Typen in Feldern werden toleriert.
- **Abnahme:** Alle neuen und alten Tests grün. Kein vorher grüner Test wird rot.

### 🔍 Prüfpunkt B (Opus, Schlussprüfung)
- Kompletter Diff (`git diff`), Build und Tests selbst ausführen.
- Prüfen, ob die Tests das Verhalten wirklich festhalten (keine leeren Assertions, Kollisionsfälle abgedeckt).
- `README` von `sysml` um einen Abschnitt „JSON“ ergänzen lassen, falls fehlend.
- Bericht an dich: was erledigt ist, was offen bleibt, Testergebnisse.

## 6. Nicht Teil dieser Aufgabe
- Semantische Nachberechnung der SysML-Snapshots (E5).
- Performance-Optimierung der Rauten-Serialisierung (E4).
- Bereinigung des verdeckten `ConnectionDefinition::isSufficient`-Members im Datenmodell (nur dokumentiert).
- JSON-LD (`application/ld+json`), Commits und Push.

## 7. Risiken
| Risiko | Gegenmaßnahme |
|---|---|
| Mehrdeutige Überladungen oder versteckte Getter durch Mehrfachvererbung (z. B. `isSufficient()` const vs. non-const) | immer qualifiziert aufrufen (`X::prop()`); Prüfpunkt A |
| Längere Compile-Zeit und größere Objektdateien | `/bigobj` für MSVC, Testdatei ggf. aufteilen |
| `elementId()` in `Membership` protected (bekannt aus KerML-Tests) | gleiche Hilfsfunktion `elementIdOf` wie in KerML-Tests |
| Neuer Linkpfad REST → `sysml` bricht Windows/Conan-Build | Linux-Build im AP3, Windows-Hinweis im Bericht |
