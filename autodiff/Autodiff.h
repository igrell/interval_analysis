// Igor Piechowiak
#include <iostream>
#include <iomanip>
#include <utility>
#include "vector"
#include "cassert"
#include "cmath"

using std::vector;

class FunJet {
    double fx;
//    double dx, dy;
    vector<double> diffs;

public:

    FunJet() : fx(0), diffs({}) {}

    explicit FunJet(const unsigned noOfVars) : fx(0) { std::fill_n(std::back_inserter(diffs), noOfVars, 0); }

    // varFlag indicates which element from diffs is a variable
//    FunJet(const double _fx, const unsigned noOfVars) : FunJet(noOfVars) { fx = _fx; }
    FunJet(const double _fx, const unsigned varFlag, const unsigned noOfVars) : FunJet(noOfVars) {
        fx = _fx;
        diffs[varFlag] = 1;
    }

    FunJet(const double _fx, vector<double> _diffs) : fx(_fx), diffs(std::move(_diffs)) {}

    FunJet(const FunJet &jet) = default;

    inline FunJet &operator=(const FunJet &jet) = default;

    inline friend std::ostream &operator<<(std::ostream &ostream, const FunJet &funJet) {
        ostream << (funJet.fx == -0 ? 0 : funJet.fx);
        for (const auto &diff: funJet.diffs) { ostream << " " << (diff == -0 ? 0 : diff); }
        return ostream;
    }

    inline friend FunJet operator+(const FunJet &u, const FunJet &v) {
        assert(u.diffs.size() == v.diffs.size());
        FunJet res = u;
        res.fx += v.fx;
        for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] += v.diffs[i];
        return res;
    }

    inline friend FunJet operator+(const double c, const FunJet &u) { // check later
        FunJet res(u.diffs.size());
        res.fx = c;
        return res + u;
    }

    inline friend FunJet operator+(const FunJet &u, const double c) { return c + u; }

    inline friend FunJet operator-(const FunJet &u, const FunJet &v) {
        assert(u.diffs.size() == v.diffs.size());
        FunJet res = u;
        res.fx -= v.fx;
        for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] -= v.diffs[i];
        return res;
    }

    inline friend FunJet operator-(const double c, const FunJet &u) {
        FunJet res(u.diffs.size());
        res.fx = c;
        return (res - u);
    }

    inline friend FunJet operator-(const FunJet &u, const double c) { return (-c + u); }

    inline friend FunJet operator-(const FunJet &u) { return (-1 * u); }

    inline friend FunJet operator*(const FunJet &u, const FunJet &v) {
        assert(u.diffs.size() == v.diffs.size());
        FunJet res(u.diffs.size());
        res.fx = u.fx * v.fx;
        for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] = (u.fx * v.diffs[i]) + (u.diffs[i] * v.fx);
        return res;
    }

    inline friend FunJet operator*(const double c, const FunJet &u) { // TODO DOBRZE?
        FunJet res(u.diffs.size());
        res.fx = c;
        return res * u;
    }

    inline friend FunJet operator*(const FunJet &u, const double c) { return c * u; }

    inline friend FunJet operator/(const FunJet &u, const FunJet &v) {
        assert(u.diffs.size() == v.diffs.size());
        FunJet res(u.diffs.size());
        res.fx = u.fx / v.fx;
        for (unsigned i = 0; i < u.diffs.size(); ++i) res.diffs[i] = (u.diffs[i] - (res.fx * v.diffs[i])) / v.fx;
        return res;
    }

    inline friend FunJet operator/(const FunJet &u, const double c) {
        FunJet res(u.diffs.size());
        res.fx = c;
        return u / res;
    }

    inline friend FunJet operator/(const double c, const FunJet &u) {
        FunJet res(u.diffs.size());
        res.fx = c;
        return res / u;
    }

    vector<double> getDiffs() {
        return diffs;
    }

    static void setVarOrder(vector<FunJet> &jets, unsigned noOfVars) {
        for (unsigned i = 0; i < noOfVars; ++i) jets[i].diffs[i] = 0;
    }

//    inline friend FunJet sin(const FunJet &u) {
//        double sin_u = std::sin(u.fx);
//        double cos_u = std::cos(u.fx);
//        return FunJet(sin_u,
//                      u.dx * cos_u,
//                      u.dy * cos_u);
//    }
//
//    inline friend FunJet cos(const FunJet &u) {
//        double sin_u = std::sin(u.fx);
//        double cos_u = std::cos(u.fx);
//        return FunJet(cos_u,
//                      -u.dx * sin_u,
//                      -u.dy * sin_u);
//    }
//
//    inline friend FunJet exp(const FunJet &u) {
//        double exp_u = std::exp(u.fx);
//        return FunJet(exp_u,
//                      u.dx * exp_u,
//                      u.dy * exp_u);
//    }
};
