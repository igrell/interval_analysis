#ifndef MANIFOLtotalDifferentialS
#define MANIFOLtotalDifferentialS
#define __STDCPP_WANT_MATH_SPEC_FUNCS__ 1

#include "iostream"
#include "vector"
#include "Eigen/Eigen"
#include "autodiff/FAD.h"
#include "numeric"
#include <cmath>

using namespace Eigen;
using std::cout, std::cin, std::endl, std::vector;

///// @name totalDifferential
///// @brief computes differential from vector of jets, outputs MatrixXd
//MatrixXd totalDifferential(const vector<FunJet> &jets) {
//    vector<double> diffVec;
//    for (const auto& el: jets) for (auto diff: el.getDiffs()) diffVec.emplace_back(diff);
//    return MatrixXd::Map(&diffVec[0], jets.size(), jets[0].getDiffSize()).transpose();
//}
//
///// @name funJetWrapper
///// @brief Calls FunJest constructor with decrement of varFlag
//FunJet funJetWrapper(unsigned &varFlag, const unsigned &noOfVars, const double &x) { return {x, varFlag--, noOfVars}; }
//
///// @brief computes eigenvalues and eigenvectors of a matrix
///// @name computeEigens
///// @result pair = {eigenvalues, eigenvectors}
//auto computeEigens(const MatrixXd &matrix) {
//    return std::pair<VectorXd, Matrix<std::complex<double>, -1, -1, 0, -1, -1>>{
//            matrix.selfadjointView<Lower>().eigenvalues(),
//            EigenSolver<MatrixXd>(matrix).eigenvectors()};
//}
//
//// f(x,y) = ( (0 + x + y + x2 - 5xy - 2y2)/(1 + x - 4y), (1 + 2x - y + x2 - 4xy + 8y2)/(1 - 2x + 8y) )
//template<typename T>
//vector<T> fun(T x, T y, T z) {
//    return {(2 * x) + (x * x) + (y * z), (3 * y) + (x * y) - (z * z), (5 * z) + (y * y) + (2 * x * z)};
//}
//
//template<typename T>
//vector<T> fun2(T x, T y, T z) {
//    return {2 * x + 3 * y + 4 * z, 5 * x + 6 * y + 7 * z, 8 * x + 9 * y + 10 * z};
//}

//int main() {
//    double x = 0;
//    double y = 0;
//    double z = 0;
//    unsigned noOfVars = 3;
//    auto differential =
//            totalDifferential(
//                    fun(FunJet(x, 0, noOfVars),
//                        FunJet(y, 1, noOfVars),
//                        FunJet(z, 2, noOfVars))
//            );
//    cout << "p = (" << x << "," << y << "," << z << ")\nDf(p):\n" << differential << "\n";
//    auto eigens = computeEigens(differential);
//    auto &eigenvals = eigens.first;
//    auto &eigenvecs = eigens.second;
//    cout << "Eigenvalues:\n" << eigenvals << "\nEigenvectors:\n" << eigenvecs << "\n";
//}

size_t binom(unsigned n, unsigned k) {
         (k > n)? 0 :          // out of range
      (k==0 || k==n  )? 1 :          // edge
      (k==1 || k==n-1)? n :          // first
      (k + k < n)?              // recursive:
      (binom(n-1,k-1) * n)/k :       //  path to k=1   is faster
      (binom(n-1,k) * n)/(n-k);      //  path to k=n-1 is faster
}

unsigned int index(vector<unsigned> multiIndex) {
    auto indexLen = multiIndex.size();
    if (indexLen == 0) return 0;
    auto indexSum = std::accumulate(multiIndex.begin(), multiIndex.end(), 0);
    vector<unsigned> multiIndexRes;
    for (int i = 1; i < indexLen ; ++i) multiIndexRes.emplace_back(multiIndex[i]);
    return binom(indexLen + indexSum - 1, indexLen) + index(multiIndexRes);
}

vector<vector<unsigned>> gen_multiid(size_t dim, size_t n) {
    vector<unsigned> resTmp(dim);
    std::fill(resTmp.begin(), resTmp.end(), 0);
    vector<vector<unsigned>> res{resTmp};

    auto increment_multiid = [&dim, &n](vector<unsigned> multiid){
        for (int i = 0 ; i < dim ; ++i) {
           multiid[i]++;
           if (multiid[i] == n + 1) { multiid[i] = 0; }
           else break;
        }
        return multiid;
    };

    while (true) {
        auto tmp = res.back();
        tmp = increment_multiid(tmp);
        if (tmp.size() == 1 && tmp == resTmp) break; // TODO ???
        res.emplace_back(tmp);
    }
    std::remove_if(res.begin(), res.end(), [&n](auto& el){ return std::accumulate(el.begin(), el.end(), 0) > n; });
    return res;
}

class Poly {
    vector<double> coeffs;
    size_t noVars;
    size_t maxDeg;

    Poly(const vector<double>& _coeffs, const size_t& _noVars) : coeffs(_coeffs), noVars(_noVars), maxDeg(0) {
        auto multiIndex = vector<unsigned>(noVars);
        std::fill(multiIndex.begin(), multiIndex.end(), 0);
        while (index(multiIndex) + 1 < coeffs.size()) {
            maxDeg++;
            multiIndex.back() += 1;
        }
    }

    void eval_poly(vector<double> arg) {
        assert(arg.size() == noVars);
        double res = 0.;
        // TODO
    }
};

int main() {
    gen_multiid(2, 3);
    return 0;
}


#endif