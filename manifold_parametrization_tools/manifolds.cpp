#ifndef MANIFOLtotalDifferentialS
#define MANIFOLtotalDifferentialS

#include "iostream"
#include "vector"
#include "Eigen/Eigen"
#include "autodiff/Autodiff.h"
#include "string"

using namespace Eigen;
using std::cout, std::cin, std::endl, std::vector, std::tuple, std::string;


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

// Convert a 2-D vector<vector<double> > into an Eigen MatrixXd.
// Throws exception if rows do not have same length.
//MatrixXd convert_vvd_to_matrix(vector<vector<double>> vvd) {
//
//    std::size_t n_rows = vvd.size();
//    std::size_t n_cols = vvd.at(0).size();
//
//    MatrixXd result(n_rows, n_cols);
//    result.row(0) = VectorXd::Map(&vvd[0][0], n_cols);
//
//     Add each vector row to the MatrixXd.
//    for (std::size_t i = 1; i < n_rows; i++) {
//
//         Make sure that every row of vvd has the same size.
//        if (n_cols != vvd.at(i).size()) {
//            char buffer[200];
//            snprintf(buffer, 200,
//                     "vvd[%ld] size (%ld) does not match vvd[0] size (%ld)",
//                     i, vvd.at(i).size(), n_cols);
//            string err_mesg(buffer);
//            throw std::invalid_argument(err_mesg);
//        }
//
//        result.row(i) = VectorXd::Map(&vvd[i][0], n_cols);
//    }
//
//    return result;
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
    auto differential = convert_vvd_to_matrix( // convertion to Eigen format
            totalDifferential( // computes differential from vector of jets
                    fun(funJetWrapper(varFlag, noOfVars, x),
                        funJetWrapper(varFlag, noOfVars, y),
                        funJetWrapper(varFlag, noOfVars, z))
            )
    );
    cout << differential << "\n";
    EigenSolver<MatrixXd> eigenSolver(differential);
    cout << eigenSolver.eigenvalues().col(0);
    // TODO biggest eigenvalue etc
}

#endif