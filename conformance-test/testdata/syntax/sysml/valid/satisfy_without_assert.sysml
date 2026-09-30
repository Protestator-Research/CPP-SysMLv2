// expect: valid
// SysML 7.21.4: 'satisfy requirement' and 'satisfy' may be declared without 'assert'; 'assert not' negates
requirement def R;
part def V;
part v : V;
satisfy R by v;
satisfy requirement r1 : R by v { doc /* body */ }
satisfy requirement r2 : R by that { }
assert satisfy R by v;
assert not satisfy R by v;
