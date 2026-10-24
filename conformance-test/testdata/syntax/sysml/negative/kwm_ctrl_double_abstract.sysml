// expect: error no-keyword-misuse
// a modifier keyword after a modifier keyword is no name
part def P { abstract
  abstract part b; }
