"""A thin helper around the SysML v2 API JSON elements of a parsed model."""

from __future__ import annotations

from typing import Any, Dict, Iterable, Iterator, List, Optional, Set

Element = Dict[str, Any]


class Model:
    """The model the parser created for a text: SysML v2 API JSON objects (plain dicts), one per element.

    The first element is the root namespace of the text. Elements refer to each other by ``{"@id": "..."}``
    references; :meth:`resolve` follows them. Elements of the standard library and other targets outside the text are
    *not* part of the model: references to them cannot be resolved (``None``). The ``@id`` values are random UUIDs, new
    for every request. Implied relationships (an implicit specialization of a ``part def`` to ``Parts::Part`` ...) are
    not materialized by the parser and therefore missing.

    The elements stay plain dicts; do not modify them.
    """

    def __init__(self, elements: Iterable[Element]) -> None:
        self._elements: List[Element] = list(elements)
        self._by_id: Dict[str, Element] = {}
        self._by_qualified_name: Dict[str, Element] = {}
        for element in self._elements:
            identifier = element.get("@id")
            if isinstance(identifier, str):
                self._by_id.setdefault(identifier, element)
            qualified_name = element.get("qualifiedName")
            if isinstance(qualified_name, str):
                self._by_qualified_name.setdefault(qualified_name, element)

    @property
    def elements(self) -> List[Element]:
        """All elements in the order of the parser (the root namespace first)."""
        return self._elements

    @property
    def root(self) -> Optional[Element]:
        """The root namespace of the text (first element), ``None`` for an empty model."""
        return self._elements[0] if self._elements else None

    def __len__(self) -> int:
        return len(self._elements)

    def __iter__(self) -> Iterator[Element]:
        return iter(self._elements)

    def __repr__(self) -> str:
        return f"Model({len(self._elements)} elements)"

    def by_id(self, identifier: str) -> Optional[Element]:
        """The element with this ``@id``, or ``None``."""
        return self._by_id.get(identifier)

    def resolve(self, ref: Any) -> Any:
        """Follows a reference.

        ``{"@id": ...}`` gives the element or ``None``; a list gives the list of the elements that could be resolved
        (references to elements outside the model are dropped); ``None`` gives ``None``.
        """
        if ref is None:
            return None
        if isinstance(ref, dict):
            identifier = ref.get("@id")
            return self._by_id.get(identifier) if isinstance(identifier, str) else None
        if isinstance(ref, (list, tuple)):
            resolved = (self.resolve(item) for item in ref)
            return [item for item in resolved if item is not None]
        raise TypeError(f"cannot resolve {type(ref).__name__}")

    def of_type(self, type_name: str) -> List[Element]:
        """The elements whose ``@type`` is exactly ``type_name`` (no subtype matching), e.g. ``"PartDefinition"``."""
        return [element for element in self._elements if element.get("@type") == type_name]

    def find(self, qualified_name: str) -> Optional[Element]:
        """The element with this qualified name (without quotes, e.g. ``"P::A"``), or ``None``."""
        return self._by_qualified_name.get(qualified_name)

    def owned_relationships(self, element: Element) -> List[Element]:
        """The relationships owned by ``element`` (``ownedRelationship``), e.g. its memberships."""
        refs = element.get("ownedRelationship") or []
        if isinstance(refs, dict):
            refs = [refs]
        return list(self.resolve(refs))

    def owned_elements(self, element: Element) -> List[Element]:
        """The elements owned by ``element`` through its relationships.

        Follows ``ownedRelationship`` and then ``ownedRelatedElement`` of each relationship, so for a package the
        members it declares (the relationships themselves are not included, see :meth:`owned_relationships`).
        The ``ownedElement`` member of the JSON is not used: it mixes relationships and their contents.
        """
        seen: Set[Any] = set()
        result: List[Element] = []
        for relationship in self.owned_relationships(element):
            related = relationship.get("ownedRelatedElement") or []
            if isinstance(related, dict):
                related = [related]
            for child in self.resolve(related):
                identifier = child.get("@id")
                if identifier not in seen:
                    seen.add(identifier)
                    result.append(child)
        return result
