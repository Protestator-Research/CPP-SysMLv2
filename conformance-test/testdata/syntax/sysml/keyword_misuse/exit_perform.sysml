// expect: keyword-misuse 'perform' is not written after 'exit'
// after exit no perform is written
state def R { exit perform action done : Done; }
