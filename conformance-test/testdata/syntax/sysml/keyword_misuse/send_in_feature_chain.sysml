// expect: keyword-misuse 'send' is a reserved keyword
// a reserved keyword is not allowed as a segment of a feature chain either
part def P { part a { port b; } flow a.b to send.cs; }
