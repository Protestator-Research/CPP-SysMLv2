// expect: valid
// KerML 8.2.4.1.6: TypeFeatureMember = MemberPrefix 'member' FeatureElement
datatype VisibilityKind {
    member feature 'private' : VisibilityKind[1];
    private member feature 'protected' : VisibilityKind[1];
    public member feature 'public' : VisibilityKind[1];
}
