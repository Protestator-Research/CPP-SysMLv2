// expect: keyword-misuse 'class' is a reserved keyword
// every KerML keyword is reserved, also as a segment of a feature chain
class C { feature a; feature b = a.class; }
