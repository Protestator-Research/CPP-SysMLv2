# Implementierungsplan: REST-Klassen an den Standard angleichen

Stand: 2026-10-25, Branch `AddingJsonParsingToAllElements`.
Status: **Entwurf, wartet auf Freigabe.** Nichts wird committet.

Grundlage: *Systems Modeling API and Services v1.1 Beta 2*, Kap. 7.1 (PIM-Modell), Kap. 8.1 (REST/HTTP PSM), Annex B (JSON-Beispiele).
Die OpenAPI-Datei wird nicht geprüft.

Ausführung: **Sonnet-Runner** setzen die Arbeitspakete (AP) nacheinander um. Nach jedem AP prüft ein **Opus-Reviewer** (🔍) den Diff gegen diesen Plan und den Standard.
Ein AP gilt erst nach bestandenem Review als fertig; Befunde gehen an denselben Sonnet-Runner zurück.

---

## 1. Ergebnis der Prüfung „JSON für alle Elemente“

| Bereich | JSON lesen/schreiben | Bemerkung |
|---|---|---|
| KerML-Metaklassen (78) | ✅ vollständig | `kerml/tools/generate_json.py --check` → verified |
| SysML-Metaklassen (93, davon 89 konkret) | ✅ vollständig | `sysml/tools/generate_abstract_syntax.py --check` → 203 Dateien verified |
| KerML-Alt-Stubs `ItemFlow`, `ItemFeature`, `ItemFlowEnd`, `SuccessionItemFlow`, `Featuring` | – | Leere Klassen aus alten KerML-Namen (heute `Flow`, `PayloadFeature`, `FlowEnd`, `SuccessionFlow`), keine `Element`-Unterklassen. **Kein JSON nötig**, bleiben unverändert. |
| REST: `Project`, `Commit`, `Branch`, `Tag`, `CommitReference`, `DataIdentity`, `DataVersion`, `Query`, `ProjectUsage`, `ExternalData`, `ExternalRelationship`, `CommitRequest`, `ProjectRequest`, `BranchRequest`, `Identification` | ⚠️ vorhanden, aber fehlerhaft | siehe AP 1–4 |
| REST: `DataDifference`, `MergeResult` | ❌ fehlt | kein `IEntity`, kein JSON |
| REST: `PrimitiveConstraint`, `CompositeConstraint` (+ `Operator`, `JoinOperator`) | ❌ Klassen fehlen | |
| REST: `TagRequest`, `QueryRequest` | ❌ Klassen fehlen | |
| REST-Enums `ChangeType`, `Direction` | ❌ keine String-Abbildung | REST-Werte `CREATED/UPDATED/DELETED`, `in/out/both` |
| `SysMLv2Deserializer` | ⚠️ unvollständig | kennt `DataVersion`, `ExternalData`, `ExternalRelationship`, `ProjectUsage`, `DataDifference`, Constraints nicht |

## 2. Entscheidungen (bitte mit freigeben)

**E1 – Gemeinsame JSON-Hilfen statt verstreuter `try/catch`.**
Neuer privater Header `rest-api/src/sysmlv2/rest/entities/RestJson.h` (nicht installiert) mit:
`looksLikeJson`, `readOptionalString` (fehlend/`null` → leer), `readReference`/`writeReference` (`{"@id": …}`, `null` erlaubt), `readReferences` (Array, Einzelobjekt oder `null`), `readTimestamp`/`readOptionalTimestamp`.

**E2 – „JSON oder Name“ nur noch über `looksLikeJson`.**
Beginnt der String mit `{` → striktes Parsen; Fehler werfen `std::invalid_argument` mit Klassennamen. Sonst → Name/Beschreibung.
Kein `catch(...)`, der Fehler verschluckt oder JSON-Text als Namen speichert; keine zufällige Ersatz-Id mehr. (Gleiches Muster wie KerML.)

