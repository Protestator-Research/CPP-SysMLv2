// expect: keyword-misuse an invocation is not allowed in a typing
// an invocation is not allowed in a typing; use a body binding or = C(payload)
action def T { action c : C(payload); }
