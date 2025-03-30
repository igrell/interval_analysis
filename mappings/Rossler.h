#ifndef _ROSSLER_H_
#define _ROSSLER_H_

#include "Mapping.h"
#include "vector"
#include "cmath"

using std::pair, std::vector, std::abs;

template<typename T>
class Rossler : public Mapping<T> {
    T coeff_1;
    T coeff_2;
    T coeff_3;
    T coeff_4;
    T coeff_5;

    [[nodiscard]] T map_1(const T &x, const T &y) const override;

    [[nodiscard]] T map_2(const T &x, const T &y) const override;

public:

    Rossler(const T &coeff_1, const T &coeff_2, const T &coeff_3, const T &coeff_4,
            const T &coeff_5, size_t composition_constant);

};

template<typename T>
Rossler<T>::Rossler(const T &coeff_1, const T &coeff_2, const T &coeff_3, const T &coeff_4,
                    const T &coeff_5, size_t composition_constant) : Mapping<T>(composition_constant), coeff_1(coeff_1), coeff_2(coeff_2),
                                                                  coeff_3(coeff_3), coeff_4(coeff_4),
                                                                  coeff_5(coeff_5)  {}

template<typename T>
T Rossler<T>::map_1(const T &x, const T &y) const {
    return ((coeff_1 * x) * (1 - x) - (coeff_2 * y));
}

template<typename T>
T Rossler<T>::map_2(const T &x, const T &y) const {
    return (coeff_3 * (y - coeff_4) * (1 - (coeff_5 * x)));
}

#endif