// expect: valid
// KerML 8.2.4.3.1: BasicFeaturePrefix = ... ( var | const )?; EndFeaturePrefix = const? end; readonly is a legacy alias of const
class C {
    var feature a;
    const feature b : T;
    abstract composite const feature c;
    readonly feature d;
    feature e;
}
assoc A {
    const end feature x;
    end feature y;
}
