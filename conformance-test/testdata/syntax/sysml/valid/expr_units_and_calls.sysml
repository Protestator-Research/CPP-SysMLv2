// expect: valid
package UnitsAndCalls {
    part def Sensor {
        attribute temperature : Real = 273.15 [K];
        attribute reading = temperature + 1 [K];
        attribute total = sum(values);
        attribute named = scale(factor = 2, value = reading);
        attribute selected = values->select { in x; x > 0 };
        attribute collected = values.{ in x; x * 2 };
        attribute created = new Reading(1, 2);
    }
}
