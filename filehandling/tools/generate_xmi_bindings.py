#!/usr/bin/env python3
"""Generate the metaclass factory and the XMI property bindings of the XMI importer (filehandling/src/sysmlv2/xmi).

Reads kerml/model/abstract_syntax.json and sysml/model/abstract_syntax.json (the OMG metamodel inventory) and the C++ headers of the
model classes. For every concrete KerML and SysML metaclass the output holds
  - a factory (KerML: std::make_shared of the hand-written class, SysML: SysMLv2::Entities::createRepresentation), and
  - a table of its properties (inherited ones included) that the importer reads from an XMI file: name, kind (bool / integer / real /
    string / enumeration / reference), multiplicity and a setter that works on KerML::Entities::Element& through dynamic_cast.
Only stored (non-derived) properties are bound, and only if the C++ class has a setter for them; derived properties are recomputed and
are ignored when they occur in an XMI file. The containment properties (ownedRelationship, ownedRelatedElement, ...) and the elementId are
structure and are handled by the importer itself (see SKIPPED). Setters whose name does not follow the pattern set<Property> are
listed in SETTER_NAMES.

Run from any directory; --check verifies that the checked-in output is up to date.
"""
import argparse
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
OUTPUT = ROOT / 'filehandling/src/sysmlv2/xmi/XmiBindings.generated.cpp'

KERML = json.loads((ROOT / 'kerml/model/abstract_syntax.json').read_text(encoding='utf8'))
SYSML = json.loads((ROOT / 'sysml/model/abstract_syntax.json').read_text(encoding='utf8'))

# Properties that are structure, not data: the importer wires them itself.
SKIPPED = {'elementId', 'ownedRelationship', 'ownedRelatedElement', 'owningRelationship', 'owningRelatedElement', 'source', 'target',
           'aliasIds'}

# Setters that are not called set<Property> in the hand-written classes: property -> setter name.
SETTER_NAMES = {
    'isAbstract': 'setAbstract',
    'operator': 'setOperatorName',
    'originalType': 'setOrginalType',
    'conjugatedType': 'setConjungatedType',
    'isImpliedIncluded': 'setImpliedIncluded',
}

SCALARS = {'bool': 'Boolean', 'std::int64_t': 'Integer', 'int': 'Integer', 'long': 'Integer', 'double': 'Real', 'std::string': 'String'}


class Cls:
    def __init__(self, data, language):
        self.data = data
        self.language = language  # 'K' or 'S'
        self.name = data['name']
        self.id = data['id']
        self.abstract = data['abstract']
        self.bases = data['bases']
        self.properties = data['properties']
        if language == 'K':
            self.header = ROOT / 'kerml/include' / data['header']
        else:
            self.header = ROOT / 'sysml/include/sysml' / data['package'] / (self.name + '.h')
        self._text = None

    @property
    def text(self):
        if self._text is None:
            text = self.header.read_text(encoding='utf8') if self.header.exists() else ''
            text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
            self._text = re.sub(r'//[^\n]*', '', text)
        return self._text

    @property
    def qualified(self):
        return ('KerML::Entities::' if self.language == 'K' else 'SysMLv2::Entities::') + self.name


CLASSES = {}
BY_ID = {}
ENUMS = {}
for model, language in ((KERML, 'K'), (SYSML, 'S')):
    for t in model['types']:
        if t['kind'] == 'Class':
            c = Cls(t, language)
            assert c.name not in CLASSES, 'metaclass name clash: ' + c.name
            CLASSES[c.name] = c
            BY_ID[c.id] = c
        else:
            ENUMS[t['name']] = (language, t)


def base_classes(c):
    result = []
    for b in c.bases:
        base = BY_ID.get(b) or CLASSES.get(b)
        if base is None:
            raise SystemExit('unknown base ' + b + ' of ' + c.name)
        result.append(base)
    return result


def linearize(c):
    """The class and its ancestors, nearest first, each once."""
    order = []

    def visit(x):
        if x in order:
            return
        order.append(x)
        for b in base_classes(x):
            visit(b)

    visit(c)
    return order


