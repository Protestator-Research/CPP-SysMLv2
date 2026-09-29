// expect: valid
package CalculationsAndConstraints {
    calc def Half { in x : Real; return : Real; x / 2 }
    calc def Weighted { in a : Real; in b : Real; (a * 3 + b) / 4 }
    constraint def Bounded { in v : Real; v >= 0 and v <= 100 }
    part def Tank {
        attribute level : Real;
        constraint ok { level > 0 and level < 10 }
    }
}
