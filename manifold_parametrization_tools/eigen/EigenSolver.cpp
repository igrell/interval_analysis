#include "EigenSolver2D.h"
#include "cassert"

template<typename T>
T EigenSolver2D<T>::delta() {
    return (a * a) - (2 * a * d) + (d * d) + (4 * b * c);
}

template<typename T>
void EigenSolver2D<T>::evalEigenvalues() {
    complex<T> delta_sqrt = sqrt(complex<T>(delta()));
    eigenvalues.first = (complex<T>(a) + complex<T>(d) - delta_sqrt) / complex<T>(2);
    eigenvalues.second = (complex<T>(a) + complex<T>(d) + delta_sqrt) / complex<T>(2);
}

template<typename T>
void EigenSolver2D<T>::evalEigenvectors() {
    assert(eigenvalues.first != 0. and eigenvalues.second != 0.);
    assert(eigenvalues.first.imag() == 0); // assume real eigenvalues for now
    Vector<T> eigenvector1 = solveEquations(Matrix<T>{{a - eigenvalues.first.real(), b},
                                                      {c,                            d - eigenvalues.first.real()}},
                                            Vector<T>{0, 0});
    Vector<T> eigenvector2 = solveEquations(Matrix<T>{{a - eigenvalues.second.real(), b},
                                                      {c,                             d - eigenvalues.second.real()}},
                                            Vector<T>{0, 0});
    eigenvectors = {{eigenvector1[0], eigenvector1[1]},
                    {eigenvector2[0], eigenvector2[1]}};
}

template<typename T>
void EigenSolver2D<T>::displayEigenvalues() {
    if (eigenvalues.first.imag() != 0) {
        std::cout << eigenvalues.first.real() << "+" << eigenvalues.first.imag() << "i";
    } else { std::cout << eigenvalues.first.real(); }
    std::cout << " , ";
    if (eigenvalues.second.imag() != 0) {
        std::cout << eigenvalues.second.real() << "+" << eigenvalues.second.imag() << "i";
    } else { std::cout << eigenvalues.second.real(); }
    std::cout << "\n";
}

template<typename T>
void EigenSolver2D<T>::displayEigenvectors() {
    std::cout << "(" << eigenvectors.first.first << "," << eigenvectors.first.second << ") , ("
              << eigenvectors.second.first << "," << eigenvectors.second.second << ")\n";
}

int main() {
    Matrix<double> matrix{{1, 2},
                          {3, 4}};
    Vector<double> vector{1, 1};
    EigenSolver2D<double> solver(matrix);
    solver.evalEigenvalues();
    solver.evalEigenvectors();
    solver.displayEigenvalues();
    solver.displayEigenvectors();
    auto res = solveEquations(matrix, vector);
    std::cout << res;
    return 0;
}