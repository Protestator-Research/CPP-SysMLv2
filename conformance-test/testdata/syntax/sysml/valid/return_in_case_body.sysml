// expect: valid
// The standard library declares result parameters of case definitions with 'return' (CaseDefinition is a CalculationDefinition)
abstract case def Case {
    subject subj default Case::result;
    objective obj;
    return ref result[0..*] {
        doc /* The result. */
    }
    abstract case subcases : Case[0..*] :> cases;
}
abstract verification def VerificationCase :> Case {
    subject subj :>> Case::subj;
    return verdict : VerdictKind :>> result;
}
