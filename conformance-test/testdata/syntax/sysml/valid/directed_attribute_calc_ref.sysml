// expect: valid
// SysML 8.2.2.17.1: NonBehaviorBodyItem contains NonOccurrenceUsageMember, so directed attributes, calcs and refs are allowed in action/calc bodies
calc def C {
    in attribute a [0..*];
    inout attribute b : Integer;
    in calc f { in x; return y = x; }
    in ref r : T;
    out ref :>> res = a;
    in x default 1;
    return z : Integer;
}
action def A {
    in attribute a : Integer;
    out ref r;
    in calc c : Cc;
}
