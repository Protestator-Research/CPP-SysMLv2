// expect: error no-keyword-misuse
// a missing ';' in front of 'do' is a plain syntax error, not a reserved word used as a name
state def S { entry action a
  do action b; }
