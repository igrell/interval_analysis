#include "Interval.h"
#include "Henon.h"
#include "vector"
#include "iostream"
#include "TaylorPol.h"
#include "TaylorAD.h"
#include "cmath"

double fun(double x) { return x*x; }

template<int R, typename F>
double applyFun(F f, double a) {
    const int originalRounding = fegetround();
    fesetround(R);
    double res = f(a);
    fesetround(originalRounding);
    return res;
}

int main() {
    std::cout << applyFun<0>(fun, 4);

//    TaylorPol<double> p0({0,1,0,-0.1666667,0,0.0083333333,0,-0.000198413});
//    TaylorJet<double> jet({p0});
//    std::cout << jet.diffAt(1);
}