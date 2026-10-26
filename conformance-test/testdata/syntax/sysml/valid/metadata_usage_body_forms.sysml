// expect: valid
metadata def M { attribute b : Natural; attribute c : Natural; attribute d : Natural; }
part def P {
    metadata M {
        b = 1;
        :>> b = 2;
        redefines b = 3;
        c { d = 3; }
    }
    #M metadata M;
}
