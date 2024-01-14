#include "Interval.h"
#include "EmptyIntersectionException.h"
#include "FAD.h"

using std::pair;

template<typename T>
T func(T x) { return exp(x) - 10; }

template<class Fun>
Interval IntervalNewtonStep(Fun f, const Interval &x) {
    double mid = x.center(); // enclosure choice
    Interval N = mid - (Interval(f(mid)) / autodiff(f, x).get_dx());
    return N && x;
}

template<class Fun>
void IntervalNewton(Fun f, Interval x, const unsigned long TOL) {
    Interval x0 = x;
    while (x.width() > TOL) {
        try { x = IntervalNewtonStep(f, x); } catch (EmptyIntersectionException &warning) {
            std::cout << "No zeros in the given domain.\n";
            return;
        }
        std::cout << x << "\n";
    }
    if (x < x0) std::cout << "There is a unique zero in the final interval.\n";
}

int main() {
    IntervalNewton([](auto x) { return func(x); }, Interval(-1, 1), static_cast<unsigned long>(0.001));
    return 0;
}