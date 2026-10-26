// expect: keyword-misuse 'perform' is not written after 'entry'
// SysML 8.2.2.17: after entry/do/exit no perform is written; correct: entry action init : Init; or entry init;
state def R { entry perform action init : Init; }
