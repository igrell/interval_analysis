#ifndef INTERVAL_ANALYSIS_AUTODIFF_H
#define INTERVAL_ANALYSIS_AUTODIFF_H

#include "iostream"
#include "Interval.h"
#include "cmath"

using std::pair;

template<typename T>
class FunJet {
    T fx;
    T dx;

public:
    FunJet();

    FunJet(bool varFlag, T fx);

    FunJet(T fx, T dx);

    FunJet(const FunJet &jet);

    inline FunJet &operator=(const FunJet &jet);

    T get_fx() const;

    T get_dx() const;

    inline friend std::ostream &operator<<(std::ostream &ostream, const FunJet &funJet) {
        ostream << (funJet.fx == T(-0) ? T(0) : funJet.fx) << " " << (funJet.dx == T(-0) ? T(0) : funJet.dx);
        return ostream;
    }

};

template<typename T>
inline FunJet<T> operator+(const FunJet<T> &u, const FunJet<T> &v);

template<typename T>
inline FunJet<T> operator+(T c, const FunJet<T> &u);

template<typename T>
inline FunJet<T> operator+(const FunJet<T> &u, T c);

template<typename T>
inline FunJet<T> operator-(const FunJet<T> &u, const FunJet<T> &v);

template<typename T>
inline FunJet<T> operator-(T c, const FunJet<T> &u);

template<typename T>
inline FunJet<T> operator-(const FunJet<T> &u, T c);

template<typename T>
inline FunJet<T> operator-(const FunJet<T> &u);

template<typename T>
inline FunJet<T> operator*(const FunJet<T> &u, const FunJet<T> &v);

template<typename T>
inline FunJet<T> operator*(T c, const FunJet<T> &u);

template<typename T>
inline FunJet<T> operator*(const FunJet<T> &u, T c);

template<typename T>
inline FunJet<T> operator/(const FunJet<T> &u, const FunJet<T> &v);

template<typename T>
inline FunJet<T> operator/(const FunJet<T> &u, T c);

template<typename T>
inline FunJet<T> operator/(T c, const FunJet<T> &u);

template<typename T>
inline FunJet<T> sin(const FunJet<T> &u);

template<typename T>
inline FunJet<T> cos(const FunJet<T> &u);

template<typename T>
inline FunJet<T> exp(const FunJet<T> &u);

template<typename T>
pair<T, T> autodiff(FunJet<T> (*f)(const FunJet<T> &), T x);

#endif //INTERVAL_ANALYSIS_AUTODIFF_H
