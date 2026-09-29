// expect: valid
// KerML 8.2.4.3.1: EndFeaturePrefix ( OwnedCrossFeatureMember )? - the cross feature sits between 'end' and 'feature'.
assoc A {
    end [1] feature a references x;
    end [0..*] feature b : T;
    end p [*] ordered feature c : T;
}
