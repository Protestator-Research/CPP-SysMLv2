# Implementierungsplan: Metadaten-Verwendungen im SysML-v2-Parser

## Ausgangslage

Jede Metadaten-Verwendung (`metadata X;`, `metadata X { … }`, `@X …`) scheitert beim Parsen von SysML v2,
z. B. mit `mismatched input '{' expecting 'about'`. Die Präfix-Form `#X` ist nicht betroffen.

### Ursachen

| # | Datei | Problem |
|---|-------|---------|
| 1 | `filehandling/resources/grammars/SysMLv2.g4:42` | `annotating_element` verweist auf die importierte KerML-Regel `metadata_feature` statt auf die SysML-Regel `metadata_usage`. `metadata_usage` (Zeile 528) wird nirgends referenziert (tote Regel). |
| 2 | `filehandling/resources/grammars/KerML.g4:359` | `metadata_feature` ist fehlerhaft: der `about`-Teil ist Pflicht (fehlendes `?`), die Komma-Liste hat kein `*`, und `metadata_body` fehlt ganz. Betrifft auch den reinen KerML-Parser (`.kerml`). |
| 3 | `filehandling/resources/grammars/SysMLv2.g4:530` | `metadata_body` erlaubt genau ein Element zwischen `{` und `}` (fehlendes `*`). |

### Spezifikation (SysML v2 / KerML Textual Notation)

```
MetadataUsage   = UsageExtensionKeyword* ( '@' | 'metadata' ) MetadataUsageDeclaration
                  ( 'about' Annotation ( ',' Annotation )* )? MetadataBody
MetadataBody    = ';' | '{' ( DefinitionMember | MetadataBodyUsageMember | AliasMember | Import )* '}'
MetadataBodyUsage = 'ref'? ( ':>>' | 'redefines' )? OwnedRedefinition
                    FeatureSpecializationPart? ValuePart? MetadataBody

MetadataFeature = PrefixMetadataMember* ( '@' | 'metadata' ) MetadataFeatureDeclaration
                  ( 'about' Annotation ( ',' Annotation )* )? MetadataBody
```

## Randbedingung: KerML-Elemente in SysML v2 bleiben erlaubt

Die Grammatik `SysMLv2.g4` importiert `KerML.g4`. Alle KerML-Konstrukte, die heute in SysML-Texten akzeptiert werden
(z. B. `function`, `feature`, `classifier`, `in feature x : T;`), bleiben unverändert erlaubt. Es wird **keine** KerML-Regel aus
dem SysML-Parser entfernt.

Für Metadaten gilt: Die textuelle Syntax von `metadata_feature` (KerML) ist eine Teilmenge von `metadata_usage` (SysML):
`#X` ↔ `#X`, `:`/`typed by` ↔ `:`/`defined by`. Wenn `annotating_element` in SysML auf `metadata_usage` zeigt, wird jeder
KerML-geschriebene Metadaten-Text weiterhin geparst. Erzeugt wird dann eine `SysMLv2::Entities::MetadataUsage`. Das ist
korrekt, weil `MetadataUsage` von `KerML::Entities::MetadataFeature` erbt und in SysML die richtige Metaklasse ist. Beide
Regeln als Alternativen nebeneinander würden nur eine Mehrdeutigkeit erzeugen, die ANTLR ohnehin zugunsten der ersten auflöst.

## Schritte

### Schritt 1: Grammatik korrigieren

1. `KerML.g4`: `metadata_feature` gemäß Spezifikation:
   ```antlr
   metadata_feature: (prefix_metadata_member)* (SYMBOL_AT | KEYWORD_METADATA) metadata_feature_declaration
                     (KEYWORD_ABOUT annotation (SYMBOL_COMMA annotation)*)? metadata_body;
   ```
2. `SysMLv2.g4`:
   - `annotating_element: comment | documentation | textual_representation | metadata_usage;`
   - `metadata_body: SYMBOL_STATEMENT_DELIMITER | SYMBOL_CURLY_BRACKET_OPEN (definition_member | metadata_body_usage_member | alias_member | namespace_import)* SYMBOL_CURLY_BRACKET_CLOSE;`
   - Die Regel `metadata_feature` bleibt über den Import vorhanden (für Kompatibilität des Listeners/Visitors); sie wird in SysML
     nur nicht mehr von `annotating_element` aus erreicht.
3. Prüfen, dass `metadata_usage` keine Linksrekursion/Mehrdeutigkeit mit `usage_element`/`definition_element` erzeugt, z. B.
   durch `usage_extention_keyword*` vor `metadata` (Präfix `#X metadata Y …`) gegenüber `#X attribute …`.

### Schritt 2: Parser neu erzeugen

Mit `tools/antlr-4.13.2-complete.jar` (gleiche Version wie die vorhandenen generierten Dateien), Zielsprache C++,
mit `-listener -visitor`, `-lib` auf das Grammatik-Verzeichnis (wegen `import KerML;`).

- SysML: Ausgabe nach `filehandling/src/sysmlv2/parser/`, Header nach `filehandling/include/sysmlv2/parser/` verschieben
  (so wie heute abgelegt).
- KerML: Ausgabe nach `filehandling/src/kerml/parser/`, Header nach `filehandling/include/kerml/parser/`.
- Vor dem Generieren den Kopf der vorhandenen generierten Dateien prüfen (Include-Pfade, `@header`, Export-Makros), damit das
  Ergebnis genau so aussieht wie bisher. Der Diff der generierten Dateien darf nur die geänderten Regeln betreffen.