def split_parameter(declaration):
    declaration = declaration.split('=')[0].strip()
    m = re.match(r'^(.*?)\s*&?\s*\b(\w+)\s*$', declaration)
    if m and m.group(1):
        return m.group(1).strip()
    return declaration


def clean_type(t):
    t = re.sub(r'\bconst\b', '', t).replace('&', '').strip()
    t = t.replace('KerML::Entities::', '').replace('SysMLv2::Entities::', '')
    return re.sub(r'\s+', ' ', t)


def find_setter(c, prop, many):
    """(class that declares the setter, setter name, parameter type) or None."""
    setter = SETTER_NAMES.get(prop, 'set' + prop[0].upper() + prop[1:])
    for owner in linearize(c):
        found = []
        for m in re.finditer(r'\b' + setter + r'\s*\(([^()]*)\)', owner.text):
            found.append(clean_type(split_parameter(m.group(1))))
        if found:
            wanted = [f for f in found if f.startswith('std::vector<')] if many else [f for f in found if not f.startswith('std::vector<')]
            return owner, setter, (wanted or found)[0]
    return None


def placeholder_kind(target):
    """The placeholder (makePlaceholder) that is-a target, or None."""
    if target == 'Element':
        return 'Element'
    if target in ('Namespace', 'Type'):
        return 'Type'
    if target == 'Classifier':
        return 'Classifier'
    if target == 'Feature':
        return 'Feature'
    return None


def enum_parser(enum_name):
    language, t = ENUMS[enum_name]
    literals = t['literals']
    if language == 'K':
        # unscoped enumerators of the hand-written headers: IN_OUT for "inout"
        header = None
        for path in (ROOT / 'kerml/include').rglob(enum_name + '.h'):
            header = path.read_text(encoding='utf8')
        body = re.search(r'enum\s+(?:KERML_EXPORT\s+)?' + enum_name + r'\s*\{([^}]*)\}', header).group(1)
        names = [x.strip() for x in body.split(',') if x.strip()]
        mapping = {}
        for lit in literals:
            candidates = [n for n in names if n.replace('_', '').lower() == lit.replace('_', '').lower()]
            if len(candidates) != 1:
                raise SystemExit('cannot map literal ' + lit + ' of ' + enum_name)
            mapping[lit] = 'KerML::Entities::' + candidates[0]
        ctype = 'KerML::Entities::' + enum_name
    else:
        mapping = {lit: 'SysMLv2::Entities::' + enum_name + '::' + (lit + '_' if lit in ('do', 'if', 'else', 'while', 'for', 'return') else lit)
                   for lit in literals}
        ctype = 'SysMLv2::Entities::' + enum_name
    lines = ['bool parse' + enum_name + '(const std::string& text, ' + ctype + '& out) {']
    for lit, value in mapping.items():
        lines.append('    if (text == "' + lit + '") { out = ' + value + '; return true; }')
    lines += ['    return false;', '}', '']
    return '\n'.join(lines)


def enum_name_of(p):
    t = p['type'].split('-')[-1]
    return t if t in ENUMS else None


GAPS = []


