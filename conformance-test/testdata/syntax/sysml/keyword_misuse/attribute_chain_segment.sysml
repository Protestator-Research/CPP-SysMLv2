// expect: keyword-misuse 'send' is a reserved keyword
// a reserved keyword as the last segment of a feature chain in an expression
part def P { part a; attribute x = a.send; }