- Das unversionierte Verzeichnis `filehandling/resources/grammars/gen/` (Java-Ausgabe eines früheren Laufs) wird nicht
  angefasst und nicht verwendet.

### Schritt 3: SysML-Listener für `metadata_usage` vervollständigen

`SysMLv2ListenerImplementation.cpp`: `Metadata_usage` hat bisher nur das generische `DEFINE_USAGE_METHODS`, weil die Regel nie
erreicht wurde. Ergänzen (nach Vorbild von `enterPrefix_metadata_usage`/`exitPrefix_metadata_usage` und der `comment`-Behandlung
mit `about`):

- Name aus `metadata_usage_declaration` (`identification`), falls angegeben.
- Typisierung aus `owned_feature_typing` → `addTyping(...)`; die Metadaten-Definition wird über den bestehenden Resolver
  (`setMetadataDefinition`) gesetzt.
- Annotierte Elemente:
  - mit `about`: jedes `annotation` wie beim Kommentar über den `Recorder` auflösen und `appendAnnotatedElement` aufrufen;
  - ohne `about`: der besitzende Namensraum ist das annotierte Element.
- Mitgliedschaft wie bei der Präfix-Form: `OwningMembership` (Metadaten sind keine Features ihres Besitzers).
- Rumpf: `metadata_body_usage` (`serviceId = 1;`) erzeugt eine `ReferenceUsage`, die das gleichnamige Feature der
  Metadaten-Definition redefiniert (`owned_redefinition` → `addRedefinition`) und den Wert aus `value_part` erhält. Prüfen, ob das
  bestehende `DEFINE_USAGE_METHODS(Metadata_body_usage, …)` Redefinition und Wert bereits verarbeitet; sonst ergänzen.
  Die Auflösung des redefinierten Namens erfolgt im Kontext der Metadaten-Definition (Typ der `MetadataUsage`).
- `enterMetadata_feature`/`exitMetadata_feature` bleiben bestehen (werden in SysML nicht mehr erreicht, schaden aber nicht).

### Schritt 4: KerML-Listener prüfen

`KerMlListenerImplementation.cpp` (`enterMetadata_feature` ff.): Durch den neuen `metadata_body` in `metadata_feature` können
Rumpf-Elemente (`metadata_body_element`) auftreten. Prüfen, dass sie dem `MetadataFeature` zugeordnet werden und kein Absturz
entsteht; `about`-Ziele analog zu oben.

### Schritt 5: Tests

Neue Testdateien im Conformance-Ratchet (`conformance-test/testdata/syntax/…`, Kopfzeile `// expect: valid`):

- `sysml/valid/metadata_usage_semicolon.sysml` — `metadata M;`
- `sysml/valid/metadata_usage_at.sysml` — `@M;` und `@M { … }`
- `sysml/valid/metadata_usage_body.sysml` — mehrere Zuweisungen im Rumpf, inkl. Enum-Wert (`trigger = ObdTrigger::Startup;`)
- `sysml/valid/metadata_usage_about.sysml` — `metadata M about A, B;`
- `sysml/valid/metadata_usage_named.sysml` — `metadata m : M;` und `metadata m defined by M;`
- `sysml/valid/metadata_usage_kerml_style.sysml` — KerML-Schreibweise im SysML-Text, plus `function`/`in feature` (Absicherung der
  Randbedingung)
- `kerml/valid/metadata_feature_body.kerml` — `metadata M about x { … }` und `metadata M;`
- `sysml/negative/metadata_usage_missing_type.sysml` — `metadata ;`

Zusätzlich in `TestSysMLParser.cpp` ein Test mit dem Modell aus der Anfrage (OBD/`SUPPORTED_PIDS_01_20`), der prüft:
keine Parserfehler, eine `MetadataUsage` vom Typ `ObdSignal`, annotiert `SUPPORTED_PIDS_01_20`, mit vier redefinierenden Features
und den Werten `1`, `0`, `ObdTrigger::Startup`, `1`.

### Schritt 6: Bauen und Regression

- Debug-Build (`build/Debug`), alle `conformance-*`-Ziele und `conformance-test` laufen lassen.
- Keine neuen Fehler gegenüber `expected_failures.txt`, `expected_unresolved.txt`, `expected_xmi_diffs.txt`. Falls Einträge durch den
  Fix nun bestehen, Ratchet-Dateien entsprechend verkleinern.
- Standardbibliothek (`resources/sysml.library`) muss weiter fehlerfrei geparst werden.

## Ablauf

- Umsetzung durch einen Sonnet-Subagenten (Schritte 1–6, nacheinander).
- Prüfung des Ergebnisses durch Opus (Grammatik-Diff, Listener-Logik, Testergebnisse).
- Code, Kommentare und Konsolenausgaben auf Englisch.
- **Keine Commits.**

## Risiken

- Neue Mehrdeutigkeiten durch `usage_extention_keyword*` vor `metadata`/`@` in Rümpfen; ggf. ANTLR-Warnungen beim Generieren
  beachten.
- Die generierten Parser-Dateien sind groß; ein abweichender ANTLR-Aufruf (Version, Optionen, Ablageort) würde einen riesigen,
  schwer prüfbaren Diff erzeugen.
- Die Redefinitions-Auflösung im Metadaten-Rumpf hängt vom Typ der `MetadataUsage` ab; bei unaufgelöstem Typ entstehen
  Warnungen statt Fehler.
