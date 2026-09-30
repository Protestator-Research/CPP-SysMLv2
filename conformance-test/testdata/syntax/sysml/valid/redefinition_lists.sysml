// expect: valid
part def P {
    part a :>> x, y::z, w;
    attribute b subsets p, q, r;
    ref c : T, U :>> x;
    ref occurrence :>> Action::this, actions::this, subperformances::this = (that as Action).this { }
}
