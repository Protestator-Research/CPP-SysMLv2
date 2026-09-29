// expect: valid
// KerML 8.2.5.7.4 / 7.4.9.4: an invariant may be declared without name, 'inv true'/'inv false' are optional
behavior B {
    inv { true }
    private inv { false }
    inv false { true }
    inv true i1 subsets s { true }
    inv named { true }
    inv;
}
