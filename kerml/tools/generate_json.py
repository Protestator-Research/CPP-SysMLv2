#!/usr/bin/env python3
"""Generate the JSON serialization of the KerML metaclasses (kerml/include/kerml/..., kerml/src/kerml/...).

Reads kerml/model/abstract_syntax.json (the OMG metamodel inventory) and the C++ headers of the model classes (through the helpers of
filehandling/tools/generate_xmi_bindings.py, which finds the setters and getters of the properties). For every KerML metaclass (except
Element, whose JSON code is written by hand in kerml/src/kerml/root/elements/Element.cpp) it writes

  - in the header: the declarations of the constructor that takes a name or a JSON string (only for classes whose string constructor is not
    written by hand, see EXISTING_CTOR), of serializeToJson, resolveJsonReferences and deserializeAndPopulate, and
  - in the source: their definitions. serializeToJson writes all properties of the metaclass (stored and derived ones, through the getters),
    deserializeAndPopulate reads the stored ones and the derived references that have a setter (references only as ids) and resolveJsonReferences resolves the stored ids through the setters
    (one try block per property, so one refused reference does not stop the others).

The generated regions are enclosed in the comments "BEGIN GENERATED JSON" and "END GENERATED JSON" and are replaced by this script: do not edit them.
Besides, the script inserts a call of clearUnresolvedJsonReferences("<property>") at the start of every setter of a stored reference, so that a
value that is set later is not overridden by the id that was read from JSON.

Usage (from any directory):
    python kerml/tools/generate_json.py           writes the files
    python kerml/tools/generate_json.py --check   verifies that the checked-in files are up to date
The files keep their line endings (CRLF or LF).
"""
import argparse
import importlib.util
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

_spec = importlib.util.spec_from_file_location('xmi_generator', ROOT / 'filehandling/tools/generate_xmi_bindings.py')
g = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(g)
g.SETTER_NAMES['ownedRelatedElement'] = 'setOwnedRelatedElements'

BEGIN = 'BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.'
END = 'END GENERATED JSON'
LOOKUP = 'const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>&'

# Classes whose string constructor is written by hand (an existing constructor that takes a name or an element id was extended).
EXISTING_CTOR = {'Relationship', 'Annotation', 'Dependency', 'Import', 'NamespaceImport', 'Namespace', 'Type', 'Classifier', 'TextualRepresentation'}
# Classes without a default constructor: they can not delegate to it.
DELETED_DEFAULT = {'Subclassification', 'CrossSubsetting', 'EndFeatureMembership', 'FeatureChaining', 'FeatureInverting', 'Redefinition',
                   'ReferenceSubsetting', 'Subsetting', 'TypeFeaturing', 'Differencing', 'Disjoining', 'Intersecting', 'Unioning'}
SUBSETTING_DERIVED = {'CrossSubsetting', 'Redefinition', 'ReferenceSubsetting'}
SKIP_PROPERTIES = {'elementId'}
# Derived properties that are only known by the id of a reference that is not resolved yet: (class, property) -> the reference it is taken from.
ID_OF_REFERENCE = {('Membership', 'memberElementId'): 'memberElement', ('OwningMembership', 'ownedMemberElementId'): 'memberElement'}

classes = [c for c in g.CLASSES.values() if c.language == 'K']
byname = {c.name: c for c in classes}


def cpp_bases(c):
    text = re.sub(r'/\*.*?\*/', '', c.header.read_text(encoding='utf8'), flags=re.S)
    m = re.search(r'class\s+(?:KERML_EXPORT\s+)?' + c.name + r'\s*:\s*([^{]*)\{', text)
    if not m:
        return []
    result = []
    for part in m.group(1).split(','):
        part = part.replace('public', '').replace('virtual', '').strip()
        if part in g.CLASSES:
            result.append(part)
    return result


for _c in classes:
    _c.cbases = cpp_bases(_c)


def ancestors(name):
    result = set()
    for b in byname[name].cbases:
        result.add(b)
        result |= ancestors(b)
    return result


def src_path(c):
    return ROOT / 'kerml/src' / Path(*c.header.relative_to(ROOT / 'kerml/include').parts).with_suffix('.cpp')


def is_virtual_setter(c, setter):
    """The setter is virtual in a class of the hierarchy (the call must not be qualified, so that a derived class can refuse a value)."""
    for owner in g.linearize(c):
        if re.search(r'\bvirtual\s+void\s+' + setter + r'\b', owner.text):
            return True
    return False


