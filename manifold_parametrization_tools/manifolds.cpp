#ifndef MANIFOLtotalDifferentialS
#define MANIFOLtotalDifferentialS

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

vector<vector<double>> totalDifferential(const vector<FunJet> &jets) {
    vector<vector<double>> res;
    for (auto el: jets) res.emplace_back(el.getDiffs());
    return res;
}

FunJet funJetWrapper(double x, unsigned& id, const unsigned N) { return {x, id, N}; }

template<typename F, typename... Args>
auto diffAtPoint(F f, Args... args) {
    return f(args...);
}

//template<typename F, typename... Args>
//vector<vector<double>> D(F f, Args... args) {
//    vector<vector<double>> res;
//    return ();
//}

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
//    auto jets = vector{FunJet(x, noOfVars), FunJet(y, noOfVars), FunJet(z, noOfVars)};
//    FunJet::setVarOrder(jets,noOfVars);
//    auto differential = totalDifferential(fun();
    auto differential = totalDifferential(fun(FunJet(x, 0, noOfVars), FunJet(y, 1, noOfVars), FunJet(z, 2, noOfVars)));
    for (auto &row: differential) {
        for (auto &el: row) {
            cout << el << " ";
        }
        cout << "\n";
    }

//    auto res = diffAtPoint(fun<double>, 1, 2, 3);
//    for (auto el: res) cout << el << " ";
}

#endif