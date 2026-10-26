// expect: valid
// KerML-style metadata (`typed by`, `feature` body members) and KerML constructs stay valid in SysML text.
metadata def M { attribute x : Natural; attribute y : Natural; }
part def A;
part def P {
    metadata m typed by M;
    metadata M { feature x = 1; }
    metadata n : M about A { feature x = 1; :>> y = 2; }
    function decode {
        in feature value : Integer;
        return feature isSet : Boolean = value > 0;
    }
}
