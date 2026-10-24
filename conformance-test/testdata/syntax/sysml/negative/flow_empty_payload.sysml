// expect: error
// SysML 8.2.2.16: 'of' requires a FlowPayloadFeatureMember
part def Fahrzeug { part tank; part motor; flow of from tank.ausgang to motor.eingang; }
