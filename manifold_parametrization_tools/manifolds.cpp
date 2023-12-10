#ifndef MANIFOLDS
#define MANIFOLDS

#include "iostream"
#include "vector"
#include "Eigen/Eigen"
#include "autodiff/Autodiff.h"

using namespace Eigen;
using std::cout, std::cin, std::endl, std::vector, std::tuple;

void parametrizeManifold(vector<vector<double>> &differentialMatrix, const unsigned n) {
//    Matrix<double, n,n>
}

template<typename T>
vector<T> fun(T x, T y, T z) {
    return {(2 * x) + (x * x) + (y * z), (3 * y) + (x * y) - (z * z), (5 * z) + (y * y) + (2 * x * z)};
}

template<typename T>
vector<T> fun2(T x, T y, T z) {
    return {x, y, z};
}

// f(x,y) = ( (0 + x + y + x2 - 5xy - 2y2)/(1 + x - 4y), (1 + 2x - y + x2 - 4xy + 8y2)/(1 - 2x + 8y) )
int main() {
    const unsigned N = 8;
    vector<double> p = {0., 0.5};
    const unsigned n = p.size();
    vector<double> L1 = {0., 1., 1., 1., -5., -2.};
    vector<double> M1 = {1., 1., -4.};
    vector<double> L2 = {1., 2., -1., 1., -4., 8.};
    vector<double> M2 = {1., -2., 8.};

    double x = 0;
    double y = 0;
    double z = 0;
    unsigned noOfVars = 3;
    auto resVec = fun2(FunJet(x, 0, noOfVars), FunJet(y, 1, noOfVars), FunJet(z, 2, noOfVars));
    cout << "f x  y z\n";
    for (auto &res: resVec) {
        cout << res << "\n";
    }
}

#endif