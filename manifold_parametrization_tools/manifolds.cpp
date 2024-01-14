#ifndef MANIFOLtotalDifferentialS
#define MANIFOLtotalDifferentialS

#include "iostream"
#include "vector"
#include "Eigen/Eigen"
#include "autodiff/FAD.h"

using namespace Eigen;
using std::cout, std::cin, std::endl, std::vector;

/// @name totalDifferential
/// @brief computes differential from vector of jets, outputs MatrixXd
MatrixXd totalDifferential(const vector<FunJet> &jets) {
    vector<double> diffVec;
    for (const auto& el: jets) for (auto diff: el.getDiffs()) diffVec.emplace_back(diff);
    return MatrixXd::Map(&diffVec[0], jets.size(), jets[0].getDiffSize()).transpose();
}

/// @name funJetWrapper
/// @brief Calls FunJest constructor with decrement of varFlag
FunJet funJetWrapper(unsigned &varFlag, const unsigned &noOfVars, const double &x) { return {x, varFlag--, noOfVars}; }

/// @brief computes eigenvalues and eigenvectors of a matrix
/// @name computeEigens
/// @result pair = {eigenvalues, eigenvectors}
auto computeEigens(const MatrixXd &matrix) {
    return std::pair<VectorXd, Matrix<std::complex<double>, -1, -1, 0, -1, -1>>{
            matrix.selfadjointView<Lower>().eigenvalues(),
            EigenSolver<MatrixXd>(matrix).eigenvectors()};
}

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

template<typename T>
vector<T> fun2(T x, T y, T z) {
    return {2 * x + 3 * y + 4 * z, 5 * x + 6 * y + 7 * z, 8 * x + 9 * y + 10 * z};
}

int main() {
    double x = 0;
    double y = 0;
    double z = 0;
    unsigned noOfVars = 3;
    auto differential =
            totalDifferential(
                    fun(FunJet(x, 0, noOfVars),
                        FunJet(y, 1, noOfVars),
                        FunJet(z, 2, noOfVars))
            );
    cout << "p = (" << x << "," << y << "," << z << ")\nDf(p):\n" << differential << "\n";
    auto eigens = computeEigens(differential);
    auto &eigenvals = eigens.first;
    auto &eigenvecs = eigens.second;
    cout << "Eigenvalues:\n" << eigenvals << "\nEigenvectors:\n" << eigenvecs << "\n";
}

#endif