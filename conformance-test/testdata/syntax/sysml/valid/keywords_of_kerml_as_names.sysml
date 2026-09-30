// expect: valid
// SysML 8.2.2.1.2: the KerML-only keywords are not reserved in SysML, also not as segments of qualified names
part def Metadata { item metadataItems; }
part def UsageX :> Metadata::step {
    derived ref item 'action' : ActionUsage[0..*] ordered subsets step, usage subsets Metadata::metadataItems;
    attribute type : Boolean;
    attribute trigger : Real;
    enum def Kind { enum trigger; enum guard; enum block; }
    ref feature :>> function::expr;
}