def indent(text, n):
    return '\n'.join((' ' * n + line if line.strip() else line) for line in text.split('\n'))


def property_code(c):
    """(serialize lines, deserialize lines, resolve blocks, [(declaring class, property, setter name)] of the stored references)."""
    ser, de, res, hooks = [], [], [], []
    for p in c.properties:
        if p['name'] in SKIP_PROPERTIES:
            continue
        key = p['name']
        many = p['upper'] != 1
        tname = p['type'].split('-')[-1]
        getter = g.find_getter(c, key)
        setter = g.find_setter(c, key, many)
        is_ref = tname in g.CLASSES
        if c.name == 'Element' and not is_ref:
            continue  # (the JSON code of Element is written by hand, only the setters of its stored references are hooked)
        if getter is None:
            raise SystemExit('no getter: %s.%s' % (c.name, key))
        gcall = '%s::%s()' % (getter[0].name, getter[1])
        if is_ref:
            ser.append('json["%s"] = Json::reference(unresolvedJsonReferences("%s"), %s);' % (key, key, gcall))
        elif (c.name, key) in ID_OF_REFERENCE:
            ser.append('json["%s"] = Json::idText(%s, unresolvedJsonReferences("%s"));' % (key, gcall, ID_OF_REFERENCE[(c.name, key)]))
        else:
            ser.append('json["%s"] = Json::value(%s);' % (key, gcall))
        # The derived references that the model keeps in a collection or cache (they have a setter) are read like the stored ones, because the
        # cache can not always be rebuilt from the stored properties (for example the arguments of an expression). The other derived
        # properties are computed and ignored on input.
        if p['derived'] and not (is_ref and setter is not None):
            continue
        if is_ref:
            de.append('if (Json::readReferences(json, "%s", ids))\n    setUnresolvedJsonReferences("%s", ids);' % (key, key))
            if setter is None:
                continue
            owner, sname, param = setter
            hooks.append((owner, key, sname))
            inner = param
            m = re.match(r'^std::optional<(.*)>$', inner)
            if m:
                inner = m.group(1).strip()
            sm = re.match(r'^std::shared_ptr<(.*)>$', inner)
            vm = re.match(r'^std::vector<std::shared_ptr<(.*)>>$', inner)
            call = '%s::%s' % (owner.name, sname)
            if vm:
                T = vm.group(1).strip()
                res.append('''if (const auto ids = unresolvedJsonReferences("%(k)s")) {
    try {
        std::vector<std::shared_ptr<KerML::Entities::%(T)s>> resolved;
        for (const auto& id : *ids) {
            auto target = std::dynamic_pointer_cast<KerML::Entities::%(T)s>(lookup(id));
            if (!target)
                break;
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
}''' % dict(k=key, T=T, call=call))
            elif sm:
                T = sm.group(1).strip()
                res.append('''if (const auto ids = unresolvedJsonReferences("%(k)s")) {
    try {
        if (auto target = std::dynamic_pointer_cast<KerML::Entities::%(T)s>(lookup(ids->front()))) {
            %(call)s(std::move(target));
            clearUnresolvedJsonReferences("%(k)s");
        }
    } catch (const std::exception&) {
        // The reference stays unresolved if the model refuses it.
        setUnresolvedJsonReferences("%(k)s", *ids);
    }
}''' % dict(k=key, T=T, call=call))
            else:
                raise SystemExit('unsupported setter parameter %s.%s: %s' % (c.name, key, param))
        else:
            if setter is None:
                continue
            owner, sname, param = setter
            inner = param
            m = re.match(r'^std::optional<(.*)>$', inner)
            if m:
                inner = m.group(1).strip()
            call = ('%s' % sname) if is_virtual_setter(c, sname) else '%s::%s' % (owner.name, sname)
            if inner == 'bool':
                reader = 'readBool'
            elif inner == 'std::string':
                reader = 'readString'
            elif inner == 'double':
                reader = 'readDouble'
            elif inner in ('std::int64_t', 'int', 'long', 'unsigned', 'std::uint64_t'):
                reader = 'readInt'
            elif inner in g.ENUMS:
                reader = 'readEnum'
            else:
                raise SystemExit('unsupported scalar %s.%s: %s' % (c.name, key, param))
            de.append('''{
    %s value{};
    if (Json::%s(json, "%s", value)) {
        try {
            %s(value);
        } catch (const std::invalid_argument&) {
            // A value the metaclass refuses (for example another operator than the fixed one) is ignored.
        }
    }
}''' % (inner, reader, key, call))
    return ser, de, res, hooks


