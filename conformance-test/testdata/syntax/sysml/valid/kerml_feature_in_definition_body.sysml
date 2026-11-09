// expect: valid
// KerML features written with the keyword 'feature' in the bodies of SysML definitions
part def P {
    in feature a : Integer;
    out feature b : Real[0..1] = 3;
    inout feature c;
    derived feature d : Integer;
    abstract feature e;
    feature f : Integer[0..*] ordered;
}
item def I { in feature a : Integer; }
attribute def A { out feature b : Real; }
port def Q { inout feature c : Integer; }
interface def IF { in feature d : Integer; end feature e; }
requirement def R { in feature a : Integer; }
constraint def C { in feature a : Boolean; }
