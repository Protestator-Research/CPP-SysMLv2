// expect: error no-keyword-misuse
// 'state' after a bare 'entry' starts a new statement
state def S { entry
  state a; }
