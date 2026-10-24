// expect: error no-keyword-misuse
// SysML v2 has no invariants: 'inv' is an ordinary name, so 'inv not' is not the KerML misuse
part def P { attribute inv : Boolean; constraint c { inv not true } }
