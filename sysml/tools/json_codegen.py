"""JSON code generation for the SysML metaclasses (imported by generate_abstract_syntax.py).

generate_abstract_syntax.py rewrites every generated file completely, so the JSON code is not written by a second generator with
markers (as kerml/tools/generate_json.py does for the hand-written KerML classes) but is emitted by the same script. This module only
builds text; it knows nothing about files. The caller hands over a namespace `h` with the helpers of the manifest (TYPES, cpp, is_ref,
is_enum, property_type, computed, literal), so there is no circular import.

It produces the same API and the same code shape as kerml/tools/generate_json.py:
  - explicit X(const std::string& nameOrJson)   (only for concrete classes)
  - serializeToJson, resolveJsonReferences, protected deserializeAndPopulate
  - clearUnresolvedJsonReferences("<property>") at the start of every generated reference setter
  - src/sysml/model/JsonSupport.h: the JSON literals of the SysML enumerations on top of kerml/model/JsonSupport.h
"""
import importlib.util
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# Classes whose own properties are not written or read here: the setters of Expose forward to KerML Import (see computed() in the
# generator), which already serializes and reads visibility and isImportAll.
FORWARDED = {'Expose'}

# A SysML member that hides a KerML member of the same JSON key: besides the own setter the setters listed here are called when reading
# ((class, property) -> setters). ConnectionDefinition::isSufficient hides Type::isSufficient; the SysML value is written (it is
# written after the bases and so overrides the Type value) and both members are set when reading.
ALSO_SET = {('ConnectionDefinition', 'isSufficient'): ['KerML::Entities::Type::setIsSufficient']}

LOOKUP = 'const std::function<std::shared_ptr<KerML::Entities::Element>(const boost::uuids::uuid&)>&'

_xmi = None


def xmi():
    """The helpers of filehandling/tools/generate_xmi_bindings.py (classes, linearization, setters of the hand-written KerML classes)."""
    global _xmi
    if _xmi is None:
        spec = importlib.util.spec_from_file_location('xmi_generator', ROOT / 'filehandling/tools/generate_xmi_bindings.py')
        _xmi = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(_xmi)
        _xmi.SETTER_NAMES['ownedRelatedElement'] = 'setOwnedRelatedElements'
    return _xmi


def indent(text, n):
    return '\n'.join((' ' * n + line if line.strip() else line) for line in text.split('\n'))


def own_properties(n):
    return [] if n['name'] in FORWARDED else n['properties']


def has_setter(h, n, p):
    return h.computed(n, p) is None


def scalar_kind(p):
    return {'Boolean': 'bool', 'String': 'string', 'Integer': 'int'}.get(p['type'], 'enum')


def optional_enums(h):
    """The enumerations that occur in an optional property (they need Json::value for std::optional)."""
    return sorted({p['type'] for n in h.TYPES.values() for p in n['properties']
                   if scalar_kind(p) == 'enum' and not h.is_ref(p) and p['upper'] == 1 and p['lower'] == 0 and p['type'] in h.TYPES})


def check_supported(h, n, p):
    """Fails if the property has a type that kerml/model/JsonSupport.h and the generated JsonSupport.h can not write."""
    kind = scalar_kind(p)
    if h.is_ref(p):
        return
    if p['upper'] != 1 and not p['derived']:
        # (a stored many-valued scalar would be read with the single-valued reader of scalar_read_block)
        raise SystemExit('json_codegen: stored many-valued %s property %s.%s is not supported' % (kind, n['name'], p['name']))
    if p['upper'] != 1 and kind != 'string':
        raise SystemExit('json_codegen: many-valued %s property %s.%s is not supported' % (kind, n['name'], p['name']))
    if p['upper'] == 1 and p['lower'] == 0 and kind not in ('string', 'enum'):
        raise SystemExit('json_codegen: optional %s property %s.%s is not supported' % (kind, n['name'], p['name']))


def check_names(h):
    """Stops the generator if two JSON properties could share a key although they are different things.

    Within the ancestry of a SysML class, two references with a setter that have the same name but different types (the key is shared
    by the ids that are read, so one of them would receive ids of the wrong type), or a SysML member that hides a KerML member of the
    same name that has a setter (then both setters must be called, see ALSO_SET), are reported with SystemExit."""
    g = xmi()
    for n in h.TYPES.values():
        if n['kind'] != 'Class' or n['name'] in FORWARDED:
            continue
        refs = {}
        shadowed = {}
        for owner in g.linearize(g.CLASSES[n['name']]):
            for p in owner.properties:
                key = p['name']
                if owner.language == 'S':
                    node = h.TYPES[owner.id]
                    if owner.name in FORWARDED or not has_setter(h, node, p):
                        continue
                    refs_entry = (owner.name, p['type'].split('-')[-1], 'S')
                    is_reference = h.is_ref(p)
                else:
                    tname = p['type'].split('-')[-1]
                    if key == 'elementId':
                        continue
                    setter = g.find_setter(owner, key, p['upper'] != 1)
                    if setter is None:
                        continue
                    refs_entry = (owner.name, tname, 'K')
                    is_reference = tname in g.CLASSES
                (refs if is_reference else shadowed).setdefault(key, []).append(refs_entry)
        for key, entries in refs.items():
            if any(e[2] == 'S' for e in entries) and len({e[1] for e in entries}) > 1:
                raise SystemExit('json_codegen: %s: the reference "%s" has setters with different types in its ancestry: %s' % (n['name'], key, entries))
        for key, entries in shadowed.items():
            own = [e for e in entries if e[2] == 'S' and e[0] == n['name']]
            if own and any(e[2] == 'K' for e in entries) and (n['name'], key) not in ALSO_SET:
                raise SystemExit('json_codegen: %s: "%s" hides a KerML member with a setter, add it to ALSO_SET: %s' % (n['name'], key, entries))


