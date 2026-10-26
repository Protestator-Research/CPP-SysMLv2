// expect: error
// SysML 8.2.2.16: a message with 'from' requires 'to' MessageEventMember
part def Fahrzeug { part tank; part motor; message of Signal from tank; }
