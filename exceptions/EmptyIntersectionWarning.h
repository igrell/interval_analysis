#ifndef INTERVAL_ANALYSIS_EMPTYINTERSECTIONWARNING_H
#define INTERVAL_ANALYSIS_EMPTYINTERSECTIONWARNING_H

#include "../interval_arithmetic_tools/Interval.h"

class EmptyIntersectionWarning : public std::exception {
    Interval a = Interval();
    Interval b = Interval();

public:
    EmptyIntersectionWarning() = default;

    EmptyIntersectionWarning(const Interval &a, const Interval &b) : a(a), b(b) {}

    void warning_message() {
        cout << "Warning: empty intersection between intervals: " << a << " && " << b << "\n";
    }

};

#endif //INTERVAL_ANALYSIS_EMPTYINTERSECTIONWARNING_H
