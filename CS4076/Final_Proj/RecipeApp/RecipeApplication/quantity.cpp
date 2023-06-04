#include "quantity.h"

Quantity::Quantity(double value, bool ounces) : isOunces(ounces) {
    if (isOunces) {
        ounces = value;
    } else {
        grams = value;
    }
}


