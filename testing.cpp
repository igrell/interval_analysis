#include "Interval.h"
#include "iostream"

int main() {
    Interval x{0.01,0.99};
    Interval y{-0.33,0.27};
    auto f = [](auto x, auto y){ return 3.8*x*(1-x) - 0.1*y;};
    std::cout << f(x,y);
}