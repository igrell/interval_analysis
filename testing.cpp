#include "Interval.h"
#include "Henon.h"
#include "vector"
#include "iostream"
#include "TaylorPol.h"

int main() {
    TaylorPol<double> p({1,1,1});
    TaylorPol<double> q({2,2,2});
    std::cout << factorial()
    auto diffs = p.getDiffs();
//    Henon henon(1.0,1.0,1);
//    std::vector<Interval> vec{Interval(1,2), Interval(3,4)};
//    std::cout << henon(vec)[0] << " " << henon(vec)[1];
}