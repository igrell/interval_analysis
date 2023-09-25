#include "Interval.h"
#include "EmptyIntersectionException.h"
#include "Autodiff.h"

using std::pair;

Interval
IntervalNewtonStep(double (*f)(const double &), FunJet<Interval> (*F)(const FunJet<Interval> &), const Interval &x) {
    double mid = x.center(); // enclosure choice
    Interval N = mid - Interval(f(mid)) / autodiff<Interval>(F, x).second;
    return N && x;
}

// template<typename T>
void IntervalNewton(double (*f)(const double &), FunJet<Interval> (*F)(const FunJet<Interval> &), Interval x, const unsigned long TOL) {
    Interval x0 = x;
    while (x.width() > TOL) {
        try {
            x = IntervalNewtonStep(f, F, x);
        } catch (EmptyIntersectionException()) {
            std::cout << "No zeros in the given domain.\n";
            return;
        }
        std::cout << x << "\n";
    }
    if (x < x0) std::cout << "There is a unique zero in the final interval.\n";
}

int main() {
    return 0;
}