#include "TSet.h"
#include "Mapping.h"
#include "vector"
#include "cmath"

using std::pair, std::vector, std::abs;

class Rossler {
    Interval coeff_1;
    Interval coeff_2;
    Interval coeff_3;
    Interval coeff_4;
    Interval coeff_5;

    template<typename T>
    T r1(T &x, T &y) const;
//
//    template<typename T>
//    T map_1(T &x, T &y) {
//
//    }



    template<typename T>
    T r2(T &x, T &y) const;

    template<typename T>
    pair<T, T> r(T &x, T &y) const;

    template<class T>
    pair<T, T> r_thrice(T &x, T &y) const;

    IPoint r_thrice(IPoint &) const;

public:

    Rossler(const Interval &coeff_1, const Interval &coeff_2, const Interval &coeff_3, const Interval &coeff_4,
            const Interval &coeff_5);

    IPoint operator()(IPoint &iPoint) const;

};