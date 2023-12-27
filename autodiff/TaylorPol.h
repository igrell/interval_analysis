#ifndef INTERVAL_ANALYSIS_TAYLORPOL_H
#define INTERVAL_ANALYSIS_TAYLORPOL_H

#include "vector"
#include "sstream"
#include "cassert"

using std::vector, std::ostream;

template<class T>
class TaylorPol {
    vector<T> coeffs;
    size_t order;
public:
    explicit TaylorPol(const vector<T> &_coeffs) : coeffs(_coeffs), order(_coeffs.size()) {}

    explicit TaylorPol(const size_t _order) : coeffs(vector<T>(_order)), order(_order) {}

    vector<T>& getCoeffs() const { return coeffs; }

    size_t getOrder() const { return order; }

    T &operator[](const unsigned id) {
        assert(id > -1 and id <= order);
        return coeffs[id];
    }

    TaylorPol<T> operator+(const TaylorPol<T> &q) {
        const TaylorPol<T> &p = *this;
        assert(p.getOrder() == q.getOrder());
        TaylorPol<T> r = p;
        for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] += q[i];
        return r;
    }

    TaylorPol<T> operator-(const TaylorPol<T> &q) {
        const TaylorPol<T> &p = *this;
        assert(p.getOrder() == q.getOrder());
        TaylorPol<T> r = p;
        for (unsigned i = 0; i <= p.getOrder(); ++i) r[i] -= q[i];
        return r;
    }

    TaylorPol<T> operator*(const TaylorPol<T> &q) {
        const TaylorPol<T> &p = *this;
    }
};


template<class T>
ostream &operator<<(ostream &ostream, const TaylorPol<T> &p) {
    ostream << "[";
    for (const auto &coeff: p.getCoeffs()) ostream << coeff << " ";
    ostream << "]\n";
    return ostream;
}

#endif //INTERVAL_ANALYSIS_TAYLORPOL_H