def cpp_block(c):
    name = c.name
    ser, de, res, _ = property_code(c)
    out = []
    if name not in EXISTING_CTOR:
        init = ''
        if name in SUBSETTING_DERIVED:
            init = ' :\n        Subsetting(JsonTag{})'
        elif name not in DELETED_DEFAULT:
            # the default constructor sets the defaults of the metaclass (for example the fixed operator of a CollectExpression)
            init = ' :\n        %s()' % name
        a = 'nameOrJson'
        fallback = 'setDeclaredName(%s)' % a
        out.append('''    %(n)s::%(n)s(const std::string& %(a)s)%(init)s {
        _dType = "%(n)s";
        if (Json::looksLikeJson(%(a)s)) {
            deserializeAndPopulate(%(a)s);
            captureJsonSource(%(a)s);
        } else {
            %(fb)s;
        }
    }
''' % dict(n=name, a=a, init=init, fb=fallback))
    b = c.cbases
    lines = ['nlohmann::json json = nlohmann::json::parse(%s::serializeToJson());' % b[0]]
    for extra in b[1:]:
        lines.append('json.update(nlohmann::json::parse(%s::serializeToJson()));' % extra)
    lines += ser
    lines.append('return applyJsonSource(json.dump(JSON_INTENT));')
    out.append('    std::string %s::serializeToJson() {\n%s\n    }\n' % (name, indent('\n'.join(lines), 8)))
    lines = ['%s::deserializeAndPopulate(jsonString);' % x for x in b]
    if de:
        lines.append('const nlohmann::json json = nlohmann::json::parse(jsonString);')
        if any('ids' in d for d in de):
            lines.append('std::vector<boost::uuids::uuid> ids;')
        lines += de
    out.append('    void %s::deserializeAndPopulate(const std::string& jsonString) {\n%s\n    }\n' % (name, indent('\n'.join(lines), 8)))
    lines = ['%s::resolveJsonReferences(lookup);' % x for x in b] + res
    out.append('    void %s::resolveJsonReferences(%s lookup) {\n%s\n    }\n' % (name, LOOKUP, indent('\n'.join(lines), 8)))
    return '// ' + BEGIN + '\nnamespace KerML::Entities {\n' + '\n'.join(out) + '}\n// ' + END + '\n'


def header_block_body(c):
    name = c.name
    parts = ['\n    public:']
    if name not in EXISTING_CTOR:
        parts.append('''        /**
         * Creates a %(n)s either from its JSON representation (if the string starts with '{') or with the given declared name.
         * Reading JSON only stores the ids of the referenced elements, see Element::resolveJsonReferences(). The type of the object stays "%(n)s".
         * @param nameOrJson The JSON representation of the %(n)s, or its declared name.
         */
        explicit %(n)s(const std::string& nameOrJson);
''' % dict(n=name))
    parts.append('''        /**
         * Serializes the %(n)s to JSON: all properties of the metaclass (stored and derived ones). References to other elements are
         * only written as identities ({"@id": "<uuid>"}), never recursively.
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
         * computed derived properties are ignored, the derived references that the model keeps as collections are read like the stored ones,
         * and references are only stored as ids.
         * @param jsonString The JSON representation of the %(n)s.
         */
        void deserializeAndPopulate(const std::string& jsonString) override;
''' % dict(n=name, l=LOOKUP))
    return '\n'.join(parts)


def header_block(c):
    return '\n    // ' + BEGIN + '\n' + header_block_body(c).lstrip('\n') + '    // ' + END + '\n'


def strip_comments_keep_length(t):
    t = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m.group(0)), t, flags=re.S)
    return re.sub(r'//[^\n]*', lambda m: ' ' * len(m.group(0)), t)


def transform_header(c, text):
    block = header_block(c)
    start = text.find('\n    // ' + BEGIN + '\n')
    if start >= 0:
        end_marker = '    // ' + END + '\n'
        end = text.index(end_marker, start) + len(end_marker)
        return text[:start] + block + text[end:]
    # the first version of the generated code had no markers: remove it
    first = None
    for lead in ('Creates a %s either' % c.name, 'Serializes the %s to JSON' % c.name):
        k = text.find('\n    public:\n        /**\n         * ' + lead)
        if k >= 0:
            first = k
            break
    if first is not None:
        tail = '        void deserializeAndPopulate(const std::string& jsonString) override;\n'
        text = text[:first] + text[text.index(tail, first) + len(tail):]
    s = strip_comments_keep_length(text)
    m = re.search(r'class\s+(?:KERML_EXPORT\s+)?' + c.name + r'\s*:[^{]*\{', s)
    i = m.end()
    depth = 1
    while depth:
        depth += (s[i] == '{') - (s[i] == '}')
        i += 1
    close = i - 1
    line_start = text.rfind('\n', 0, close) + 1
    return text[:line_start] + block + text[line_start:]


