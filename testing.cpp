#include "Interval.h"
#include "Henon.h"
#include "vector"
#include "iostream"
#include "TaylorPol.h"
#include "TaylorAD.h"

int main() {
    TaylorPol<double> p({1,1,1});
    TaylorPol<double> q({2,2,2});
//    std::cout << p * q << "\n";
    TaylorJet<double> jet1({p,q});
    TaylorJet<double> jet2({q,p});
    auto order = jet1.getOrder();
//    TaylorJet<double> jet3(order);
//    jet1.polAt(0) = q;
    std::cout << jet1 * jet2 << "\n";
    for (auto el : jet1.diffAt(0)) std::cout << el;
//    Henon henon(1.0,1.0,1);
//    std::vector<Interval> vec{Interval(1,2), Interval(3,4)};
//    std::cout << henon(vec)[0] << " " << henon(vec)[1];
}