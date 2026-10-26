// expect: error no-keyword-misuse
// 'then' after a decide without ';'
action def A { decide
  then b; action b; }
