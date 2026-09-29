// expect: valid
package LogicalExpressions {
    feature disjunction = a or b and c;
    feature bitwise = a | b xor c & d;
    feature implication = a implies b or c;
    feature coalescing = list#(i) ?? fallback;
    feature negation = not a and b;
    feature relational = a < b or c >= d;
    feature equality = a == b and c != d;
    feature identity = a === b or c !== d;
    feature guarded = i > 0 and sensor#(i) != null;
    feature conditional = if a ? 1 else 2;
    feature nestedConditional = if a ? 1 else if b ? 2 else 3 + 4;
    feature absolute = if x >= 0 ? x else -x;
}
