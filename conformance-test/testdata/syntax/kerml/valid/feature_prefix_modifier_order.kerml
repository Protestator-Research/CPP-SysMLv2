// expect: valid
// KerML 8.2.4.3.1: BasicFeaturePrefix = direction? derived? abstract? ( composite | portion )? var?
class C {
    derived composite var feature a : T[0..*] ordered subsets p, q;
    abstract portion var feature b;
    in derived abstract composite var feature c : T;
    composite feature d;
    var feature e;
}
