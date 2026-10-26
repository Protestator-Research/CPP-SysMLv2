// expect: valid
// SysML 8.2.2.6.5 / 8.2.2.12: PortUsage typing: TypedBy = DEFINED_BY FeatureTyping; Typings = TypedBy ( ',' FeatureTyping )*; FeatureTyping = OwnedFeatureTyping | ConjugatedPortTyping (8.2.2.6.5); ConjugatedPortTyping (8.2.2.12) = '~' QualifiedName
port def P;
port def KraftPort;
part def Motor { port ausgang : KraftPort; }
part def Getriebe { port eingang : ~KraftPort; }
interface def Kupplung {
    end p1 : KraftPort;
    end p2 : ~KraftPort;
}
part system {
    part motor : Motor;
    part getriebe : Getriebe;
    interface : Kupplung connect motor.ausgang to getriebe.eingang;
}
port p : ~P;
port q : ~a::P;
port s : ~P [2];
port t : P, ~P;
port u : ~P, Q;
