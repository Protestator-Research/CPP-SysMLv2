// expect: error no-keyword-misuse
// 'then' after a bare 'entry' starts a new statement
state def S { entry
  then off; state off; }
