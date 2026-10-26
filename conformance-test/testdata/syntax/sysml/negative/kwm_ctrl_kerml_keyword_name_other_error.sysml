// expect: error no-keyword-misuse
// 'feature' is a name in SysML v2 and is not flagged, the error is the missing value
part def P { part feature; attribute x [0..*] = ; }
