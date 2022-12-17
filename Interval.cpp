#include "Interval.h"

using std::min, std::max, std::abs;

Interval Interval::operator-(const Interval &b) const {
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = this->lo - b.hi;
    fesetround(FE_UPWARD);
    double new_hi = this->hi - b.lo;
    fesetround(originalRounding);
    std::string new_label = this->label + " - " + b.label;
    return {new_lo, new_hi, new_label};
}

Interval Interval::operator+(const Interval &b) const {
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = this->lo + b.lo;
    fesetround(FE_UPWARD);
    double new_hi = this->hi + b.hi;
    fesetround(originalRounding);
    std::string new_label = this->label + " + " + b.label;
    return {new_lo, new_hi, new_label};
}

Interval Interval::operator*(const Interval &b) const {
    const int originalRounding = fegetround();
    double res1 = this->lo * b.lo;
    double res2 = this->lo * b.hi;
    double res3 = this->hi * b.lo;
    double res4 = this->hi * b.hi;
    fesetround(FE_DOWNWARD);
    double new_lo = min(res1, std::min(res2, std::min(res3, res4)));
    fesetround(FE_UPWARD);
    double new_hi = max(res1, std::max(res2, std::max(res3, res4)));
    fesetround(originalRounding);
    std::string new_label = this->label + " * " + b.label;
    return {new_lo, new_hi, new_label};
}

Interval Interval::operator/(const Interval &b) const {
    if ((b.lo <= 0 and b.hi >= 0) or (b.lo >= 0 and b.hi <= 0)) { //if 'b' contains 0
        cout << "Division by interval containing zero.";
        return {0, 0, "error"};
    }
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double res1 = this->lo / b.lo;
    double res2 = this->lo / b.hi;
    double res3 = this->hi / b.lo;
    double res4 = this->hi / b.hi;
    double new_lo = min(res1, min(res2, min(res3, res4)));
    fesetround(FE_UPWARD);
    res1 = this->lo / b.lo;
    res2 = this->lo / b.hi;
    res3 = this->hi / b.lo;
    res4 = this->hi / b.hi;
    double new_hi = max(res1, max(res2, max(res3, res4)));
    fesetround(originalRounding);
    std::string new_label = this->label + " / " + b.label;
    return {new_lo, new_hi, new_label};
}

Interval Interval::operator+(const double &a) {
    return {get_lo() + a, get_hi() + a, get_label()};
}

Interval Interval::operator-(const double &a) {
    return {get_lo() - a, get_hi() - a, get_label()};
}

Interval Interval::operator*(const double &a) { //not sure if it should work like that
    return {get_lo() * a, get_hi() * a, this->get_label()};
}

Interval Interval::operator/(const double &a) {
    if (a == 0) {
        cout << "Division by zero.";
        return {0, 0, "null"};
    }
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = get_lo() / a;
    fesetround(FE_UPWARD);
    double new_hi = get_hi() / a;
    fesetround(originalRounding);
    return {new_lo, new_hi, get_label()};
}

bool Interval::operator==(const Interval &a) const {
    return (get_lo() == a.get_lo() and get_hi() == a.get_hi());
}

bool Interval::operator!=(const Interval &a) const {
    return (get_lo() != a.get_lo() or get_hi() != a.get_hi());
}

bool Interval::operator<(const Interval &a) const {
    return (get_lo() > a.get_lo() and get_hi() < a.get_hi());
}

bool Interval::operator<=(const Interval &a) const {
    return (get_lo() >= a.get_lo() and get_hi() <= a.get_hi());
}

Interval Interval::operator&&(const Interval &a) const {
    if (get_hi() < a.get_lo() || get_lo() > a.get_hi()) {
        cout << "Warning: empty intersection.";
        return Interval(0);
    }
    return {max(get_lo(), a.get_lo()), min(get_hi(), a.get_hi())};
}

Interval Interval::operator||(const Interval &a) const {
    if ((get_lo() < a.get_lo() and get_hi() < a.get_lo()) or (a.get_hi() < get_lo())) {
//        cout << "Warning: empty intersection for intervals " << *this << " , " << a << "\n";
        return Interval(0);
    }
//    cout << "min of lows: " << min(get_lo(),a.get_lo()) << "\n";
//    cout << "max of highs: "<< max(get_hi(),a.get_hi()) << "\n";
    return {min(get_lo(), a.get_lo()), max(get_hi(), a.get_hi())};
}

Interval::Interval(double lo, double hi) : lo(lo), hi(hi) {
//    if (lo > hi and (lo > 0 and hi > 0)) {
//        this->set_lo(lo);
//        this->set_hi(hi);
//        std::cout << "The endpoints of interval: " << *this << " do not define an interval." << std::endl;
//        return;
//    }
}

Interval::Interval(double lo, double hi, std::string label) : lo(lo), hi(hi), label(std::move(label)) {
//    if (lo > hi and (lo > 0 and hi > 0)) {
//        std::cout << "The endpoints of interval: " << *this << "do not define an interval." << std::endl;
//        return;
//    }
}

Interval Interval::operator-() const {
    return {(-1) * get_hi(), (-1) * get_lo()};
}

Interval &Interval::operator+=(const Interval &interval) {
    *this = *this + interval;
    return *this;
}

double Interval::width() const {
    return abs(get_hi() - get_lo());
}

std::ostream &operator<<(std::ostream &stream, const Interval &a) {
    stream << "[" << std::setprecision(17) << a.get_lo() << " , " << a.get_hi() << "]";
    return stream;
}

Interval operator-(double b, Interval a) {
    return {b - a.get_lo(), b - a.get_hi(), a.get_label()};
}

Interval operator*(double a, Interval b) {
    return {a * b.get_lo(), a * b.get_hi(), b.get_label()};
}

// explicit instantiation of <<
template<> std::ostream &operator<<<Interval>(std::ostream &ostream,const std::pair<Interval, Interval> &pair) {
ostream << "{ " << pair.first << " ; " << pair.second << " }\n";
return ostream;
}

template<> std::ostream &operator<<<double>(std::ostream &ostream,const std::pair<double, double> &pair) {
ostream << "[ " << pair.first << " ; " << pair.second << " ]\n";
return ostream;
}