**E0 – Kompatibilität mit Warnung (gilt für alle folgenden Punkte).**
Jede bisherige öffentliche API und jedes bisher geschriebene/gelesene JSON-Format bleibt nutzbar. Wird eine alte Variante verwendet, erscheint auf der Konsole (`std::cerr`) ein Hinweis, dass eine alte Version der Bibliothek benutzt wird.
- Neuer Header `rest-api/include/sysmlv2/rest/Deprecation.h` mit `SysMLv2::REST::warnDeprecated(what, replacement)`.
- Ausgabe **einmal pro Meldung** je Programmlauf (kein Spam in Schleifen), thread-sicher, Text englisch wie die übrigen Meldungen im Code, z. B.:
  `[SysMLv2 REST] Deprecated: ProjectRequest(name, description, "main") is from an older library version. Use ProjectRequest(name, description, std::optional<uuid>) instead.`
- Alte Methoden/Konstruktoren bekommen zusätzlich `[[deprecated("…")]]`, damit der Compiler ebenfalls warnt. Der eigene Code (`services`, `rest-api`) wird auf die neuen Varianten umgestellt und löst keine Warnungen aus.
- Beim Lesen alter JSON-Felder (`timestamp`, `previousCommit`, `usedCommit`, `order`, `dataVersions`, `"@type": "CommitRequest"`, `defaultBranch` als String) wird der Wert übernommen und ebenfalls gewarnt.

**E3 – Schreiben nach PIM, Lesen tolerant.**
Geschrieben werden die PIM-Namen: `created`, `previousCommits`, `orderBy`, `usedProjectCommit`, `taggedCommit` usw. – außer wenn eine alte API benutzt wird, die nur das alte Format erzeugen kann (siehe E8).
Gelesen werden zusätzlich die alten Namen (Annex B und frühere Versionen dieser Bibliothek) mit Warnung nach E0. Die bestehenden Tests mit `"timestamp"` bleiben damit grün.

**E4 – Zeitstempel immer mit `Z`.**
`Utilities::toIso8601` hängt `Z` an (UTC, Kap. 7.1.2). `deleted` wird als `std::optional` geführt und nur geschrieben, wenn gesetzt.

**E5 – `DataVersion`: neue API, alte bleibt mit Warnung.**
Neu: `DataVersion(std::shared_ptr<Data> payload, std::shared_ptr<DataIdentity> identity = nullptr, uuid id = random)`.
`id` = neue zufällige UUID; `identity` = übergeben oder `DataIdentity(payload->getId())`; `payload == nullptr` = Löschen (`"payload": null`).
Neue Getter: `getVersionId()` (Id der DataVersion) und `getIdentity()`.
Alt und weiter nutzbar (mit Warnung):
- `DataVersion(uuid, payload)`: der UUID wird als Identity-Id gedeutet, wenn `payload == nullptr` (behebt den heutigen Absturz), sonst wie bisher die Payload-Id.
- `DataVersion::getId()` behält seine bisherige Bedeutung (Id der Daten = Identity-Id) und stürzt bei `payload == nullptr` nicht mehr ab.
Die Aufrufer in `ProjectUsageService.cpp`, `ElementNavigationService.cpp` und `ProjectVersioningService.cpp` werden auf die neue API umgestellt.

**E6 – `owningProject` wandert von `Tag` nach `CommitReference`** (gilt so für Branch und Tag). `Tag.taggedCommit` und `Branch.head` sind mit `referencedCommit` synchron. `setReferencedCommit` wird `protected` (Tag ist unveränderlich).

**E7 – `MergeResult` folgt Tabelle 9:** Die REST-Antwort ist entweder ein `Commit` (Erfolg) oder ein Array von `DataIdentity` (Konflikte). `MergeResult` bekommt `fromJson(...)`, das beide Formen erkennt, und `serializeToJson()` in derselben Form.

**E8 – `ProjectRequest.defaultBranch` als Branch-Id.**
Neu: `ProjectRequest(name, description, std::optional<uuid> defaultBranch)` schreibt `{"@id": …}` (setDefaultBranch, Kap. 8.1.3); ohne Branch-Id fehlt das Feld.
Alt und weiter nutzbar (mit Warnung): `ProjectRequest(name, description, "main")` und `defaultBranch()` als String. Ein Branch-**Name** lässt sich nicht in eine Id umrechnen, deshalb schreibt diese alte Variante weiterhin `"defaultBranch": "main"`.
Die bestehenden Tests `SerializeProjectRequest`/`DeserializeProjectRequest` bleiben unverändert und grün; neue Tests decken das Standardformat ab.

