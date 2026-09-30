// expect: valid
// SysML 8.2.2.6.6: MultiplicityPart = OwnedMultiplicity | ( OwnedMultiplicity )? ( 'ordered' ( 'nonunique' )? | 'nonunique' ( 'ordered' )? )
part def P {
    attribute a : Integer ordered;
    attribute b : Integer nonunique;
    attribute c : Integer ordered nonunique;
    attribute d : Integer nonunique ordered;
    attribute e : Integer[0..*] nonunique ordered;
    ref f : Integer nonunique;
    part g : Q[2] ordered;
}
