# Implementierungsplan: Python-Paket als `cpp-sysmlv2` auf PyPI veröffentlichen

**Status:** freigegeben am 2026-11-10, umgesetzt und geprüft, noch nicht committet

## Ausgangslage

- `python.yml` baut und testet die Wheels (Linux x86_64/aarch64, Windows x86_64/ARM64, macOS x86_64) und das sdist. Hochgeladen wird nichts.
- Der Name `sysmlv2` ist auf PyPI von einem fremden Platzhalter-Projekt belegt. `cpp-sysmlv2` ist auf PyPI und TestPyPI frei (geprüft am 2026-11-10).
- `pyproject.toml` trägt die Version `0.1.0`, die Tags folgen dem Schema `JJMM.N` (zuletzt `2611.1`, liegt auf dem aktuellen `HEAD`).
- Das macOS-arm64-Wheel ist seit `e550585f` auskommentiert.

## Festgelegte Entscheidungen

| Punkt | Entscheidung |
|---|---|
| Distributionsname | `cpp-sysmlv2`; das Import-Paket bleibt `sysmlv2` |
| Versionsschema | Tag-Schema `JJMM.N` bleibt, `pyproject.toml` wird darauf umgestellt |
| macOS arm64 | Wheel wird wieder gebaut |

## Annahmen, die du mit der Freigabe bestätigst

1. **Kein sdist auf PyPI.** Es werden nur Wheels hochgeladen, weil das sdist ohne Conan-Schritt nicht baubar ist. Das sdist bleibt Anhang des GitHub-Releases.
2. **Upload nur bei Tags, als letzter Schritt.** Der PyPI-Upload läuft erst, wenn alle Builds und das GitHub-Release erfolgreich waren.
3. **Zusätzlicher TestPyPI-Workflow** zum manuellen Probelauf (Punkt 6 unten). Er ist der einzige Weg, Upload und macOS-arm64-Wheel vor dem ersten echten Tag zu prüfen.

## Änderungen

### 1. `pyproject.toml`

- `name = "cpp-sysmlv2"`.
- `version = "2611.1"` mit Kommentar: Schema `JJMM.N` wie die Git-Tags; in der CI überschreibt `set-version.py` den Wert aus dem Tag.
- `[project.urls]` um `Repository` und `Issues` ergänzen.
- Classifier für die Betriebssysteme ergänzen (`Operating System :: POSIX :: Linux`, `:: Microsoft :: Windows`, `:: MacOS`).
- Unverändert bleiben `wheel.packages`, `wheel.install-dir = "sysmlv2"` und der cibuildwheel-Testbefehl, weil der Import-Name gleich bleibt.

### 2. `python/src/sysmlv2/__init__.py`

- `_version("sysmlv2")` wird zu `_version("cpp-sysmlv2")`. Sonst wäre `__version__` nach der Installation immer `0+unknown`.

### 3. `python/README.md` (wird die Projektseite auf PyPI)

- Titel auf `cpp-sysmlv2`, direkt darunter ein Abschnitt „Installation“ mit `pip install cpp-sysmlv2` und dem Hinweis, dass weiterhin `import sysmlv2` gilt.
- Liste der Plattformen mit fertigem Wheel; Hinweis, dass es kein sdist auf PyPI gibt.
- Wheel-Muster im Testbefehl (Zeile 106): `dist/sysmlv2-*.whl` wird zu `dist/cpp_sysmlv2-*.whl`.

### 4. `python/tools/conan_deps.py`

- Nur der Kopftext der erzeugten `THIRD_PARTY_LICENSES.txt`: „the sysmlv2 package“ wird zu „the cpp-sysmlv2 package“.

### 5. `.github/workflows/python.yml`

- Matrix-Zeile `macos-arm64` (`macos-14`, `arm64`, `armv8`, Deployment `11.0`) wieder aktivieren, den Zusatz „Currently not supported“ entfernen.
- Die auskommentierte `publish-pypi`-Vorlage am Dateiende entfernen. Trusted Publishing prüft den aufrufenden Workflow, der Job gehört deshalb nach `tagbuild.yml`.
- Kopfkommentar anpassen: Veröffentlicht wird in `tagbuild.yml` und `testpypi.yml`.
- Die Artefaktnamen `sysmlv2-wheels-*` und `sysmlv2-sdist` bleiben, damit der `release`-Job unverändert funktioniert.

### 6. `.github/workflows/tagbuild.yml`: neuer Job `publish-pypi`

- `needs: [release]`, `environment: pypi`, `permissions: id-token: write`.
- Lädt nur `sysmlv2-wheels-*` nach `dist/`.
- **Prüfschritt vor dem Upload:** Der Tag muss eine gültige PEP-440-Version sein, und jede Datei in `dist/` muss `cpp_sysmlv2-<Version>-…whl` heißen. Sonst bricht der Job ab. Hintergrund: `set-version.py` behält bei einem ungültigen Tag stillschweigend die Version aus `pyproject.toml`; ohne die Prüfung würde dann eine falsche Version unwiderruflich hochgeladen.
- Upload mit `pypa/gh-action-pypi-publish@release/v1`, ohne Token.