**Weitere alte APIs, die mit Warnung erhalten bleiben:** `DataDifference::comparedData()` (neu `compareData()`), `Commit::getPreviusCommits()`/`getDataVersion()` (neu `getPreviousCommits()`/`getChange()`), `Tag::setReferencedCommit` (Tag ist unveränderlich; der Aufruf funktioniert noch, warnt aber), `Query`-Konstruktor mit `order` (neu `orderBy`), `ProjectUsage`-Feld `usedCommit`.

**E9 – Nicht Teil dieser Aufgabe** (nur notiert): `SysMLAPIImplementation::postProject` schickt ein vollständiges `Project` statt eines `ProjectRequest`; Endpunkte und Pagination liegen außerhalb des `rest`-Ordners.

## 3. Arbeitspakete

Build/Test nach jedem AP: `cmake --build build/Debug -j` und `ctest --test-dir build/Debug -R conformance-regression --output-on-failure`.

### AP 0 – Grundlagen
Dateien: `Utilities.cpp`, `JSONEntities.h`, neu `RestJson.h`, neu `Deprecation.h/.cpp`, `Record.h/.cpp`.
- `warnDeprecated` nach E0.
- `toIso8601` mit `Z` (Fehler 17).
- Konstanten: `previousCommits`, `orderBy`, `where`, `usedProjectCommit`, `usedProject`, `taggedCommit`, `elementEnd`, `externalDataEnd`, `baseData`, `compareData`, `createdAt`, `deletedAt`, `commit`, `inverse`, `property`, `operator`, `value`, `constraint`; alte Konstanten bleiben für das tolerante Lesen.
- `Record`: `null`-sicher (1), `@id` optional bei Requests (2), `resourceIdentifier` (19), `setName` pflegt `alias`, leere Namen nicht in `alias` (19), E2.
- 🔍 Opus

### AP 1 – Versionierung
Dateien: `Project`, `ProjectRequest`, `Commit`, `CommitReference`, `Branch`, `Tag`, `BranchRequest`, `CommitRequest`, neu `TagRequest`.
- `Project`: `created`, Default-Branch in `branches` ohne Duplikate, `serializeToJson` ohne Absturz bei fehlendem Branch (18).
- `ProjectRequest` nach E8 (12).
- `Commit`: `created`, `previousCommits` lesen/schreiben nach E3, kein Absturz bei fehlendem `owningProject` (7, 8).
- `CommitReference`: optionales `deleted` (9), `owningProject` (E6), `null`-sichere Serialisierung.
- `Branch`: `owningProject`, `head` ↔ `referencedCommit` synchron (11).
- `Tag`: `@type "Tag"`, `taggedCommit`, unveränderlich (10, 26).
- `BranchRequest`: `head` Pflicht (25).
- `CommitRequest`: `@type "Commit"`, optionale `description`, `previousCommits`, Änderungen über `DataVersion::serializeAsRequest()` (13). *(Hängt von AP 2 ab → `CommitRequest` wird erst am Ende von AP 2 fertiggestellt.)*
- Neu `TagRequest` (`@type "Tag"`, `name`, `taggedCommit`) (21).
- 🔍 Opus