# ----------------------------------------------------------------------------------------------------------------------------------
# JsonSupport.h
# ----------------------------------------------------------------------------------------------------------------------------------

def json_support(h, banner):
    enums = [e for e in h.TYPES.values() if e['kind'] == 'Enumeration']
    optional = set(optional_enums(h))
    out = [banner, '''#pragma once
//
// JSON helpers of the SysML metaclasses (private to the sysml library). They extend the helpers of the KerML library
// (kerml/src/kerml/model/JsonSupport.h) by the enumerations of SysML. Enumerations are written as their OMG literal
// (the C++ literal do_ is "do").
//
// A many-valued String property (for example RequirementUsage::text) is written as an array of strings.
#include <kerml/model/JsonSupport.h>
''']
    out += ['#include <sysml/%s/%s.h>\n' % (e['package'], e['name']) for e in enums]
    out.append('''#include <optional>
#include <string>
#include <vector>

namespace SysMLv2::Entities::Json {
''')
    for name in ('Lookup', 'References', 'looksLikeJson', 'reference', 'value', 'readBool', 'readString', 'readInt', 'readDouble',
                 'readStringArray', 'readReferences', 'parseIdentity', 'literal', 'readEnum'):
        out.append('using KerML::Entities::Json::%s;\n' % name)
    out.append('''
inline nlohmann::json value(const std::vector<std::string>& v) {
    nlohmann::json json = nlohmann::json::array();
    for (const auto& item : v) {
        json.push_back(item);
    }
    return json;
}
''')
    for e in enums:
        name = e['name']
        lits = e['literals']
        out.append('\ninline std::string literal(%s v) {\n    switch (v) {\n' % name)
        out += ['        case %s::%s: return "%s";\n' % (name, h.literal(v), v) for v in lits]
        out.append('    }\n    return "%s";\n}\n' % lits[0])
        out.append('\ninline nlohmann::json value(%s v) {\n    return literal(v);\n}\n' % name)
        if e['id'] in optional:
            out.append('\ninline nlohmann::json value(const std::optional<%s>& v) {\n    if (!v.has_value()) {\n        return nullptr;\n    }\n    return literal(*v);\n}\n' % name)
        out.append('\ninline bool readEnum(const nlohmann::json& json, const char* key, %s& out) {\n    std::string text;\n    if (!readString(json, key, text)) {\n        return false;\n    }\n' % name)
        out += ['    if (text == "%s") {\n        out = %s::%s;\n        return true;\n    }\n' % (v, name, h.literal(v)) for v in lits]
        out.append('    return false;\n}\n')
    out.append('} // namespace SysMLv2::Entities::Json\n')
    return ''.join(out)


# ----------------------------------------------------------------------------------------------------------------------------------
# Header and source of a class
# ----------------------------------------------------------------------------------------------------------------------------------

def header_lines(h, n):
    """The declarations that are inserted before the private section of the class (public part first, then the protected one)."""
    name = n['name']
    out = ['\n']  # (a blank line separates the declarations from the properties)
    if not n['abstract']:
        out.append('''    /**
     * Creates a %(n)s either from its JSON representation (if the string starts with '{') or with the given declared name.
     * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "%(n)s".
     * @param nameOrJson The JSON representation of the %(n)s, or its declared name.
     */
    explicit %(n)s(const std::string& nameOrJson);
''' % dict(n=name))
    out.append('''    /**
     * Serializes the %(n)s to JSON: all properties of the metaclass (stored and derived ones) and of its base classes. References to
     * other elements are only written as identities ({"@id": "<uuid>"}), never recursively.
     * @return The JSON representation of the %(n)s.
     */
    std::string serializeToJson() override;

    /**
     * Resolves the references that were read from JSON to the elements (see Element::resolveJsonReferences()), for the properties
     * of %(n)s and of its base classes.
     * @param lookup Returns the element of an element id, or an empty pointer if it is not known.
     */
    void resolveJsonReferences(%(l)s lookup) override;

protected:
    /**
     * Populates the %(n)s from its JSON representation; the stored properties of %(n)s and of its base classes are read,
     * computed derived properties are ignored, the derived references that the model keeps as snapshots are read like the stored ones,
     * and references are only stored as ids.
     * @param jsonString The JSON representation of the %(n)s.
     */
    void deserializeAndPopulate(const std::string& jsonString) override;
''' % dict(n=name, l=LOOKUP))
    return out