### 7. Neue Datei `.github/workflows/testpypi.yml`

- Auslöser nur `workflow_dispatch` mit Pflichteingabe `version` (z. B. `2611.2.dev1`).
- Ruft `python.yml` mit dieser Version auf und lädt die Wheels mit `repository-url: https://test.pypi.org/legacy/` hoch (`environment: testpypi`, derselbe Prüfschritt wie in Punkt 6).

## Nicht Teil dieses Plans

- **`mainbuild.yml`:** Der Main-Build übergibt weiter `1.0-main` (Wheel-Version `1.0.dev0`). Diese Wheels werden nicht veröffentlicht. Die Kennung passt nicht zum Schema `JJMM.N`; eine Umstellung beträfe auch das Conan- und das WASM-Paket.
- **`set-version.py`:** bleibt unverändert, die Absicherung sitzt im Publish-Job.
- **musllinux-Wheels** (Alpine) und **C++-Code**.
- **Bereits veröffentlichtes `2611.1`:** Der Tag existiert schon. Die erste Version auf PyPI wird der nächste Tag.

## Was du außerhalb des Repositorys einrichten musst

| Wo | Was |
|---|---|
| pypi.org → Publishing | Pending Publisher: Projekt `cpp-sysmlv2`, Owner `Protestator-Research`, Repo `CPP-SysMLv2`, Workflow `tagbuild.yml`, Environment `pypi` |
| test.pypi.org → Publishing | Dasselbe mit Workflow `testpypi.yml`, Environment `testpypi` |
| GitHub → Settings → Environments | `pypi` (am besten mit „Required reviewers“) und `testpypi` |

## Risiken

- **macOS arm64 ist ungeprüft.** Der Grund für die Deaktivierung ist nicht dokumentiert. Im letzten Lauf mit aktivem arm64-Job (`3d1700c0`) wurde er abgebrochen, während alle anderen Wheels aus einem inzwischen behobenen Grund scheiterten; ein eigener arm64-Fehler ist also nie beobachtet worden. Seitdem kam der macOS-Fix `849827bb` dazu, und `build-macos` in `tagbuild.yml` (arm64) läuft für `2611.1` durch.
- **Offener macOS-Fehler in `build.yml`.** Dort scheitert `build-macos` (arm64, `with_check=True`) auf `54f341af` im Schritt `build sysmlv2lib`. Das Wheel baut denselben Check-Code, allerdings ohne Tests. Ob der Fehler das Wheel betrifft, zeigt erst der CI-Lauf; die Logs kann ich ohne GitHub-Anmeldung nicht lesen. Scheitert der arm64-Job, brauche ich den Log.
- **Uploads sind endgültig.** Eine Versionsnummer lässt sich auf PyPI nie ein zweites Mal vergeben, auch nicht nach dem Löschen.
- **Der Pending Publisher reserviert den Namen nicht.** Bis zum ersten Upload kann jemand anderes `cpp-sysmlv2` belegen.

## Umsetzung und Prüfung

1. Ein Sonnet-Agent setzt die Punkte 1 bis 7 um. Code, Kommentare und Workflow-Texte bleiben englisch.
2. Ein Opus-Agent prüft den Diff gegen diesen Plan. Zusätzlich wird geprüft:
   - `pyproject.toml` und alle geänderten Workflow-Dateien lassen sich parsen (TOML, YAML).
   - Im Repository steht kein veralteter Verweis auf den Distributionsnamen `sysmlv2` mehr (Import-Name und Artefaktnamen ausgenommen).
   - Der Prüfschritt aus Punkt 6 lehnt einen ungültigen Tag und einen falsch benannten Wheel-Namen ab (lokal mit Beispieldateien).
   - `python/tests/test_protocol.py` läuft weiter aus dem Checkout.
3. Es wird nichts committet und nichts gepusht.

**Grenze der Prüfung:** Wheel-Builds, der macOS-arm64-Job und der Upload lassen sich lokal nicht ausführen. Das zeigt erst ein Lauf von `testpypi.yml` nach deinem Push, sobald die Einrichtung aus der Tabelle oben steht.

## Empfohlene Reihenfolge nach der Umsetzung

1. Änderungen prüfen, committen und pushen.
2. Environments und Pending Publisher anlegen.
3. `testpypi.yml` mit einer Testversion starten und `pip install -i https://test.pypi.org/simple/ cpp-sysmlv2` ausprobieren.
4. Den nächsten Tag (z. B. `2611.2`) pushen; `tagbuild.yml` veröffentlicht dann auf PyPI.
