#include "FAD.h"

FunJet::FunJet(const unsigned int noOfVars) : fx(0) { std::fill_n(std::back_inserter(diffs), noOfVars, 0); }

FunJet::FunJet(const double _fx, const unsigned int varFlag, const unsigned int noOfVars) : FunJet(noOfVars) {
    fx = _fx;
    diffs[varFlag] = 1;
}

FunJet::FunJet(const double _fx, vector<double> _diffs) : fx(_fx), diffs(std::move(_diffs)) {}

FunJet operator+(const FunJet &u, const FunJet &v) {
    assert(u.getDiffSize() == v.getDiffSize());
    FunJet res = u;
    res.fx += v.fx;
    for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] += v.diffs[i];
    return res;
}

FunJet operator+(const double c, const FunJet &u) { // check later
    FunJet res(u.getDiffSize());
    res.fx = c;
    return res + u;
}

FunJet operator+(const FunJet &u, const double c) { return c + u; }

FunJet operator-(const FunJet &u, const FunJet &v) {
    assert(u.getDiffSize() == v.diffs.size());
    FunJet res = u;
    res.fx -= v.fx;
    for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] -= v.diffs[i];
    return res;
}

FunJet operator-(const double c, const FunJet &u) {
    FunJet res(u.getDiffSize());
    res.fx = c;
    return (res - u);
}

FunJet operator-(const FunJet &u, const double c) { return (-c + u); }

FunJet operator-(const FunJet &u) { return (-1 * u); }

FunJet operator*(const FunJet &u, const FunJet &v) {
    assert(u.getDiffSize() == v.diffs.size());
    FunJet res(u.getDiffSize());
    res.fx = u.fx * v.fx;
    for (unsigned i = 0; i < res.diffs.size(); ++i) res.diffs[i] = (u.fx * v.diffs[i]) + (u.diffs[i] * v.fx);
    return res;
}

FunJet operator*(const double c, const FunJet &u) { // TODO DOBRZE?
    FunJet res(u.getDiffSize());
    res.fx = c;
    return res * u;
}

FunJet operator*(const FunJet &u, const double c) { return c * u; }

FunJet operator/(const FunJet &u, const FunJet &v) {
    assert(u.getDiffSize() == v.diffs.size());
    FunJet res(u.getDiffSize());
    res.fx = u.fx / v.fx;
    for (unsigned i = 0; i < u.getDiffSize(); ++i) res.diffs[i] = (u.diffs[i] - (res.fx * v.diffs[i])) / v.fx;
    return res;
}

FunJet operator/(const FunJet &u, const double c) {
    FunJet res(u.getDiffSize());
    res.fx = c;
    return u / res;
}

FunJet operator/(const double c, const FunJet &u) {
    FunJet res(u.getDiffSize());
    res.fx = c;
    return res / u;
}

vector<double> FunJet::getDiffs() const {
    return diffs;
}

[[maybe_unused]] void FunJet::setVarOrder(vector<FunJet> &jets, unsigned int noOfVars) {
    for (unsigned i = 0; i < noOfVars; ++i) jets[i].diffs[i] = 0;
}

unsigned FunJet::getDiffSize() const { return diffs.size(); }

[[maybe_unused]] FunJet sin(const FunJet &u) {
    double cos_u = std::cos(u.fx);
    FunJet res = u;
    res.fx = std::sin(u.fx);
    for (auto& diff : res.diffs) diff *= cos_u;
    return res;
}

[[maybe_unused]] FunJet cos(const FunJet &u) {
    double sin_u = std::sin(u.fx);
    FunJet res = u;
    res.fx = std::cos(u.fx);
    for (auto& diff : res.diffs) diff *= (-sin_u);
    return res;
}

[[maybe_unused]] FunJet exp(const FunJet &u) {
    double exp_u = std::exp(u.fx);
    FunJet res = u;
    res.fx = exp_u;
    for (auto& diff : res.diffs) diff *= exp_u;
    return res;
}
