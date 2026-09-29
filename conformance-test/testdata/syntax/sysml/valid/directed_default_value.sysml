// expect: valid
// SysML 8.2.2.6.2: FeatureValue = '=' | ':=' | 'default' ( '=' | ':=' )?
calc def C {
    in clock : Clock[1] default enclosing.localClock;
    in a : Integer default = 1;
    in b : Integer default := 2;
    in c : Integer = 3;
}
