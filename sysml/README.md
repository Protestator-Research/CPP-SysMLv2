# SysML abstract representation

The `SysMLv2::Entities` C++ model covers the **93 classes, five enumerations and
218 directly declared properties** in the OMG SysML abstract syntax published at
<https://www.omg.org/spec/SysML/20250201/SysML.xmi>. This is the machine-readable
artifact referenced by SysML 2.0. The manifest also records the input SHA-256. The inventory is pinned in
`model/abstract_syntax.json`; generation never downloads a moving specification.

## Use

```cpp
#include <sysml/SysML.h>

using namespace SysMLv2::Entities;
auto vehicle = std::make_shared<PartDefinition>();
vehicle->setDeclaredName("Vehicle");
auto wheel = std::make_shared<PartUsage>();
wheel->setDeclaredName("wheel");
vehicle->appendOwnedFeature(wheel);
// Derived from KerML::Type::ownedFeature, preserving insertion order:
auto parts = vehicle->ownedPart();

auto element = createRepresentation("ActionUsage");
auto issues = element->validateRepresentation();
```

Individual headers live in `include/sysml/<package>/<Class>.h`; their implementations
live in `src/sysml/<package>/<Class>.cpp`. Constructors, destructors, property
accessors, metaclass names and validation are defined in these source files.
`src/sysml/AbstractSyntax.cpp` contains only the factory and metaclass inventory.
The generator also maintains the explicit CMake source list in `SysMLSources.cmake`.
Existing
`sysml/usage` and misspelled `sysml/attibutes` includes remain available;
`sysml/attributes` is the canonical attributes directory. Enum literals use the
OMG spelling, with a trailing underscore for C++ keywords (`StateSubactionKind::do_`).

All specified generalizations are represented by public inheritance. Virtual
inheritance ensures one `KerML::Entities::Element` identity even for connections,
flows and other diamond hierarchies. This changes the KerML ABI: rebuild clients
and libraries together. Missing KerML ancestors were added with their inheritance;
this does not implement their full semantic behavior.

## Properties and validation

* Getters use the existing `property()` naming convention. Stored properties have
  `setProperty(value)` and collections additionally have `appendProperty(value)`.
* Ordered collections preserve order. Unique collection setters reject duplicate
  references and null entries before changing the existing collection.
* Optional scalar/enumeration values use `std::optional`; references use nullable
  `std::shared_ptr`, following the existing KerML API.
* Objects can be constructed before all references are populated. Validation
  reports missing required references, invalid enumerations and multiplicity
  violations. `validateRepresentation(true)` also checks derived snapshots.
* `metaclasses()` lists every class, including abstract classes. The factory rejects
  abstract and unknown names. Abstract C++ types cannot be instantiated.

### Semantic boundary

This is a structural representation, **not a complete SysML semantic engine**.
The generated API distinguishes directly computed views from stored snapshots in
its property comments. Computed views currently include Definition owned usages,
Usage nested usages, typed definitions, owning usage/definition, directed usages,
variants and the reference/composite relationship. They use existing KerML
collections; those collections must be populated by the caller.

Other derived properties are explicit snapshots populated by an importer or
semantic evaluator. Setters do not evaluate OCL, update association opposites,
apply subset/redefinition constraints, resolve library specializations or keep
those snapshots synchronized after graph edits. Inherited KerML serialization
also does not yet round-trip the added SysML properties. These are outstanding
parts of full language conformance; the tests do not assert such conformance.

References follow KerML's shared ownership convention. Avoid strong ownership
cycles when populating snapshots and inverse links, or explicitly clear those
links when releasing a model.

## Generate and test

```sh
python3 sysml/tools/import_metamodel.py /path/to/SysML.xmi --check
python3 sysml/tools/generate_abstract_syntax.py
python3 sysml/tools/generate_abstract_syntax.py --check
cmake -S . -B build/model -DBUILD_WITH_PARSING=OFF \
  -DBUILD_WITH_SERVICES=OFF -DBUILD_WITH_REST=OFF
cmake --build build/model
ctest --test-dir build/model --output-on-failure
```

Supply the existing Conan toolchain when dependencies are installed through Conan.
The model tests require no parser, services, REST implementation or GTest.
They compile every concrete class, verify all declared generalizations and unique
Element conversion, and exercise identity, properties, derivation and validation.
The generator freshness test prevents edits to generated files from diverging
from their source. Installation includes the entire public header hierarchy.
