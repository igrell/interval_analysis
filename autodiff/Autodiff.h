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
    vector<double> diffs;

public:

    FunJet() : fx(0), diffs({}) {}

    explicit FunJet(unsigned noOfVars);

    // varFlag indicates which element from diffs is a variable
    FunJet(double _fx, unsigned varFlag, unsigned noOfVars);

    FunJet(double _fx, vector<double> _diffs);

    FunJet(const FunJet &jet) = default;

    [[nodiscard]] vector<double> getDiffs() const;

    [[maybe_unused]] static void setVarOrder(vector<FunJet> &jets, unsigned noOfVars);

    [[nodiscard]] unsigned getDiffSize() const;

    FunJet &operator=(const FunJet &jet) = default;

    friend FunJet operator+(const FunJet &u, const FunJet &v);

    friend FunJet operator+(double c, const FunJet &u);

    friend FunJet operator+(const FunJet &u, double c);

    friend FunJet operator-(const FunJet &u, const FunJet &v);

    friend FunJet operator-(double c, const FunJet &u);

    friend FunJet operator-(const FunJet &u, double c);

    friend FunJet operator-(const FunJet &u);

    friend FunJet operator*(const FunJet &u, const FunJet &v);

    friend FunJet operator*(double c, const FunJet &u);

    friend FunJet operator*(const FunJet &u, double c);

    friend FunJet operator/(const FunJet &u, const FunJet &v);

    friend FunJet operator/(const FunJet &u, double c);

    friend FunJet operator/(double c, const FunJet &u);

    friend FunJet sin(const FunJet &u);

    friend FunJet cos(const FunJet &u);

    friend FunJet exp(const FunJet &u);

    friend std::ostream &operator<<(std::ostream &ostream, const FunJet &funJet) {
        ostream << (funJet.fx == -0 ? 0 : funJet.fx);
        for (const auto &diff: funJet.diffs) { ostream << " " << (diff == -0 ? 0 : diff); }
        return ostream;
    }

};