def transform_cpp(c, text):
    block = cpp_block(c)
    start = text.find('// ' + BEGIN)
    if start >= 0:
        end_marker = '// ' + END + '\n'
        end = text.index(end_marker, start) + len(end_marker)
        text = text[:start].rstrip('\n') + '\n\n' + block + text[end:].lstrip('\n')
    else:
        # the first version had no markers: remove its trailing block
        marker = '\nnamespace KerML::Entities {\n'
        while True:
            k = text.rfind(marker)
            if k >= 0 and ('%s::serializeToJson' % c.name) in text[k:]:
                text = text[:k].rstrip('\n') + '\n'
            else:
                break
        text = text.rstrip('\n') + '\n\n' + block
    includes = ['#include <kerml/KerML.h>', '#include <nlohmann/json.hpp>', '#include "../../model/JsonSupport.h"']
    missing = [x for x in includes if x not in text]
    if missing:
        found = list(re.finditer(r'^#include[^\n]*\n', text, flags=re.M))
        pos = found[-1].end() if found else 0
        text = text[:pos] + '\n'.join(missing) + '\n' + text[pos:]
    return text


def hook_setters(files, hooks):
    """Inserts clearUnresolvedJsonReferences("<property>") at the start of the setters of the stored references. files: path -> text."""
    for owner, prop, setter in sorted(hooks, key=lambda h: (h[0].name, h[1])):
        pattern = re.compile(r'\b' + owner.name + r'::' + setter + r'\s*\(([^()]*)\)\s*\{')
        statement = 'clearUnresolvedJsonReferences("%s");' % prop
        found = False
        for path, text in files.items():
            pos = 0
            while True:
                m = pattern.search(text, pos)
                if not m:
                    break
                found = True
                body = m.end()
                pos = body
                if statement in text[body:body + 300]:
                    continue
                if text[body:].startswith('\n'):
                    nxt = re.match(r'\n([ \t]*)', text[body:])
                    ws = nxt.group(1) if nxt and nxt.group(1) else '    '
                    insertion = '\n' + ws + statement
                else:
                    insertion = ' ' + statement
                text = text[:body] + insertion + text[body:]
                pos = body + len(insertion)
            files[path] = text
        if not found:
            raise SystemExit('definition of %s::%s not found' % (owner.name, setter))


def build():
    """path -> new text of every file that this script writes."""
    files = {}

    def load(path):
        if path not in files:
            raw = path.read_bytes().decode('utf8')
            files[path] = raw
        return files[path]

    crlf = {}
    sources = sorted((ROOT / 'kerml/src').rglob('*.cpp'))
    for path in sources:
        raw = path.read_bytes().decode('utf8')
        crlf[path] = '\r\n' in raw
        files[path] = raw.replace('\r\n', '\n')
    for c in classes:
        raw = c.header.read_bytes().decode('utf8')
        crlf[c.header] = '\r\n' in raw
        files[c.header] = raw.replace('\r\n', '\n')

    hooks = []
    for c in classes:
        if c.name != 'Element':
            files[c.header] = transform_header(c, files[c.header])
            sp = src_path(c)
            files[sp] = transform_cpp(c, files[sp])
        hooks += property_code(c)[3]
    sources_only = {p: files[p] for p in sources}
    hook_setters(sources_only, hooks)
    files.update(sources_only)
    return {p: (t.replace('\n', '\r\n') if crlf[p] else t) for p, t in files.items()}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    result = build()
    stale = []
    for path, text in sorted(result.items()):
        if path.read_bytes().decode('utf8') != text:
            stale.append(path)
            if not args.check:
                path.write_bytes(text.encode('utf8'))
    if args.check:
        if stale:
            raise SystemExit('Generated files are stale: ' + ', '.join(str(p.relative_to(ROOT)) for p in stale))
        print('verified')
    else:
        print('%d files written' % len(stale))
