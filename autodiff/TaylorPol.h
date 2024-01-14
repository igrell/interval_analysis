#ifndef TAYLORPOL_H
#define TAYLORPOL_H

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

    [[nodiscard]] size_t getOrder() const { return coeffs.size() - 1; }

    T &operator[](unsigned);

    T operator[](unsigned) const;

    TaylorPol<T> operator+(const TaylorPol<T> &) const;

    TaylorPol<T> operator-(const TaylorPol<T> &) const;

    TaylorPol<T> operator*(const TaylorPol<T> &) const;
};

/* Operators */

template<class T>
T &TaylorPol<T>::operator[](const unsigned int id) {
    assert(id <= getOrder());
    return coeffs[id];
}

template<class T>
T TaylorPol<T>::operator[](unsigned int id) const {
    return coeffs[id];
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator+(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] += q[i];
    return r;
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator-(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] -= q[i];
    return r;
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator*(const TaylorPol<T> &q) const {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] *= q[i];
    return r;
}

template<class T>
ostream &operator<<(ostream &ostream, const TaylorPol<T> &p) {
    ostream << "[";
    for (unsigned i = 0; i < p.getOrder(); ++i) ostream << p[i] << " ";
    ostream << p[p.getOrder()] << "]";
    return ostream;
}


#endif // TAYLORPOL_H