### AP 2 – Daten
Dateien: `DataIdentity`, `DataVersion`, `DataDifference`, `MergeResult`, `ProjectUsage`, `ExternalData`, `ExternalRelationship`, Aufrufer in `services` (E5), danach `CommitRequest` fertigstellen.
- `DataIdentity`: nur Record-Felder + optionale `createdAt`/`deletedAt` als Commit-Referenzen; minimales `{"@id","@type"}` lesbar (6).
- `DataVersion` nach E5, `identity` lesen/schreiben, optionales `commit`, `serializeAsRequest()` ohne `@id` (3, 4, 5).
- `DataDifference`: `IEntity`, `@type "DataDifference"`, `baseData`/`compareData` (Getter `compareData()`, `comparedData()` bleibt als Alias) (20).
- `MergeResult` nach E7 (20).
- `ProjectUsage`: `@type`, `usedProjectCommit` als Referenz, `usedProject` lesen/schreiben, kein Absturz in `getUsedProject()` (14).
- `ExternalData`: `@type`, IRI-Konstruktor ohne Exception; dafür bekommt `Data` (sysmlinterfaces) einen geschützten Konstruktor `Data(uuid, type)` – `Data(std::string)` bleibt unverändert, da KerML ihn nutzt (23).
- `ExternalRelationship`: `@type`, `elementEnd`, `externalDataEnd`, optionale `specification`/`language` (15, 24).
- 🔍 Opus

### AP 3 – Abfragen und Enums
Dateien: `Query`, neu `Constraint.h/.cpp` (`Constraint`, `PrimitiveConstraint`, `CompositeConstraint`, `Operator`, `JoinOperator`), neu `QueryRequest`, `ChangeType.h`, `Direction.h`.
- `Query`: `orderBy`, `where`, `owningProject`, `scope` als Referenzen, keine verschluckten Fehler (16).
- `PrimitiveConstraint`: `inverse`, `property`, `operator` (`instanceOf`, `=`, `<`, `<=`, `>`, `>=`, `in`), `value` (beliebiger JSON-Wert/Array); `CompositeConstraint`: `operator` (`and`/`or`), `constraint` (≥ 2). Fabrik `Constraint::fromJson` über `@type`.
- `QueryRequest` (Query ohne `@id`).
- `toString`/`fromString` für `ChangeType` und `Direction` (27).
- 🔍 Opus

### AP 4 – Deserializer und Tests
Dateien: `SysMLv2Deserializer.cpp`, `CMakeLists.txt`, neu `conformance-test/src/TestRestEntities.cpp`, Anpassung `TestRestAPI.cpp`.
- Deserializer kennt alle REST-Typen, `null` → `nullptr` (22).
- Neue Tests je REST-Klasse: Round-Trip, Lesen der Annex-B-Beispiele (inkl. `null`-Werte, `previousCommit` als Objekt/`null`), Löschen per `payload: null`, ungültiges JSON wirft, Zeitstempel enden auf `Z`.
- Kompatibilitätstests: jede alte API/jedes alte JSON-Feld funktioniert weiter und erzeugt genau eine Warnung auf `stderr` (geprüft mit `testing::internal::CaptureStderr`); die neuen APIs erzeugen keine.
- Die bestehenden Tests in `TestRestAPI.cpp` und `TestBranchRequest.cpp` bleiben unverändert.
- 🔍 **Abschluss-Review Opus** über den gesamten Diff gegen die Fehlerliste 1–28.

## 4. Abnahmekriterien
- Alle 28 Punkte der Fehlerliste sind behoben oder hier begründet ausgenommen (E9).
- Bestehender Code, der die alten APIs nutzt, kompiliert und läuft weiter; er erzeugt nur Deprecation-Warnungen (Compiler + Konsole).
- Build des eigenen Codes ohne neue Warnungen; alle `ctest`-Tests grün, bestehende Tests unverändert.
- KerML/SysML-Generatoren weiterhin `--check` → verified.
- Kein Commit ohne deine Freigabe.

---

## Anhang A – Fehlerliste (Referenz für Runner und Reviewer)

Pfade relativ zu `rest-api/src/sysmlv2/rest/` bzw. `sysmlinterfaces/`.

