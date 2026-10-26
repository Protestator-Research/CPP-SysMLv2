// expect: valid
// negative control: perform action is allowed in a part definition
action def Act; part def P { perform action x : Act; }
