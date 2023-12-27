#ifndef INTERVAL_ANALYSIS_TAYLORPOL_H
#define INTERVAL_ANALYSIS_TAYLORPOL_H

#include <gmpxx.h>
#include "vector"
#include "sstream"
#include "cassert"

using std::vector, std::ostream;

template<class T>
class TaylorPol {
    vector<T> coeffs;
    size_t order;
public:
    explicit TaylorPol(const vector<T> &_coeffs) : coeffs(_coeffs), order(_coeffs.size() - 1) {}

    explicit TaylorPol(const size_t _order) : coeffs(vector<T>(_order + 1)), order(_order) {}

    vector<T> getCoeffs() const { return coeffs; }

    [[nodiscard]] size_t getOrder() const { return order; }

    vector<T> getDiffs();

    T &operator[](const unsigned id) {
        assert(id <= order);
        return coeffs[id];
    }

    TaylorPol<T> operator+(const TaylorPol<T> &q);

    TaylorPol<T> operator-(const TaylorPol<T> &q) {
        const TaylorPol<T> &p = *this;
        assert(p.getOrder() == q.getOrder());
        TaylorPol<T> r = p;
        for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] -= q.getCoeffs()[i];
        return r;
    }

    TaylorPol<T> operator*(const TaylorPol<T> &q) {
        const TaylorPol<T> &p = *this;
        assert(p.getOrder() == q.getOrder());
        TaylorPol<T> r(p.getOrder());
        T tmpSum = 0;
        for (unsigned i = 0 ; i <= p.getOrder() ; ++i)
            for (unsigned j = 0 ; j <= i ; ++j) r[i] += p.getCoeffs()[j] * q.getCoeffs()[i-j];
        return r;
    }
};

template<class T>
vector<T> TaylorPol<T>::getDiffs() {
    vector<T> _coeffs = getCoeffs();
    std::transform(_coeffs.begin(),_coeffs.end(),_coeffs.begin(),[](T x){ return factorial(x); }); // TODO
    return vector<T>();
}

template<class T>
TaylorPol<T> TaylorPol<T>::operator+(const TaylorPol<T> &q) {
    const TaylorPol<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    TaylorPol<T> r = p;
    for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] += q.getCoeffs()[i];
    return r;
}

template<class T>
ostream &operator<<(ostream &ostream, const TaylorPol<T> &p) {
    ostream << "[";
    for (unsigned i = 0; i < p.getOrder() ; ++i) ostream << p.getCoeffs()[i] << " ";
    ostream << p.getCoeffs()[p.getOrder()] << "]\n";
    return ostream;
}

#endif //INTERVAL_ANALYSIS_TAYLORPOL_H
