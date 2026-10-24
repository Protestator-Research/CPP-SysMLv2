// expect: keyword-misuse 'send' is a reserved keyword
// SysML 8.2.2.1.2: send is a reserved keyword and cannot name a usage; the diagnosis must say so instead of "mismatched input"
action def T { then action send { in cs : Integer; } }
