#ifndef _HENON_H_
#define _HENON_H_

#include "Mapping.h"
#include "../covering_relations_analysis/TSet.h"

template<typename T>
class Henon : public Mapping<T> {
    T coeff_a;
    T coeff_b;

    [[nodiscard]] T map_1(const T &x, const T &y) const override;

    [[nodiscard]] T map_2(const T &x, const T &y) const override;

public:

    Henon(const T &coeff_a, const T &coeff_b, int composition_constant);

};

template<class T>
Henon<T>::Henon(const T &coeff_a, const T &coeff_b, int composition_constant)  : Mapping<T>(composition_constant),
                                                                                 coeff_a(coeff_a), coeff_b(coeff_b) {}

template<class T>
T Henon<T>::map_1(const T &x, const T &y) const {
    return ((Interval(1) + y) - (coeff_a * (x * x)));
}

template<class T>
T Henon<T>::map_2(const T &x, const T &y) const {
    return (coeff_b * x);
}


#endif
