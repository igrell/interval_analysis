#ifndef INTERVAL_ANALYSIS_INTERVALFORMATPOLICY_H
#define INTERVAL_ANALYSIS_INTERVALFORMATPOLICY_H

#include "iostream"
#include "sstream"
#include "Interval.h"
#include "bits/stdc++.h"

using std::cout, std::ostream, std::setprecision;

struct LoHiFormat {
    static ostream& printInterval(ostream& ostream, const Interval& interval) {
        ostream << "[" << setprecision(17) << interval.get_lo() << "," << interval.get_hi() << "]";
        return ostream;
    }
};

struct HiLoFormat {
    static ostream& printInterval(ostream& ostream, const Interval& interval) {
        ostream << "[" << setprecision(17) << interval.get_hi() << "," << interval.get_lo() << "]";
        return ostream;
    }
};

#endif //INTERVAL_ANALYSIS_INTERVALFORMATPOLICY_H
