#ifndef INTERVAL_ANALYSIS_EIGENSOLVER2D_H
#define INTERVAL_ANALYSIS_EIGENSOLVER2D_H

#include "complex"
#include "iostream"
#include "Vectalg.h"

using std::pair, std::complex;

template<typename T>
class EigenSolver2D {
    T a = 0;
    T b = 0;
    T c = 0;
    T d = 0;
    pair<complex<T>, complex<T>> eigenvalues = {0, 0};
    pair<pair<T, T>, pair<T,T>> eigenvectors = {{0, 0}, // assume real values for now
                                                {0, 0}};

    T delta();

public:
    explicit EigenSolver2D(Matrix<T> _matrix) : a(_matrix(0, 0)), b(_matrix(0, 1)), c(_matrix(1, 0)),
                                                d(_matrix(1, 1)) {}

//    EigenSolver2D(const T &_a, const T &_b, const T &_c, const T &_d) : a(_a), b(_b), c(_c), d(_d) {}

//    pair<pair<T,T>,pair<T,T>> eigenvectors() {}

    void evalEigenvalues();

    void evalEigenvectors();

    void displayEigenvalues();

    void displayEigenvectors();
//    friend std::ostream &operator<<(std::ostream &ostream, const complex<T> &z) {
//        if (z.imag() == 0) ostream << z.real();
//        else ostream << z.real() << "+i" << z.imag();
//        return ostream;
//    }
};



#endif //INTERVAL_ANALYSIS_EIGENSOLVER2D_H
