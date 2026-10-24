// expect: valid
// negative control: inv false negates an invariant
classifier B { feature x : Real; inv false { x > 1.0 } }
