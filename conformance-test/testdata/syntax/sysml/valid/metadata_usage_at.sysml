// expect: valid
metadata def M { attribute id : Natural; }
part def P {
    @M;
    @M { id = 1; }
}
