// expect: valid
package OperatorExpressions {
    attribute def Mass;
    part def Vehicle {
        attribute mass : Real = 2 * 3 + 1;
        attribute power : Real = 2 ** 3 ** 2;
        attribute negated : Real = -mass ** 2;
        attribute flag : Boolean = mass > 10 and not (mass == 20) or mass < 2;
        attribute pick : Real = if mass > 5 ? 1 else 2;
        attribute isMass : Boolean = mass istype Real;
        attribute cast = mass as Real;
        attribute indexed = values#(1);
        attribute chained = engine.cylinders.count;
        attribute sequence = (1, 2, 3);
        attribute range = 1 .. 10;
    }
}
