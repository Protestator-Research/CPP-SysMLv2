// expect: valid
// negative control: a reserved keyword written as an unrestricted name is a valid name
action def T { then action 'send' { in cs : Integer; } }
