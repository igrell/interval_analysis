#ifndef TAYLORPOL_H
#define TAYLORPOL_H

#include <gmpxx.h>
#include "vector"
#include "sstream"
#include "cassert"

using std::vector, std::ostream;

template<class T>
class TaylorPol {
    vector<T> coeffs;
public:
    explicit TaylorPol(const vector<T> &_coeffs) : coeffs(_coeffs) {}

    explicit TaylorPol(const size_t _order) : coeffs(vector<T>(_order + 1)) {}

    vector<T> getCoeffs() const { return coeffs; }

    [[nodiscard]] size_t getOrder() const { return coeffs.size() - 1; }

    T &operator[](unsigned id);

    TaylorPol<T> operator+(const TaylorPol<T> &q) const;

    TaylorPol<T> operator-(const TaylorPol<T> &q) const;

    TaylorPol<T> operator*(const TaylorPol<T> &q) const;
};

/* Operators */

template<class T>
T &TaylorPol<T>::operator[](const unsigned int id) {
    assert(id <= getOrder());
    return coeffs[id];
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator+(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] += q.getCoeffs()[i];
    return r;
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator-(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] -= q.getCoeffs()[i];
    return r;
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator*(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r(p.getOrder());
    T tmpSum = 0;
    for (unsigned i = 0; i <= p.getOrder(); ++i)
        for (unsigned j = 0; j <= i; ++j) r[i] += p.getCoeffs()[j] * q.getCoeffs()[i - j];
    return r;
}

template<class T>
ostream &operator<<(ostream &ostream, const TaylorPol<T> &p) {
    ostream << "[";
    for (unsigned i = 0; i < p.getOrder(); ++i) ostream << p.getCoeffs()[i] << " ";
    ostream << p.getCoeffs()[p.getOrder()] << "]";
    return ostream;
}


#endif // TAYLORPOL_H
