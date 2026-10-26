// expect: error no-keyword-misuse
// 'then' after a fork without ';'
action def A { fork
  then b; }