def binding_for(declaring, p):
    """(identifier, definition) of the binding of one stored property, or None if the C++ model has no setter for it."""
    prop = p['name']
    many = p['upper'] != 1
    found = find_setter(declaring, prop, many)
    if found is None:
        GAPS.append(declaring.name + '.' + prop)
        return None
    owner, setter, parameter = found
    inner = parameter
    optional = re.match(r'^std::optional<(.*)>$', inner)
    if optional:
        inner = optional.group(1).strip()
    ident = 'p_' + declaring.name + '_' + prop
    target_class = owner.qualified
    call = 'as<' + target_class + '>(e).' + target_class + '::' + setter
    multiplicity = 'true' if many else 'false'

    def head(kind, target, placeholder, can_placeholder):
        return ('const PropertyBinding ' + ident + ' = {"' + prop + '", PropertyKind::' + kind + ', ' + multiplicity + ', "' + declaring.name +
                '", "' + target + '", ReferenceKind::' + placeholder + ', ' + can_placeholder + ', ')

    enum = enum_name_of(p)
    shared = re.match(r'^std::shared_ptr<(.*)>$', inner)
    vector = re.match(r'^std::vector<std::shared_ptr<(.*)>>$', inner)
    if shared or vector:
        target_name = (shared or vector).group(1).strip()
        if target_name not in CLASSES:
            GAPS.append(declaring.name + '.' + prop + ' (target ' + target_name + ')')
            return None
        target = CLASSES[target_name]
        kind = placeholder_kind(target.name)
        code = [head('Reference', target.name, kind or 'Element', 'true' if kind else 'false') + 'nullptr,',
                '    [](Element& e, const std::vector<ElementPtr>& values, std::string& error) {']
        if vector:
            code += ['        std::vector<std::shared_ptr<' + target.qualified + '>> typed;',
                     '        for (const auto& value : values) {',
                     '            std::shared_ptr<' + target.qualified + '> item;',
                     '            if (!castReference(value, item, "' + target.name + '", error)) return false;',
                     '            typed.push_back(std::move(item));',
                     '        }',
                     '        ' + call + '(std::move(typed));']
        else:
            code += ['        std::shared_ptr<' + target.qualified + '> typed;',
                     '        if (!castReference(values.front(), typed, "' + target.name + '", error)) return false;',
                     '        ' + call + '(typed);']
        code += ['        return true;', '    }};', '']
        return ident, '\n'.join(code)
    if enum or inner in ENUMS:
        name = enum or inner
        ctype = ('KerML::Entities::' if ENUMS[name][0] == 'K' else 'SysMLv2::Entities::') + name
        code = [head('Enumeration', name, 'Element', 'false') + '',
                '    [](Element& e, const std::string& text) {',
                '        ' + ctype + ' value;',
                '        if (!parse' + name + '(text, value)) return false;',
                '        ' + call + '(value);',
                '        return true;',
                '    }, nullptr};', '']
        return ident, '\n'.join(code)
    if inner in SCALARS:
        scalar = SCALARS[inner]
        parse = {'Boolean': 'parseBoolean', 'Integer': 'parseInteger', 'Real': 'parseReal', 'String': None}[scalar]
        body = ['        ' + inner + ' value;']
        if parse:
            body += ['        if (!' + parse + '(text, value)) return false;']
        else:
            body += ['        value = text;']
        body += ['        ' + call + '(value);', '        return true;']
        code = [head(scalar, '', 'Element', 'false') + '',
                '    [](Element& e, const std::string& text) {'] + body + ['    }, nullptr};', '']
        return ident, '\n'.join(code)
    GAPS.append(declaring.name + '.' + prop + ' (parameter ' + parameter + ')')
    return None


def parameter_lists(text, name):
    """The parameter lists of all declarations 'name(...)' in text (parentheses inside default arguments are balanced)."""
    result = []
    for m in re.finditer(r'\b' + name + r'\s*\(', text):
        depth = 1
        i = m.end()
        while i < len(text) and depth > 0:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        rest = text[i:i + 12].lstrip()
        if rest.startswith((':', '{', ';', 'override')):
            result.append(text[m.end():i - 1])
    return result


def factory_expression(c):
    """make_shared of a hand-written KerML class; relationships without a default constructor get placeholders for their ends."""
    text = c.text
    if re.search(r'\b' + c.name + r'\s*\(\s*\)\s*=\s*delete', text):
        ctors = [x for x in parameter_lists(text, c.name) if x.strip()]
        arguments = []
        for part in re.split(r',(?![^<]*>)', ctors[0]):
            if '=' in part:
                break
            t = clean_type(split_parameter(part))
            m = re.match(r'^std::shared_ptr<(\w+)>$', t)
            if m:
                arguments.append('placeholder<' + CLASSES[m.group(1)].qualified + '>()')
            elif t.startswith('std::vector<'):
                arguments.append('std::vector<std::shared_ptr<K::Type>>{}')
            else:
                raise SystemExit('cannot build ' + c.name + ' from ' + ctors[0])
        return 'std::make_shared<' + c.qualified + '>(' + ', '.join(arguments) + ')'
    return 'std::make_shared<' + c.qualified + '>()'


