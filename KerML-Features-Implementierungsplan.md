# Implementierungsplan: KerML-Features in SysML-Definitions- und Usage-Rümpfen

## Ausgangslage

KerML-Features mit dem Schlüsselwort `feature` werden in SysML-Texten nur auf Paketebene akzeptiert, nicht in Rümpfen:

| Eingabe | Ergebnis heute |
|---|---|
| `package Q { in feature x : Integer; }` | ok |
| `part def P { in feature x : Integer; }` | `mismatched input 'x' expecting {'default', ';', '{', '=', ':='}` |
| `part def P { feature x : Integer; }` | `no viable alternative at input 'feature x'` |
| `part def P { out feature x : …; }`, `derived feature x …` | wie oben |
| `part p { in feature x : Integer; }` (Usage-Rumpf) | wie oben |
| `calc def C { in feature x : Integer; }` | `no viable alternative at input 'in feature x'` + Folgefehler |
| `function f { in feature x : Integer; }` | ok (KerML-Regel) |

### Ursache

- `package_member` nutzt `usage_element`, das als letzte Alternative die KerML-Regel `feature_element` enthält
  (`SysMLv2.g4:91`). Die Rumpf-Regeln enthalten `feature_element` nicht:
  - `definition_body_item` (`SysMLv2.g4:99`): part/item/attribute/port/connection/occurrence/… def, alle Usage-Rümpfe
    (`usage_body: definition_body`), über `requirement_body_item`, `view_definition_body_item`, `view_body_item` auch
    Requirements, Concerns und Views.
  - `interface_body_item` (`SysMLv2.g4:256`).
  - `non_behavior_body_item` (`SysMLv2.g4:310`): action, state, calc, case, analysis, verification und use case (über
    `action_body_item`, `state_body_item`, `calculation_body_item`, `case_body_item`).
- Nach SysML 8.2.2.1.2 sind KerML-Schlüsselwörter in SysML nicht reserviert (`sysml_name` enthält `KEYWORD_FEATURE`;
  Testdatei `keywords_of_kerml_as_names.sysml`). Deshalb wird `in feature x` heute als Referenz-Usage mit dem **Namen**
  `feature` gelesen (`default_reference_usage: ref_prefix usage`), und `x` ist danach unerwartet.

## Ziel und Randbedingungen

- `[in|out|inout] [derived] [abstract] … feature <name> … ;` und die übrigen KerML-`feature`-Formen sind in allen
  oben genannten Rümpfen erlaubt, so wie heute auf Paketebene.
- **Vorrang SysML:** Ist eine Eingabe sowohl als SysML-Usage als auch als KerML-Feature lesbar, gewinnt wie bisher SysML.
  Beispiele, die unverändert als Usage mit dem Namen `feature` gelesen werden müssen:
  `in feature : Integer;`, `feature;`, `ref feature :>> function::expr;` (aus `keywords_of_kerml_as_names.sysml`).
  Nur wenn nach `feature` ein Name/eine Deklaration folgt, die als SysML-Usage nicht passt, greift die KerML-Regel.
- Keine KerML-Regel wird entfernt, keine SysML-Regel geändert, außer den Rumpf-Regeln.

## Schritte

### Schritt 1: Grammatik (`SysMLv2.g4`)

Neue Member-Regel, analog zu den bestehenden `*_member`-Regeln:

```antlr
kerml_feature_member: member_prefix feature_element;
```

Sie wird jeweils als **letzte** Alternative angehängt (ANTLR löst Mehrdeutigkeiten zugunsten der niedrigsten Alternative auf,
damit bleibt der SysML-Vorrang erhalten):

- `definition_body_item`
- `interface_body_item`
- `non_behavior_body_item`

Ob die volle Regel `feature_element` (inkl. `anonymous_feature`, `step`, `expression`, `connector`, …) oder nur `feature` mit
explizitem Schlüsselwort aufgenommen wird, entscheidet Schritt 3:
- Bevorzugt: `feature_element`, damit die Rümpfe dasselbe akzeptieren wie Pakete (gleiche Logik wie `usage_element`).
- Rückfall auf eine schmalere Regel, wenn die volle Regel dazu führt, dass Eingaben, die heute gültig sind, anders geparst
  werden (anderer Elementtyp im Ergebnis), oder die Parsezeit der Bibliothek merklich steigt.

### Schritt 2: Parser neu erzeugen

