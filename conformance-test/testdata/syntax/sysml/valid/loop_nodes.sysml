// expect: valid
// SysML 8.2.2.17.7: the 'until' clause of a while loop is optional
action def L {
    while x < 3 { assign x := x + 1; }
    while x < 3 { assign x := x + 1; } until x > 10;
    loop { perform body; } until done;
    loop { perform body; }
    for i in 1..3 { perform body; }
}
