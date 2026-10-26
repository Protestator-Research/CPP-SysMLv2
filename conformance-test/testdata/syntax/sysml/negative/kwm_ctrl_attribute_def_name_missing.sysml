// expect: error no-keyword-misuse
// the name after 'attribute def' is missing: the next statement is no name
part def P { attribute def
  part def X; }