Wie im Metadaten-Plan: `tools/antlr-4.13.2-complete.jar`, `-Dlanguage=Cpp -listener -visitor -lib <grammars>`, Ausgabe nach
`$TMPDIR`, dann die bestehende Nachbearbeitung (Include-Pfade, `SYSMLV2FILE_EXPORT`, fehlende `accept()`) per Transplantation
übernehmen. Der Diff der generierten Dateien darf nur ATN, die geänderten Regeln und die neue Regel betreffen.
Nur `SysMLv2.g4` wird geändert, der KerML-Parser bleibt unberührt.

### Schritt 3: Vorrang und Mehrdeutigkeit prüfen

- Der Parser arbeitet zweistufig (SLL, bei Fehler/Konflikt LL; `Workspace.cpp:147ff.`). Beide Stufen prüfen.
- Vergleich vor/nach für alle `valid`-Testdateien und die Standardbibliothek: gleiche Anzahl Elemente und gleiche Metaklassen
  (z. B. per kleinem Treiber, der Elementtyp + Name ausgibt). Abweichungen sind Fehler, nicht hinzunehmen.
- `KeywordMisuseDiagnoser` prüfen: Er darf `in feature x : T;` nicht mehr als Schlüsselwort-Fehlgebrauch melden, muss
  aber die vorhandenen `keyword_misuse`-Tests weiter bestehen.
- Parsezeit der Standardbibliothek vor/nach messen (`conformance-library`), Abweichung im Bericht nennen.

### Schritt 4: Listener (`SysMLv2ListenerImplementation.cpp`)

`enterFeature`/`exitFeature` existieren bereits und funktionieren auf Paketebene. Prüfen und ggf. ergänzen, dass in Rümpfen:
- das Feature dem umgebenden Typ als besessenes Feature gehört (FeatureMembership, `owningType` gesetzt),
- Richtung (`in`/`out`/`inout`), `derived`, `abstract`, Typisierung, Multiplizität und Wert übernommen werden,
- in Verhaltens-/Calc-Rümpfen gerichtete KerML-Features als Parameter gelten, so wie SysML-`in x : T;`
  (Vergleich mit dem Ergebnis von `calc def C { in x : Integer; }`),
- ParentStack bei Syntaxfehlern im Feature ausgeglichen bleibt.

### Schritt 5: Tests

Testdaten (`// expect: valid`) unter `conformance-test/testdata/syntax/sysml/valid/`:
- `kerml_feature_in_definition_body.sysml`: `part def`, `item def`, `attribute def`, `port def`, `interface def`,
  `requirement def` je mit `in feature`, `out feature`, `feature x : T[0..1] = …;`, `derived feature`.
- `kerml_feature_in_usage_body.sysml`: `part p { in feature x : Integer; }` u. Ä.
- `kerml_feature_in_behavior_body.sysml`: `action def`, `state def`, `calc def`, `case def` mit `in feature`.
- `keywords_of_kerml_as_names.sysml` bleibt unverändert und muss weiter bestehen; zusätzlich eine Datei mit
  `in feature : Integer;` und `feature;` in einem `part def`.

gtests in `conformance-test/src/TestSysMLParser.cpp`:
- `part def P { in feature x : Integer; }`: ein `KerML::Entities::Feature` `x`, Richtung IN, typisiert mit `Integer`,
  besessen von `P`.
- `part def P { in feature : Integer; }`: weiterhin eine Usage mit dem Namen `feature` (SysML-Vorrang).
- `calc def C { in feature x : Integer; }`: `x` ist Parameter wie bei `in x : Integer;`.

### Schritt 6: Bauen und Regression

Debug-Build, alle `conformance-*` und `conformance-test` laufen lassen, Ergebnis vor/nach vergleichen; Ratchet-Dateien nur
verkleinern, nie erweitern. Das OBD-Modell aus der Metadaten-Aufgabe muss weiter fehlerfrei geparst werden.

## Ablauf

- Umsetzung durch einen Sonnet-Subagenten, Prüfung durch Opus.
- Code, Kommentare und Konsolenausgaben auf Englisch.
- **Keine Commits.**

## Risiken

- **Mehrdeutigkeit `feature` als Name vs. Schlüsselwort:** Abgesichert über die Alternativen-Reihenfolge und den
  Vor/nach-Vergleich in Schritt 3.
- **`anonymous_feature`** (`x : T;` ohne Schlüsselwort) überschneidet sich mit SysML-Referenz-Usages. Durch die Reihenfolge
  gewinnt SysML; der Vergleich in Schritt 3 muss das bestätigen, sonst schmalere Regel (Schritt 1).
- **Parsezeit:** Mehr Alternativen in häufig genutzten Rumpf-Regeln können die SLL-Vorhersage verlangsamen.