**Kritisch**
1. `Record::deserializeAndPopulate`: `"name": null` / `"description": null` werfen; der `catch` im Konstruktor setzt dann `Name` = ganzer JSON-Text und eine zufällige Id.
2. `Record` verlangt immer `@id`; Requests ohne `@id` landen im selben Rückfall.
3. `DataVersion`: Pflichtfeld `identity` fehlt (lesen/schreiben).
4. `DataVersion(uuid, payload)`: `id` ignoriert, Id = `payload->getId()`. Standard: DataVersion.id neu/zufällig, DataIdentity.id = Data.getId().
5. `DataVersion` mit `payload == nullptr` (Löschen) stürzt ab: Konstruktor, `serializeToJson`, Lesen von `"payload": null`, `getId()`.
6. `DataIdentity`: schreibt erfundene Felder `dataVersions`, `created`, `deleted` (Zeitstempel); Standard: `createdAt`/`deletedAt` = abgeleitete Commit-Verweise. Minimales `{"@id","@type":"DataIdentity"}` wirft beim Lesen.
7. `Commit.previousCommit`: erwartet Array; Annex B liefert Objekt oder `null` → wirft. PIM-Name `previousCommits`.
8. Commit-Zeitfeld `timestamp` statt `created` (CommitReference nutzt `created`).
9. `CommitReference.deleted` wird immer geschrieben (`time_point::min()` bzw. 1970).
10. `Tag`: `@type` wird `"CommitReference"`; `taggedCommit` fehlt.
11. `Branch`: `owningProject` fehlt; `head` ↔ `referencedCommit` nicht synchron; `serializeToJson` stürzt ohne Head/ReferencedCommit ab.
12. `ProjectRequest.defaultBranch` als Name `"main"` statt Branch-Id `{"@id"}`; `description`/`defaultBranch` beim Lesen Pflicht.
13. `CommitRequest`: `@type "CommitRequest"` statt `"Commit"`; `previousCommits` fehlt; fehlende `description` → ganzer JSON-Text landet in `Description`.
14. `ProjectUsage`: `usedCommit` statt `usedProjectCommit`; Commit als escapter String statt `{"@id"}`; Lesen ignoriert das Feld → `getUsedProject()` stürzt ab; `usedProject` fehlt.
15. `ExternalRelationship`: `elementEnd`, `externalDataEnd` fehlen.
16. `Query`: `order` statt `orderBy`; `where` + Constraint-Klassen fehlen; `owningProject` fehlt; `scope` wird nicht gelesen; `catch(...)` verschluckt Fehler.
17. `Utilities::toIso8601` ohne Zeitzone (`Z`).

**Fehlende Teile**
18. `Project`: `created` fehlt; Default-Branch nicht in `Branches` bzw. Duplikate durch `setDefaultBranch`; `serializeToJson` stürzt ohne Default-Branch ab.
19. `Record`: `resourceIdentifier` fehlt; `setName` pflegt `alias` nicht; leerer Name als `""` in `alias`.
20. `DataDifference`, `MergeResult`: kein JSON, kein `@type`; Getter `comparedData` statt `compareData`.
21. `TagRequest`, Query-Request fehlen.
22. `SysMLv2Deserializer` kennt `DataVersion`, `ExternalData`, `ExternalRelationship`, `ProjectUsage`, `DataDifference`, Constraints nicht.
23. `ExternalData(IRI)` wirft immer (Basis `Data(std::string)` erwartet JSON); `@type` nie gesetzt; ebenso bei `ExternalRelationship`.
24. `ExternalRelationship`: `specification`/`language` optional, beim Lesen aber Pflicht; schreibt `""` statt wegzulassen.

**Klein**
25. `BranchRequest`: `head` optional, obwohl `createBranch` ihn verlangt.
26. `Tag` veränderbar (`setReferencedCommit` öffentlich).
27. `Direction`/`ChangeType` ohne String-Abbildung (`in/out/both`, `CREATED/UPDATED/DELETED`).
28. „JSON oder Name“ mit `catch(...)` in Record, Branch, Tag, CommitRequest, Query verschluckt Fehler.

## Anhang B – Regeln für die Runner
- Code, Kommentare, Meldungen: **Englisch**. Stil des umgebenden Codes übernehmen.
- **Nichts committen**, keine Branches wechseln, kein `git stash`/`reset`.
- Nur die Dateien des eigenen AP anfassen (plus `CMakeLists.txt`, falls neue Dateien).
- Nach dem AP: Build + `conformance-regression` grün; Ergebnis (geänderte Dateien, Testausgabe) berichten.
