// expect: valid
// negative control: assert not is a negated assertion, not a misused inv not
part def P { attribute x : Integer; assert not constraint c { x > 1 } }
