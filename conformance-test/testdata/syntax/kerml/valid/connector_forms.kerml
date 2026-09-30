// expect: valid
// KerML 8.2.5.5.1: Connector = FeaturePrefix 'connector' ( FeatureDeclaration? ValuePart? | ConnectorDeclaration ) TypeBody
class C {
    feature a; feature b; feature c;
    connector;
    connector k : T[n] { }
    connector k2 : T = 1;
    connector [0..1] a to [1..*] b;
    private connector [0..1] l to [1..*] b;
    connector m : T from a to b;
    connector all from a to b;
    connector all a to b;
    connector (a, b, c);
    connector n (a, b);
    connector e from [1] x references a to [0..*] y references b;
    abstract connector z : T from a to b { doc /* text */ }
}
