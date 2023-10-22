#ifndef INTERVAL_ANALYSIS_EIGENSOLVER_H
#define INTERVAL_ANALYSIS_EIGENSOLVER_H

#include "Matrix.h"
#include "vector"

using std::vector, std::pair;

template<typename T, size_t N>
class EigenSolver {
    Matrix<T, N, N> matrix;

    vector<T> eigenvalues() {}

    vector<pair<T,T>> eigenvectors() {}

};


#endif //INTERVAL_ANALYSIS_EIGENSOLVER_H
