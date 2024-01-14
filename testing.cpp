#include "Interval.h"
#include "Henon.h"
#include "vector"
#include "iostream"
#include "TaylorPol.h"
#include "TaylorAD.h"
#include "cmath"

int main() {
    TaylorPol<double> p0({1,2,3});
    TaylorPol<double> p1({4,5,6});
    TaylorPol<double> p2({7,8,9});
    TaylorJet<double> jet({p0,p1,p2});
    std::cout << jet.diffAt(2);
}