// expect: valid
// KerML 8.2.4.3.1: Redefines and Subsets may list several features
class C {
    feature a redefines x, y::z, w;
    feature b subsets p, q, r;
    feature c :> p, q :>> x, y;
    feature d : T, U, V;
}
