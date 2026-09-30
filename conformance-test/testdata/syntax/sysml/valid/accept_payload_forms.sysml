// expect: valid
// SysML 8.2.2.17.4: PayloadFeature = Identification? PayloadFeatureSpecializationPart ValuePart? | OwnedFeatureTyping ( OwnedMultiplicity )? | OwnedMultiplicity OwnedFeatureTyping
action def A {
    action a1 accept p : Real via r;
    action a2 accept T via r;
    action a3 accept T[2] via r;
    action a4 accept [2] T;
    action a5 accept p : T[1] = v via r;
}
state def S {
    state x; state y;
    transition first x accept apayload : Anything via receiver then y;
    transition t2 first x accept ev : E then y;
    transition first x accept T then y;
}
