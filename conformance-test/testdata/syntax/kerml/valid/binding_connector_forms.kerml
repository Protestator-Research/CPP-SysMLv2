// expect: valid
// KerML 8.2.5.5.2: BindingConnectorDeclaration uses '=' and accepts multiplicities on the ends
class C {
    feature a;
    feature b;
    binding a = b;
    binding of a = b;
    binding all a = b;
    binding x of a = b;
    binding [0..1] a.c = [1] b;
    private binding instant[n] of [0..1] a = [0..1] b { }
    binding;
}
