// expect: valid
// KerML features written with the keyword 'feature' in the bodies of SysML usages
part def Engine;
part p : Engine {
    in feature a : Integer;
    out feature b : Real[0..1] = 3;
    derived feature c;
    part q {
        feature d : Integer;
    }
}
item i { feature a : Integer; }
attribute x : Integer { feature a : Integer; }
port pt { inout feature a : Integer; }
