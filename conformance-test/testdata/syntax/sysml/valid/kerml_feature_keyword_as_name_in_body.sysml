// expect: valid
// SysML wins where an input reads both ways: 'feature' stays a name when no declaration follows it
part def P {
    in feature : Integer;
    out feature;
    feature;
    ref feature :>> function::expr;
    attribute feature : Integer;
    in feature x : Integer;
}
