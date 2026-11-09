// expect: valid
// KerML features written with the keyword 'feature' in the bodies of behavior definitions
action def A { in feature x : Integer; out feature y : Integer; }
state def S { in feature x : Integer; }
calc def C { in feature x : Integer; return feature r : Integer; }
case def K { in feature x : Integer; }
analysis def An { in feature x : Integer; }
verification def V { in feature x : Integer; }
use case def U { in feature x : Integer; }
action act { in feature x : Integer; }
state st { in feature x : Integer; }
calc cl { in feature x : Integer; }
