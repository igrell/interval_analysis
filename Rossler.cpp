#include "Rossler.h"

IPoint Rossler::operator()(IPoint &iPoint) const {
//    IPoint res = {Interval((iPoint.area.first.get_lo() + iPoint.area.first.get_hi()) / 2),Interval((iPoint.area.second.get_lo() + iPoint.area.second.get_hi()) / 2) };
    return r_thrice(iPoint);
}

template<class T>
T Rossler::r1(T &x, T &y) const { //Rossler R1
    return ((coeff_1 * x) * (1 - x) - (coeff_2 * y));
}

template<class T>
T Rossler::r2(T &x, T &y) const { //Rossler R2
    return (coeff_3 * (y - coeff_4) * (1 - (coeff_5 * x)));
}

template<class T>
pair<T, T> Rossler::r(T &x, T &y) const { //Rossler map
    return pair<T, T>(r1(x, y), r2(x, y));
}

template<class T>
pair<T, T> Rossler::r_thrice(T &x, T &y) const { //triple composition of Rossler map
    pair<T, T> r_once = r(x, y);
    pair<T, T> r_twice = r(r_once.first, r_once.second);
    return r(r_twice.first, r_twice.second);
}

IPoint
Rossler::r_thrice(IPoint &iPoint) const {
    auto res = r_thrice(iPoint.area.first, iPoint.area.second);
    return {res.first, res.second};
}

Rossler::Rossler(const Interval &coeff_1, const Interval &coeff_2, const Interval &coeff_3, const Interval &coeff_4,
                 const Interval &coeff_5) : coeff_1(coeff_1), coeff_2(coeff_2), coeff_3(coeff_3), coeff_4(coeff_4),
                                            coeff_5(coeff_5) {
}