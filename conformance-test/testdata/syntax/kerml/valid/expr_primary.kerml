// expect: valid
package PrimaryExpressions {
    feature chain = a.b.c;
    feature indexed = m#(1);
    feature indexedTwice = m#(1)#(2);
    feature indexedChain = m#(1).name;
    feature unit = 273.15 [K];
    feature quantity = 1 + 2 [m] * 3;
    feature sequence = (1, 2, 3);
    feature trailing = (1, 2, );
    feature empty = ();
    feature nothing = null;
    feature selected = s.?{ in x; x > 0 };
    feature collected = s.{ in x; x * 2 };
    feature invoked = s->select { in x; x > 0 };
    feature reduced = s->reduce '+';
    feature counted = s->size();
    feature call = f(a, b + 1);
    feature named = f(x = 1, y = a == b);
    feature method = stats.avg();
    feature created = new Member("Jane", "Doe", 1234, null);
    feature createdNamed = new Member(firstName = "John", memberNumber = 1 + 1);
    feature access = x.metadata;
    feature nestedBody = { in x; x + 1 };
}
