// expect: error
// SysML 8.2.2.16: FlowEndSubsetting 'tank.' (QualifiedName followed by the implied '.') must be followed by a FlowFeature
part def Fahrzeug { part tank; part motor; flow tank. to motor.eingang; }
