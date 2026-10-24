// expect: keyword-misuse an invariant is negated with 'inv false'
// KerML 8.2.3.4: an invariant is negated with inv false, inv not is invalid
classifier B { inv not { x > 1.0 } }
