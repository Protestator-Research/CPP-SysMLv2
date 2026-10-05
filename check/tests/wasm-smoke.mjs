// Smoke test of the WebAssembly module of sysmlv2check, run with Node (>= 18):
//   node check/tests/wasm-smoke.mjs [path/to/sysmlv2check.js]      (default: build/wasm/out/sysmlv2check.js, or $SYSMLV2CHECK_WASM)
// Same cases as check/tests/TestCheck.cpp (valid model, syntax error, unresolved name, required element, library import, limits,
// timeout, STRUKTUR). Prints timings (module start, warm-up of the whole library, warm request).
import assert from 'node:assert/strict';
import { performance } from 'node:perf_hooks';
import { fileURLToPath, pathToFileURL } from 'node:url';
import path from 'node:path';

const here = path.dirname(fileURLToPath(import.meta.url));
const modulePath = path.resolve(process.argv[2] ?? process.env.SYSMLV2CHECK_WASM ?? path.join(here, '../../build/wasm/out/sysmlv2check.js'));
const createSysmlCheck = (await import(pathToFileURL(modulePath).href)).default;

const t0 = performance.now();
const mod = await createSysmlCheck();
const tStart = performance.now() - t0;

const call = (fn, arg) => {
  const ptr = mod.ccall(fn, 'number', ['string'], [arg]);
  return ptr;
};
const pruefe = (request) => {
  const ptr = call('sysml_pruefe', JSON.stringify(request));
  assert.notEqual(ptr, 0, 'no response');
  const text = mod.UTF8ToString(ptr);
  mod._sysml_freigeben(ptr);
  return JSON.parse(text);
};
const select = (r, kategorie, quelle) => r.diagnosen.filter((d) => d.kategorie === kategorie && (!quelle || d.quelle === quelle));

let n = 0;
const test = (name, fn) => {
  fn();
  n++;
  console.log('ok -', name);
};

const VALID = 'package Fahrzeuge {\n  part def Auto;\n  part def Rad;\n  part auto : Auto {\n    part raeder : Rad [4];\n  }\n}\n';

test('valid model: no diagnoses, elements listed', () => {
  const r = pruefe({ quelltext: VALID, id: 7 });
  assert.equal(r.version, '1');
  assert.equal(r.id, 7);
  assert.equal(r.fehler, undefined);
  assert.deepEqual(r.diagnosen, []);
  assert.ok(r.elemente.some((e) => e.metaklasse === 'PartDefinition' && e.qualifiedName === 'Fahrzeuge::Auto'));
  assert.ok(r.elemente.some((e) => e.metaklasse === 'PartUsage' && e.qualifiedName === 'Fahrzeuge::auto::raeder'));
});

test('syntax error is GRAMMATIK/SYNTAX with a line', () => {
  const r = pruefe({ quelltext: 'package P {\n  part def A;\n  part def ;;; B {\n}\n' });
  const errors = select(r, 'GRAMMATIK', 'SYNTAX');
  assert.ok(errors.length > 0);
  assert.ok(errors.some((e) => e.zeile === 3));
});

test('unresolved reference is LOGIK/UNRESOLVED', () => {
  const r = pruefe({ quelltext: 'package P {\n  part def A;\n  part x : DoesNotExist;\n}\n' });
  assert.deepEqual(select(r, 'GRAMMATIK'), []);
  const u = select(r, 'LOGIK', 'UNRESOLVED');
  assert.equal(u.length, 1);
  assert.equal(u[0].name, 'DoesNotExist');
  assert.equal(u[0].zeile, 3);
});

test('required elements: Motor missing, Auto is no PartUsage', () => {
  const r = pruefe({
    quelltext: VALID,
    pflichtelemente: [
      { metaklasse: 'PartDefinition', name: 'Auto' },
      { metaklasse: 'PartDefinition', name: 'Motor' },
      { metaklasse: 'PartUsage', name: 'Fahrzeuge::auto::raeder' },
      { metaklasse: 'PartUsage', name: 'Auto' },
    ],
  });
  const missing = select(r, 'LOGIK', 'PFLICHT');
  assert.deepEqual(missing.map((d) => d.name), ['Motor', 'Auto']);
});

test('import from the embedded standard library resolves; unknown name is reported', () => {
  const r = pruefe({ quelltext: 'package P {\n  import ScalarValues::*;\n  import ISQ::*;\n  import SI::*;\n  attribute def M {\n    attribute n : Integer;\n    attribute l : LengthValue;\n    attribute m : MassValue = 5 [kg];\n    attribute x : Integerr;\n  }\n}\n' });
  assert.deepEqual(select(r, 'GRAMMATIK'), []);
  const u = select(r, 'LOGIK', 'UNRESOLVED');
  assert.deepEqual(u.map((d) => d.name), ['Integerr']);
});

test('requests do not influence each other', () => {
  const broken = pruefe({ quelltext: 'package P {\n  part x : Gone;\n  part def ;;;\n}\n' });
  assert.ok(broken.diagnosen.length > 0);
  assert.deepEqual(pruefe({ quelltext: VALID }).diagnosen, []);
});

