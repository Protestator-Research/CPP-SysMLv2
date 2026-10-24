// expect: error no-keyword-misuse
// the target of ':>' is missing
part def P { part x :>
  part y; }
