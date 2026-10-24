// expect: error
// SysML 8.2.2.16: a flow with 'from' requires 'to' FlowEndMember
part def Fahrzeug { part tank; part motor; flow of Kraftstoff from tank.ausgang; }
