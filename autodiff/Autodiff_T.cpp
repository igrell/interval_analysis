#ifndef AUTODIFF_
#define AUTODIFF_

#include "Interval.h"
#include "cmath"
#include "Autodiff_T.h"

using std::sin, std::cos, std::exp, std::pair;

template<typename T>
FunJet<T>::FunJet(const FunJet &jet) : fx(jet.fx), dx(jet.dx) {}

template<typename T>
FunJet<T>::FunJet(T fx, T dx) : fx(fx), dx(dx) {
}

template<typename T>
FunJet<T>::FunJet(const bool varFlag, T fx) : fx(fx) { dx = varFlag ? T(1) : T(0); }

template<typename T>
FunJet<T>::FunJet() : fx(0), dx(0) {}

template<typename T>
FunJet<T> cos(const FunJet<T> &u) { return FunJet(cos(u.fx), -u.dx * sin(u.fx)); }

template<typename T>
FunJet<T> exp(const FunJet<T> &u) {
    T exp_u = exp(u.fx);
    return FunJet(exp_u, u.dx * exp_u);
}

template<typename T>
FunJet<T> sin(const FunJet<T> &u) { return FunJet(sin(u.fx), u.dx * cos(u.fx)); }


template<typename T>
FunJet<T> &FunJet<T>::operator=(const FunJet<T> &jet) {
    fx = jet.fx;
    dx = jet.dx;
    return *this;
}

template<typename T>
FunJet<T> operator+(const FunJet<T> &u, const FunJet<T> &v) {
    return FunJet(u.fx + v.fx, u.dx + v.dx);
}

template<typename T>
FunJet<T> operator+(const T c, const FunJet<T> &u) { return u + FunJet(c, 0); }

template<typename T>
FunJet<T> operator+(const FunJet<T> &u, const T c) { return c + u; }

template<typename T>
FunJet<T> operator-(const FunJet<T> &u, const FunJet<T> &v) {
    return FunJet(u.fx - v.fx, u.dx - v.dx);
}

template<typename T>
FunJet<T> operator-(const T c, const FunJet<T> &u) { return FunJet(c, 0) - u; }

template<typename T>
FunJet<T> operator-(const FunJet<T> &u, const T c) { return (-c + u); }

template<typename T>
FunJet<T> operator-(const FunJet<T> &u) { return (-1 * u); }

template<typename T>
FunJet<T> operator*(const FunJet<T> &u, const FunJet<T> &v) {
    return FunJet<T>((u.get_fx() * v.get_fx()), (u.get_fx() * v.get_dx()) + (u.get_dx() * v.get_fx()));
}

template<typename T>
FunJet<T> operator*(const T c, const FunJet<T> &u) { return u * FunJet(c, 0); }

template<typename T>
FunJet<T> operator*(const FunJet<T> &u, const T c) { return c * u; }

template<typename T>
FunJet<T> operator/(const FunJet<T> &u, const T c) { return u / FunJet(c, 0); }

template<typename T>
FunJet<T> operator/(const T c, const FunJet<T> &u) { return FunJet(c, 0) / u; }

template<typename T>
FunJet<T> operator/(const FunJet<T> &u, const FunJet<T> &v) {
    T u_by_v = u.fx / v.fx;
    return FunJet(u_by_v, (u.dx - (u_by_v * v.dx)) / v.fx);
}

template<typename T>
T FunJet<T>::get_dx() const { return dx; }

template<typename T>
T FunJet<T>::get_fx() const { return fx; }

template<typename T>
FunJet<T> autodiff(T (*f)(T), T x) { return f(FunJet<T>(true, x)); }

template<typename T>
T fun(T x) { return x * x; }

int main() {
    double x = 3;
    auto res2 = autodiff(fun, x);
    return 0;
}


#endif

