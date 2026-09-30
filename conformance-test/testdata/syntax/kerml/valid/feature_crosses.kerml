// expect: valid
// KerML 8.2.4.3.1: Crosses = CROSSES OwnedCrossSubsetting (feature chains allowed)
assoc all SelfLink specializes BinaryLink {
    end feature thisThing : Anything redefines source subsets sameThing crosses sameThing.self;
    end feature other : Anything redefines target => thisThing.others;
    feature f : T crosses a;
}