test('STRUKTUR: valid model has none; a syntax error does not yield a second (STRUKTUR) diagnosis', () => {
  assert.deepEqual(select(pruefe({ quelltext: VALID }), 'LOGIK', 'STRUKTUR'), []);
  const r = pruefe({ quelltext: 'part def A { attribute x [0..*] = ; }' });
  assert.ok(select(r, 'GRAMMATIK').length > 0);
  assert.deepEqual(select(r, 'LOGIK', 'STRUKTUR'), []);
});

test('invalid requests answer with "fehler"', () => {
  const r = JSON.parse((() => { const p = call('sysml_pruefe', 'not json'); const t = mod.UTF8ToString(p); mod._sysml_freigeben(p); return t; })());
  assert.equal(typeof r.fehler, 'string');
  assert.deepEqual(r.diagnosen, []);
  assert.equal(pruefe({ quelltext: 5 }).fehler, 'quelltext must be a string');
});

test('limits: too large, too deep, too long chain, token limit', () => {
  assert.equal(pruefe({ quelltext: `package P { ${'part a;'.repeat(30000)} }` }).fehler, 'zuGross');
  assert.equal(pruefe({ quelltext: 'package P ' + '{ '.repeat(100) + '}'.repeat(100) }).fehler, 'zuTief');
  assert.equal(pruefe({ quelltext: 'package P { part x : ' + Array.from({ length: 100 }, (_, i) => 'a' + i).join('::') + '; }' }).fehler, 'zuLang');
  assert.equal(call('sysml_konfigurieren', '{"maxTokens":50}') , 1);
  assert.equal(pruefe({ quelltext: 'package P { ' + 'part a; '.repeat(40) + '}' }).fehler, 'zuGross');
  assert.equal(call('sysml_konfigurieren', '{"maxTokens":20000}'), 1);
  assert.equal(call('sysml_konfigurieren', '[1]'), 0);
  assert.deepEqual(pruefe({ quelltext: VALID }).diagnosen, []);
});

test('operator chains within the byte limit are refused (zuTief), no JS exception', () => {
  for (const op of ['1 + ', 'a ** ', 'if true ? 1 else ', 'true implies ', 'true or ']) {
    const r = pruefe({ quelltext: 'package P { attribute x = ' + op.repeat(3000) + '1; }' });
    assert.equal(r.fehler, 'zuTief', op);
  }
  assert.deepEqual(pruefe({ quelltext: VALID }).diagnosen, []);
  assert.equal(call('sysml_konfigurieren', '{"maxOperatoren":1000}'), 1);
  assert.equal(call('sysml_konfigurieren', '{"maxOperatoren":256}'), 1);
});

test('alias of a missing name: exactly one Logik diagnosis; memory is reported', () => {
  const r = pruefe({ quelltext: 'package P { alias X for Missing; }' });
  assert.deepEqual(select(r, 'LOGIK').map((d) => d.quelle), ['UNRESOLVED']);
  assert.ok(mod.ccall('sysml_speicher', 'number', [], []) >= 64 * 1048576);
});

test('limit of diagnoses', () => {
  assert.equal(call('sysml_konfigurieren', '{"maxDiagnosen":3}'), 1);
  const r = pruefe({ quelltext: 'package P { part x : A; part y : B; part z : C; part w : D; part v : E; }' });
  assert.equal(r.diagnosen.length, 3);
  assert.ok(r.weitereDiagnosen >= 2);
  call('sysml_konfigurieren', '{"maxDiagnosen":200}');
});

test('parse deadline: zeitueberschreitung, module stays usable', () => {
  // 1 ms deadline
  assert.equal(call('sysml_konfigurieren', '{"maxMs":1}'), 1);
  const big = 'package P {\n' + Array.from({ length: 300 }, (_, i) => `  part def D${i} { part p${i} : D${i}; attribute a${i}; }`).join('\n') + '\n}\n';
  const r = pruefe({ quelltext: big });
  assert.equal(r.fehler, 'zeitueberschreitung');
  assert.equal(call('sysml_konfigurieren', '{"maxMs":20000}'), 1);
  assert.equal(pruefe({ quelltext: big }).fehler, undefined);
  assert.deepEqual(pruefe({ quelltext: VALID }).diagnosen, []);
});

// Timings
const warmStart = performance.now();
const loaded = mod.ccall('sysml_vorwaermen', 'number', ['string'], ['["*"]']);
const tWarm = performance.now() - warmStart;
assert.ok(loaded > 0, 'sysml_vorwaermen loaded nothing');
const times = [];
for (let i = 0; i < 5; i++) {
  const s = performance.now();
  const r = pruefe({ quelltext: VALID });
  times.push(performance.now() - s);
  assert.deepEqual(r.diagnosen, []);
}
console.log(`timing: module start ${tStart.toFixed(0)} ms; sysml_vorwaermen(["*"]) ${(tWarm / 1000).toFixed(1)} s (${loaded} library files); warm request ${Math.min(...times).toFixed(1)}-${Math.max(...times).toFixed(1)} ms`);
console.log(`${n} tests passed`);
