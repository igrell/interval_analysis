#ifndef INTERVAL_ANALYSIS_EMPTYINTERSECTIONEXCEPTION_H
#define INTERVAL_ANALYSIS_EMPTYINTERSECTIONEXCEPTION_H

#include "../interval_arithmetic_tools/Interval.h"

class EmptyIntersectionException : public std::exception {
    Interval a = Interval();
    Interval b = Interval();

public:

    EmptyIntersectionException() = default;

    EmptyIntersectionException(const Interval &a, const Interval &b) : a(a), b(b) {}

    void message() {
        cout << "Warning: empty intersection between intervals: " << a << " && " << b << "\n";
    }

};

#endif //INTERVAL_ANALYSIS_EMPTYINTERSECTIONEXCEPTION_H
