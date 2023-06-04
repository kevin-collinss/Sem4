#ifndef UNITCONVERSION_H
#define UNITCONVERSION_H

//TEMPLATE CLASS
template <typename T>
T convertUnit(T value, bool toGrams) {
    const double gramsToOunces = 0.03527396;
    if (toGrams) {
        return static_cast<T>(value / gramsToOunces);
    } else {
        return static_cast<T>(value * gramsToOunces);
    }
}

#endif // UNITCONVERSION_H
