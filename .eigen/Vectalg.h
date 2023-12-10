//
// Created by kapela on 08.04.2020.
//

#ifndef GAUSS_VECTALG_H
#define GAUSS_VECTALG_H

// Jeżeli odkomentujemy poniższą linię to indeksy (asercje) nie będą sprawdzane
// #define  NDEBUG

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

/**
 * Wektor wymiaru n.
 * Domyślnie nie jest wypełniany zerami.
 */
template<typename T>
class Vector {
private:
    size_t n;
    std::unique_ptr<T[]> data = nullptr;
public:

    explicit Vector(size_t n = 0) : n(n) {
        data.reset(new T[n]);
    }

    Vector(const Vector &m) : n(m.n), data(new T[m.n]) {
        std::copy(m.data.get(), m.data.get() + n, data.get());
    }

    Vector(Vector &&m) noexcept: n(m.n), data(std::move(m.data)) {
        m.n = 0;
    }

    Vector(const std::initializer_list<T> &list) : n(list.size()) {
        data.reset(new T[n]);
        std::copy(list.begin(), list.end(), data.get());
    }

    Vector &operator=(const Vector &m) {
        if (this != &m) {
            if (n != m.n) {
                data.reset(new T[m.n]);
                n = m.n;
            }
            std::copy(m.data.get(), m.data.get() + n, data.get());
        }
        return *this;
    }

    Vector &operator=(Vector &&m) noexcept {
        data = std::move(m.data);
        n = m.n;
        return *this;
    }

    size_t size() const {
        return n;
    }

    T operator[](size_t index) const {
        assert(index < n);
        return data[index];
    }

    T &operator[](size_t index) {
        assert(index < n);
        return data[index];
    }

    double max_norm() const {
        double norm = 0;
        for (double x: *this) {
            norm = std::max(norm, std::abs(x));
        }
        return norm;
    }

    typedef T *iterator;

    iterator begin() {
        return data.get();
    }

    iterator end() {
        return data.get() + n;
    }

    typedef const T *const_iterator;

    const_iterator begin() const {
        return data.get();
    }

    const_iterator end() const {
        return data.get() + n;
    }
};

template<typename T>
inline std::ostream &operator<<(std::ostream &out, const Vector<T> &m) {
    for (auto x: m) {
        out << x << " ";
    }
    return out;
}

template<typename T>
inline std::istream &operator>>(std::istream &in, Vector<T> &m) {
    for (auto &x: m) {
        in >> x;
    }
    return in;
}

/**
 * Macierz n x n.
 * Domyślnie nie jest wypełniana zerami.
 */

template<typename T>
class Matrix {
private:
    size_t n;
    std::unique_ptr<T[]> data = nullptr;
public:
    explicit Matrix(size_t n = 0) : n(n) {
        data.reset(new T[n * n]);
    }

    Matrix(const Matrix &m) : n(m.n), data(new T[m.n * m.n]) {
        std::copy(m.data.get(), m.data.get() + n * n, data.get());
    }

    Matrix(Matrix &&m) noexcept: n(m.n), data(std::move(m.data)) {
        m.n = 0;
    }

    Matrix(std::initializer_list<std::initializer_list<T> > list) {
        n = list.size();
        data.reset(new T[n * n]);
        auto it = data.get();
        for (const auto &row: list) {
            it = std::copy(row.begin(), row.end(), it);
        }
    }

    Matrix &operator=(const Matrix &m) {
        if (this != &m) {
            if (n != m.n) {
                data.reset(new T[m.n * m.n]);
                n = m.n;
            }
            std::copy(m.data.get(), m.data.get() + n * n, data.get());
        }
        return *this;
    }

    Matrix &operator=(Matrix &&m) noexcept {
        data = std::move(m.data);
        n = m.n;
        return *this;
    }

    size_t size() const {
        return n;
    }

    T operator()(size_t row, size_t col) const {
        assert(row < n && col < n);
        return data[row * n + col];
    }

    T &operator()(size_t row, size_t col) {
        assert(row < n && col < n);
        return data[row * n + col];
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix &m) {
        for (int row = 0; row < m.n; ++row) {
            for (int col = 0; col < m.n; ++col) {
                out << m(row, col) << " ";
            }
            out << std::endl;
        }
        return out;
    }

    friend std::istream &operator>>(std::istream &in, Matrix &m) {
        for (auto &x: m) {
            in >> x;
        }
        return in;
    }

    typedef T *iterator;

    iterator begin() {
        return data.get();
    }

    iterator end() {
        return data.get() + n * n;
    }

    typedef const T *const_iterator;

    const_iterator begin() const {
        return data.get();
    }

    const_iterator end() const {
        return data.get() + n;
    }
};

template<typename T>
inline Vector<T> residual_vector(const Matrix<T> &a, const Vector<T> &b, const Vector<T> x) {
    assert(a.size() == b.size());
    assert(a.size() == x.size());
    int n = b.size();
    Vector<T> result(n);
    for (int i = 0; i < n; ++i) {
        long double s = 0;
        for (int j = 0; j < n; ++j) {
            s += static_cast<long double>(a(i, j)) * x[j];
        }
        long double bb = b[i];
        result[i] = static_cast<double>(bb - s);
    }
    return result;
}

/// Scaled Gauss linear equations solve by matrix inversion
template<typename T>
inline void swapRows(Matrix<T> &A, Vector<T> &b, const int &i, const int &j, const int &N) {
    if (i >= N or j >= N) return;
    for (int k = 0; k < N; ++k) std::swap(A(i, k), A(j, k));
    std::swap(b[i], b[j]);
}

template<typename T>
Vector<T> solveEquations(const Matrix<T> &A, const Vector<T> &b, double eps = 10e-10) { // solve A x == b
    const int N = A.size();
    if (N > 3000) return b;
    Matrix A1 = A;
    Vector x = b;

    Vector<T> rowNorms(N);
    Vector<T> row(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) row[j] = A1(i, j);
        rowNorms[i] = row.max_norm();
    }

    /* get main element */
    int mainId;
    for (int k = 0; k < N; ++k) {
        const int N1 = A1.size();
        double scaledVal = std::abs(A1(k, k)) / rowNorms[k];
        double maxVal = scaledVal;
        mainId = k;
        for (int i = k + 1; i < N1; ++i) {
            scaledVal = std::abs(A1(i, k)) / rowNorms[i];
            if (scaledVal > maxVal) {
                maxVal = scaledVal;
                mainId = i;
            }
        }
        swapRows(A1, x, k, mainId, N1);

        double scalingFactor;
        for (int i = k + 1; i < N1; ++i) {
            scalingFactor = A1(i, k) / A1(k, k);
            for (int j = 0; j < N1; ++j) A1(i, j) -= (scalingFactor * A1(k, j));
            x[i] -= (scalingFactor * x[k]);
        }
    }
    double temp;
    for (int i = N - 1; i >= 0; --i) {
        temp = 0;
        for (int j = N - 1; j > i; --j) temp += (A1(i, j) * x[j]);
        x[i] = ((x[i] - temp) / A1(i, i));
    }
    while (true) {
        Vector r = residual_vector(A, b, x);
        if (r.max_norm() < eps) return x;
        Vector error = solveEquations(A, r, eps);
        for (int i = 0; i < N; ++i) x[i] += error[i];
    }
}

#endif //GAUSS_VECTALG_H