def resolve_block(h, n, p):
    key = p['name']
    cap = key[0].upper() + key[1:]
    t = h.cpp(p['type'])
    call = n['name'] + '::set' + cap
    if p['upper'] != 1:
        return '''if (const auto ids = unresolvedJsonReferences("%(k)s")) {
    try {
        std::vector<std::shared_ptr<%(T)s>> resolved;
        for (const auto& id : *ids) {
            auto target = std::dynamic_pointer_cast<%(T)s>(lookup(id));
            if (!target) {
                break;
            }
            resolved.push_back(std::move(target));
        }
        // (the setter forgets the ids, see clearUnresolvedJsonReferences)
        if (resolved.size() == ids->size()) {
            %(call)s(std::move(resolved));
            clearUnresolvedJsonReferences("%(k)s");
        }
    } catch (const std::exception&) {
        // The reference stays unresolved if the model refuses it.
        setUnresolvedJsonReferences("%(k)s", *ids);
    }
}''' % dict(k=key, T=t, call=call)
    return '''if (const auto ids = unresolvedJsonReferences("%(k)s")) {
    try {
        if (auto target = std::dynamic_pointer_cast<%(T)s>(lookup(ids->front()))) {
            %(call)s(std::move(target));
            clearUnresolvedJsonReferences("%(k)s");
        }
    } catch (const std::exception&) {
        // The reference stays unresolved if the model refuses it.
        setUnresolvedJsonReferences("%(k)s", *ids);
    }
}''' % dict(k=key, T=t, call=call)


def scalar_read_block(h, n, p):
    key = p['name']
    cap = key[0].upper() + key[1:]
    kind = scalar_kind(p)
    ctype = {'bool': 'bool', 'string': 'std::string', 'int': 'std::int64_t'}.get(kind) or h.cpp(p['type'])
    reader = {'bool': 'readBool', 'string': 'readString', 'int': 'readInt', 'enum': 'readEnum'}[kind]
    setters = [n['name'] + '::set' + cap] + ALSO_SET.get((n['name'], key), [])
    tries = ''.join('''        try {
            %s(value);
        } catch (const std::invalid_argument&) {
            // A value the metaclass refuses is ignored.
        }
''' % s for s in setters)
    return '''{
    %s value{};
    if (Json::%s(json, "%s", value)) {
%s    }
}''' % (ctype, reader, key, tries)


def source_methods(h, n, method):
    """The definitions of the JSON functions of the class. method(signature, body) formats a function like the generator does."""
    name = n['name']
    bases = [h.cpp(b) for b in n['bases']]
    ser, de, res = [], [], []
    for p in own_properties(n):
        check_supported(h, n, p)
        key = p['name']
        gcall = '%s::%s()' % (name, key)
        if h.is_ref(p):
            ser.append('json["%s"] = Json::reference(unresolvedJsonReferences("%s"), %s);' % (key, key, gcall))
        else:
            ser.append('json["%s"] = Json::value(%s);' % (key, gcall))
        settable = has_setter(h, n, p)
        if h.is_ref(p):
            if not settable:
                continue  # a derived view is computed
            de.append('if (Json::readReferences(json, "%s", ids)) {\n    setUnresolvedJsonReferences("%s", ids);\n}' % (key, key))
            res.append(resolve_block(h, n, p))
        elif settable and not p['derived']:
            de.append(scalar_read_block(h, n, p))
    out = []
    if not n['abstract']:
        out.append(method(name + '::' + name + '(const std::string& nameOrJson) : ' + name + '()', '''if (Json::looksLikeJson(nameOrJson)) {
    deserializeAndPopulate(nameOrJson);
    captureJsonSource(nameOrJson);
} else {
    setDeclaredName(nameOrJson);
}'''))
    lines = ['nlohmann::json json = nlohmann::json::parse(%s::serializeToJson());' % bases[0]]
    lines += ['json.update(nlohmann::json::parse(%s::serializeToJson()));' % b for b in bases[1:]]
    lines += ser
    lines.append('return applyJsonSource(json.dump(JSON_INTENT));')
    out.append(method('std::string %s::serializeToJson()' % name, '\n'.join(lines)))
    lines = ['%s::deserializeAndPopulate(jsonString);' % b for b in bases]
    if de:
        lines.append('const nlohmann::json json = nlohmann::json::parse(jsonString);')
        if any('readReferences' in d for d in de):
            lines.append('std::vector<boost::uuids::uuid> ids;')
        lines += de
    out.append(method('void %s::deserializeAndPopulate(const std::string& jsonString)' % name, '\n'.join(lines)))
    lines = ['%s::resolveJsonReferences(lookup);' % b for b in bases] + res
    out.append(method('void %s::resolveJsonReferences(%s lookup)' % (name, LOOKUP), '\n'.join(lines)))
    return out


def setter_hook(p):
    """The statement at the start of the setter of a reference (a value set later must not be overridden by an id read from JSON)."""
    return 'clearUnresolvedJsonReferences("%s");\n' % p['name']
