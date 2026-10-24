// expect: valid
// SysML 8.2.2.6.5 / 8.2.2.12: PortUsage typing: TypedBy = DEFINED_BY FeatureTyping; Typings = TypedBy ( ',' FeatureTyping )*; FeatureTyping = OwnedFeatureTyping | ConjugatedPortTyping (8.2.2.6.5); ConjugatedPortTyping (8.2.2.12) = '~' QualifiedName
port p : ~P;
