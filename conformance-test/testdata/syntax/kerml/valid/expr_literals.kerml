// expect: valid
package LiteralExpressions {
    feature flag = true;
    feature other = false;
    feature text = "hello";
    feature whole = 42;
    feature real = 3.14;
    feature small = 0.5;
    feature exponent = 2e3;
    feature realExponent = 1.5e-3;
    feature unbounded = *;
}
