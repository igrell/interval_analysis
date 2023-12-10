#ifndef MANIFOLtotalDifferentialS
#define MANIFOLtotalDifferentialS

#include "iostream"
#include "vector"
#include "Eigen/Eigen"
#include "autodiff/Autodiff.h"

using namespace Eigen;
using std::cout, std::cin, std::endl, std::vector, std::tuple;


vector<vector<double>> totalDifferential(const vector<FunJet> &jets) {
    vector<vector<double>> res;
    for (auto el: jets) res.emplace_back(el.getDiffs());
    return res;
}

/// @name funJetWrapper
/// @brief Calls FunJest constructor with decrement of varFlag
FunJet funJetWrapper(unsigned &varFlag, const unsigned &noOfVars, const double &x) { return {x, varFlag--, noOfVars}; }

//template<typename F, typename... Args>
//auto applyFun(F f, Args... args) {
//    return f(args...);
//}

// TODO
//template<unsigned noOfVars, typename F, typename...Args>
//vector<vector<double>> differentialAtPoint(F f, Args...args) {
//    unsigned varFlag = noOfVars - 1;
//    vector<vector<double>> res;
//    res.emplace_back(funJetWrapper(noOfVars,varFlag,args)...);
//}

// f(x,y) = ( (0 + x + y + x2 - 5xy - 2y2)/(1 + x - 4y), (1 + 2x - y + x2 - 4xy + 8y2)/(1 - 2x + 8y) )
template<typename T>
vector<T> fun(T x, T y, T z) {
    return {(2 * x) + (x * x) + (y * z), (3 * y) + (x * y) - (z * z), (5 * z) + (y * y) + (2 * x * z)};
}
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
    unsigned varFlag =
            noOfVars - 1; // as for some reason funJets are initialized from the last one, this flag goes from 2 to 0
    auto differential = totalDifferential(fun(funJetWrapper(varFlag, noOfVars, x), funJetWrapper(varFlag, noOfVars, y),
                                              funJetWrapper(
                                                      varFlag, noOfVars, z)));
    for (auto &row: differential) {
        for (auto &el: row) {
            cout << el << " ";
        }
        cout << "\n";
    }
}

#endif