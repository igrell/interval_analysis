#ifndef TAYLORAD_H
#define TAYLORAD_H

#include "vector"
#include "TaylorPol.h"
#include "cassert"
#include "sstream"

using std::vector, std::ostream;

/// @class TaylorJet
/// @brief Implementing FAD of any order for function p : R -> R^n
template<class T>
class TaylorJet {
    vector<TaylorPol<T>> pols; // p^[i] (t)
//    vector<vector<T>> diffs; // p^(i) (t)

public:

    explicit TaylorJet(const size_t order) {
        pols = vector<TaylorPol<T>>(order);
    }

    explicit TaylorJet(const vector<TaylorPol<T>> _pols) : pols(_pols) {}

    [[nodiscard]] size_t getOrder() const;

    TaylorPol<T> polAt(const unsigned int k) const { return pols.at(k); }

    TaylorPol<T> &polAt(const unsigned int k) { return pols.at(k); };

//    vector<T> diffAt(const unsigned int k) const { return polAt(k) * fact(k); }

//    vector<T> &diffAt(const unsigned int k) { return polAt(k) * fact(k); }

    TaylorJet<T> operator+(TaylorJet<T> &) const;

    TaylorJet<T> operator-(TaylorJet<T> &) const;

    TaylorJet<T> operator*(TaylorJet<T> &) const;

};

// Helper factorial evaluator
unsigned fact(unsigned long long k) {
    if (k == 0) return 1;
    else return k * fact(k - 1);
}

template<class T>
TaylorJet<T> TaylorJet<T>::operator*(TaylorJet<T> &q) const {
    const TaylorJet<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    vector<TaylorPol<T>> newpols;
    for (unsigned i = 0; i <= p.getOrder(); ++i) {
        TaylorPol<T> tmpSum(p.polAt(0).getOrder());
        for (unsigned j = 0; j <= i; ++j)
            tmpSum = tmpSum +
                     p.polAt(j) * q.polAt(i - j);
        newpols.emplace_back(tmpSum);
    }
    return TaylorJet<T>(newpols);
}

template<class T>
TaylorJet<T> TaylorJet<T>::operator-(TaylorJet<T> &q) const {
    const TaylorJet<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    vector<TaylorPol<T>> newpols;
    for (unsigned i = 0; i <= p.getOrder(); ++i) newpols.emplace_back(p.polAt(i) - q.polAt(i));
    return TaylorJet<T>(newpols);
}

template<class T>
TaylorJet<T> TaylorJet<T>::operator+(TaylorJet<T> &q) const {
    const TaylorJet<T> &p = *this;
    assert(p.getOrder() == q.getOrder());
    vector<TaylorPol<T>> newpols;
    for (unsigned i = 0; i <= p.getOrder(); ++i) newpols.emplace_back(p.polAt(i) + q.polAt(i));
    return TaylorJet<T>(newpols);
}

template<class T>
size_t TaylorJet<T>::getOrder() const {
    return pols.size() - 1;
}

template<class T>
ostream &operator<<(ostream &ostream, const TaylorJet<T> &jet) {
    ostream << "k |  p[k]\n";
    for (unsigned i = 0; i <= jet.getOrder(); ++i) ostream << i << ": " << jet.polAt(i) << "\n";
    return ostream;
}

#endif //TAYLORAD_H
