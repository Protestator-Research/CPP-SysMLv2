// expect: valid
package ArithmeticExpressions {
    feature sum = 2 * 3 + 1;
    feature difference = 10 - 4 - 3;
    feature remainder = 8 / 2 % 3;
    feature tower = 2 ** 3 ** 2;
    feature caret = a ^ b ^ c;
    feature negated = -x ** 2;
    feature positive = +x;
    feature complement = ~x;
    feature grouped = (1 + 2) * 3;
    feature span = 1 .. 2 + 3;
    feature mixed = -w + x * y * z + a ^ b ^ c;
}
