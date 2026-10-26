// expect: valid
metaclass M { feature id : ScalarValues::Natural; }
class C {
    feature x;
    metadata M;
    metadata M about x;
    @M about x { id = 1; }
}
