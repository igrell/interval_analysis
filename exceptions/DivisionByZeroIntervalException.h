#ifndef INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALEXCEPTION_H
#define INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALEXCEPTION_H

#include "Interval.h"

class DivisionByZeroIntervalException : public std::exception {
    Interval a = Interval();
    Interval b = Interval();

public:
    DivisionByZeroIntervalException() = default;

    DivisionByZeroIntervalException(const Interval &a, const Interval &b) : a(a), b(b) {}

    void warning_message() {
        cout << "Warning: encountered zero in division between intervals: " << a << " , " << b << "\n";
    }

};

#endif //INTERVAL_ANALYSIS_DIVISIONBYZEROINTERVALEXCEPTION_H
