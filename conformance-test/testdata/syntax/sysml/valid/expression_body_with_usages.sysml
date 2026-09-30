// expect: valid
// The body of an expression in SysML may contain usages such as 'in x;' and 'in ref a { ... }'
calc def C {
    in seq : Integer[0..*];
    in value : Integer;
    private attribute position : Natural[1] = (1..size(seq))->selectOne{in i; seq#(i) == value};
    return selected : Anything = seq->selectOne { in ref a { doc /* the element */ } test(selected = a) };
    return samples = seq->collect { in x; new Sample(x, f(x)) };
}
