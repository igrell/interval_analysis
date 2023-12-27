#include "Interval.h"
#include "Henon.h"
#include "vector"
#include "iostream"

int main() {
    Henon henon(1.0,1.0,1);
    std::vector<Interval> vec{Interval(1,2), Interval(3,4)};
    std::cout << henon(vec)[0] << " " << henon(vec)[1];
}