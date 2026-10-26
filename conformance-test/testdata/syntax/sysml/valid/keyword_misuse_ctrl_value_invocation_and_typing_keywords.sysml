// expect: valid
// negative control: an invocation in a value and 'typed by' are fine
attribute def C { attribute v : Integer; }
part def P { attribute c : C = C(1); part d typed by P; }
