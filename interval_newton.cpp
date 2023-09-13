#include "Interval.h"
#include "EmptyIntersectionException.h"
#include "Autodiff.h"

using std::pair;

Interval
IntervalNewtonStep(double (*f)(const double &), FunJet<Interval> (*F)(const FunJet<Interval> &), const Interval &x) {
    double mid = x.center(); // enclosure choice
    Interval N = mid - Interval(f(mid)) / autodiff<Interval>(F, x).second;
    return x && N;
}
// template<typename T>
void IntervalNewton(double (*f)(const double &), FunJet<Interval> (*F)(const FunJet<Interval> &), Interval x, const size_t TOL) {
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

// TODO
template<typename T>
T fun(const T &x) {
    return x * x + T(-2);
}

int main() {
    Interval x{1, 3};
    IntervalNewton(fun<double>, fun<FunJet<Interval>>, x, static_cast<size_t>(10e-4));
    return 0;
}