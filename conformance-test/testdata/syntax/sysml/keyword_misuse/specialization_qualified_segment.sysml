// expect: keyword-misuse 'part' is a reserved keyword
// a reserved keyword as a segment of a qualified name in a specialization
part def P { part b :> P::part; }
