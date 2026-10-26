// expect: valid
metadata def M;
part def P {
    metadata m : M;
    metadata n defined by M;
}