def build():
    out = ['// Generated by filehandling/tools/generate_xmi_bindings.py. Do not edit.\n',
           '#include "XmiBindings.h"\n',
           '#include <kerml/KerML.h>\n#include <sysml/SysML.h>\n',
           '#include <algorithm>\n#include <array>\n#include <iterator>\n#include <unordered_map>\n',
           '\nnamespace SysMLv2::Files::Xmi {\n\nnamespace {\n',
           'using KerML::Entities::Element;\n',
           'namespace K = KerML::Entities;\nnamespace S = SysMLv2::Entities;\n\n']
    used_enums = set()
    bindings = {}
    for c in CLASSES.values():
        for p in c.properties:
            if p['derived'] or p['name'] in SKIPPED:
                continue
            result = binding_for(c, p)
            if result:
                bindings[(c.name, p['name'])] = result
                e = enum_name_of(p)
                if e:
                    used_enums.add(e)
    for e in sorted(used_enums):
        out.append(enum_parser(e) + '\n')
    for key in sorted(bindings):
        out.append(bindings[key][1] + '\n')
    tables = []
    for c in sorted(CLASSES.values(), key=lambda x: x.name):
        seen = set()
        idents = []
        for ancestor in linearize(c):
            for p in ancestor.properties:
                if p['derived'] or p['name'] in SKIPPED or p['name'] in seen:
                    continue
                if (ancestor.name, p['name']) in bindings:
                    seen.add(p['name'])
                    idents.append('&' + bindings[(ancestor.name, p['name'])][0])
        tables.append((c, idents))
    for c, idents in tables:
        if not c.abstract:
            out.append('const PropertyBinding* const props_' + c.name + '[] = {' + ', '.join(idents + ['nullptr']) + '};\n')
    out.append('\n')
    for c, _ in tables:
        if c.abstract:
            continue
        out.append('ElementPtr create_' + c.name + '() {\n')
        if c.language == 'S':
            out.append('    return std::dynamic_pointer_cast<Element>(S::createRepresentation("' + c.name + '"));\n')
        else:
            out.append('    return ' + factory_expression(c) + ';\n')
        out.append('}\n')
    out.append('\nconst MetaclassBinding metaclassTable[] = {\n')
    for c, idents in tables:
        if c.abstract:
            out.append('    {"' + c.name + '", true, nullptr, nullptr, 0},\n')
        else:
            out.append('    {"' + c.name + '", false, &create_' + c.name + ', props_' + c.name + ', ' + str(len(idents)) + '},\n')
    out.append('};\n\n}  // namespace\n\n')
    out.append('const MetaclassBinding* findMetaclass(std::string_view name) {\n'
               '    static const std::unordered_map<std::string_view, const MetaclassBinding*> index = [] {\n'
               '        std::unordered_map<std::string_view, const MetaclassBinding*> result;\n'
               '        for (const auto& binding : metaclassTable) result.emplace(binding.name, &binding);\n'
               '        return result;\n'
               '    }();\n'
               '    const auto found = index.find(name);\n'
               '    return found == index.end() ? nullptr : found->second;\n'
               '}\n\n')
    derived = sorted({p['name'] for c in CLASSES.values() for p in c.properties if p['derived']} | SKIPPED)
    out.append('bool isDerivedProperty(std::string_view name) {\n    static const std::array<std::string_view, ' + str(len(derived)) + '> names = {\n')
    out.append(''.join('        "' + n + '",\n' for n in derived))
    out.append('    };\n    return std::binary_search(names.begin(), names.end(), name);\n}\n\n')
    out.append('std::size_t metaclassCount() {\n    return std::size(metaclassTable);\n}\n\n')
    out.append('}  // namespace SysMLv2::Files::Xmi\n')
    return ''.join(out)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    text = build()
    if args.check:
        if not OUTPUT.exists() or OUTPUT.read_text(encoding='utf8') != text:
            raise SystemExit('Generated file is stale: ' + str(OUTPUT.relative_to(ROOT)))
        print('verified')
    else:
        OUTPUT.parent.mkdir(parents=True, exist_ok=True)
        OUTPUT.write_text(text, encoding='utf8', newline='\n')
        print(str(sum(1 for c in CLASSES.values() if not c.abstract)) + ' concrete metaclasses; properties without a setter: ' + ', '.join(sorted(GAPS)))
