// expect: valid
// KerML 8.2.4.3.1: MultiplicityPart = OwnedMultiplicity | ( OwnedMultiplicity )? ( 'ordered' ( 'nonunique' )? | 'nonunique' ( 'ordered' )? )
class C {
    feature a : T ordered;
    feature b : T nonunique;
    feature c : T ordered nonunique;
    feature d : T nonunique ordered;
    feature e : T[0..*] nonunique ordered;
    feature f[1] ordered;
}
