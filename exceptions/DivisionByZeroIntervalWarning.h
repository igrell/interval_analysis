#ifndef INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALWARNING_H
#define INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALWARNING_H

#include "../interval_arithmetic_tools/Interval.h"

class DivisionByZeroIntervalWarning : public std::exception {
    Interval a = Interval();
    Interval b = Interval();

public:
    DivisionByZeroIntervalWarning() = default;

    DivisionByZeroIntervalWarning(const Interval &a, const Interval &b) : a(a), b(b) {}

    void warning_message() {
        cout << "Warning: encountered zero in division between intervals: " << a << " , " << b << "\n";
    }

};

#endif //INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALWARNING_H
