#include "Interval.h"
#include "EmptyIntersectionException.h"
#include "DivisionByZeroIntervalException.h"

using std::min, std::max, std::abs;


Interval Interval::operator-(const Interval &b) const {
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = this->lo - b.hi;
    fesetround(FE_UPWARD);
    double new_hi = this->hi - b.lo;
    fesetround(originalRounding);
//    std::string new_label = this->label + " - " + b.label;
//    return {new_lo, new_hi, new_label};
    return {new_lo, new_hi};
}

Interval Interval::operator+(const Interval &b) const {
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = this->lo + b.lo;
    fesetround(FE_UPWARD);
    double new_hi = this->hi + b.hi;
    fesetround(originalRounding);
//    std::string new_label = this->label + " + " + b.label;
//    return {new_lo, new_hi, new_label};
    return {new_lo, new_hi};
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
//    std::string new_label = this->label + " * " + b.label;
//    return {new_lo, new_hi, new_label};
    return {new_lo, new_hi};
}

Interval Interval::operator/(const Interval &b) const {
    if ((b.lo <= 0 and b.hi >= 0) or (b.lo >= 0 and b.hi <= 0)) { //if 'b' contains 0
        throw DivisionByZeroIntervalException(*this, b);
//        cout << "Division by interval containing zero: " << *this << " , " << b << "\n";
//        return Interval(0);
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
//    std::string new_label = this->label + " / " + b.label;
//    return {new_lo, new_hi, new_label};
    return {new_lo, new_hi};
}

Interval Interval::operator+(const double &a) const {
//    return {get_lo() + a, get_hi() + a, get_label()};
    return {get_lo() + a, get_hi() + a};
}

Interval Interval::operator-(const double &a) const {
//    return {get_lo() - a, get_hi() - a, get_label()};
    return {get_lo() - a, get_hi() - a};
}

Interval Interval::operator*(const double &a) const { //not sure if it should work like that
//    return {get_lo() * a, get_hi() * a, this->get_label()};
    return {get_lo() * a, get_hi() * a};
}

Interval Interval::operator/(const double &a) {
    if (a == 0) throw DivisionByZeroIntervalException(*this, Interval(a));
    const int originalRounding = fegetround();
    fesetround(FE_DOWNWARD);
    double new_lo = get_lo() / a;
    fesetround(FE_UPWARD);
    double new_hi = get_hi() / a;
    fesetround(originalRounding);
//    return {new_lo, new_hi, get_label()};
    return {new_lo, new_hi};
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
    if (get_hi() < a.get_lo() || get_lo() > a.get_hi()) throw EmptyIntersectionException(*this, a);
    return {max(get_lo(), a.get_lo()), min(get_hi(), a.get_hi())};
}

Interval Interval::operator||(const Interval &a) const {
    if ((get_lo() < a.get_lo() and get_hi() < a.get_lo()) or (a.get_hi() < get_lo()))
        throw EmptyIntersectionException(*this, a);
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

//Interval::Interval(double lo, double hi, std::string label) : lo(lo), hi(hi), label(std::move(label)) {
////    if (lo > hi and (lo > 0 and hi > 0)) {
////        std::cout << "The endpoints of interval: " << *this << "do not define an interval." << std::endl;
////        return;
////    }
//}

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

double Interval::center() const {
    return ((lo + hi) / 2);
}

bool Interval::containsZero() const {
    return lo < 0 and hi > 0;
    // return lo * hi < 0;
}

std::ostream &operator<<(std::ostream &stream, const Interval &a) {
    stream << std::setprecision(17) << "[" << a.get_lo() << " , " << a.get_hi() << "]";
    return stream;
}

Interval operator-(double b, Interval a) {
//    return {b - a.get_lo(), b - a.get_hi(), a.get_label()};
    return {b - a.get_lo(), b - a.get_hi()};
}

Interval operator*(double a, Interval b) {
    return {a * b.get_lo(), a * b.get_hi()};
}

template<double (*f)(double), int R>
double applyFunWithRounding(double a) {
    const int originalRounding = fegetround();
    fesetround(R);
    double res = f(a);
    fesetround(originalRounding);
    return res;
}

template<double (*f)(double, double), int R>
double applyFunWithRounding(double a, double b) {
    const int originalRounding = fegetround();
    fesetround(R);
    double res = f(a, b);
    fesetround(originalRounding);
    return res;
}

template<double(*f)(double)>
Interval applyFunToInterval(const Interval &interval) {
    return {applyFunWithRounding<f, FE_DOWNWARD>(interval.get_lo()),
            applyFunWithRounding<f, FE_UPWARD>(interval.get_hi())};
}

Interval sqrt(const Interval &interval) { return applyFunToInterval<sqrt>(interval); }

Interval cbrt(const Interval &interval) { return applyFunToInterval<cbrt>(interval); }

Interval log(const Interval &interval) { return applyFunToInterval<log>(interval); }

Interval exp(const Interval &interval) { return applyFunToInterval<exp>(interval); }

Interval pow_naive(const Interval &x, const Interval &y) { return exp(y * log(x)); }

template<double (*f)(double, double)>
void setIntervalEnds(Interval &interval, double lo_y, double lo_l, double hi_y, double hi_l) {
    fesetround(FE_DOWNWARD);
    interval.set_lo(f(lo_y, lo_l));
    fesetround(FE_UPWARD);
    interval.set_hi(f(hi_y, hi_l));
}

auto multiply = [](double a, double b) { return a * b; };

Interval pow1(const Interval &x, const Interval &y) {
    Interval l;
    if (x.get_lo() < 1 or 0 <= y.get_lo() or y.get_hi() <= 0)
        l.set_lo(applyFunWithRounding<log, FE_DOWNWARD>(x.get_lo()));
    if (1 < x.get_hi() or 0 <= y.get_lo() or y.get_hi() <= 0)
        l.set_hi(applyFunWithRounding<log, FE_UPWARD>(x.get_hi()));
    Interval m;
    const int originalRounding = fegetround();
    if (0 <= y.get_lo()) {
        if (x.get_hi() <= 1) {
            setIntervalEnds<multiply>(m, y.get_hi(), l.get_lo(), y.get_lo(), l.get_hi());
        } else if (1 <= x.get_lo()) {
            fesetround(FE_DOWNWARD);
            m.set_lo(y.get_lo() * l.get_lo());
            m.set_hi(y.get_hi() * l.get_hi());
        } else {
            setIntervalEnds<multiply>(m, y.get_hi(), l.get_lo(), y.get_hi(), l.get_hi());
        }
    } else if (y.get_hi() <= 0) {
        if (x.get_hi() <= 1) {
            setIntervalEnds<multiply>(m, y.get_hi(), l.get_hi(), y.get_lo(), l.get_lo());
        } else if (1 <= x.get_lo()) {
            fesetround(FE_DOWNWARD);
            m.set_lo(y.get_lo() * l.get_hi());
            m.set_hi(y.get_hi() * l.get_lo());
        } else {
            setIntervalEnds<multiply>(m, y.get_lo(), l.get_hi(), y.get_lo(), l.get_lo());
        }
    } else {
        if (x.get_hi() <= 1) {
            setIntervalEnds<multiply>(m, y.get_hi(), l.get_lo(), y.get_lo(), l.get_hi());
        } else if (1 <= x.get_lo()) {
            setIntervalEnds<multiply>(m, y.get_lo(), l.get_hi(), y.get_hi(), l.get_hi());
        } else {
            fesetround(FE_DOWNWARD);
            m.set_lo(std::min(y.get_hi() * l.get_lo(), y.get_lo() * y.get_hi()));
            fesetround(FE_UPWARD);
            m.set_hi(std::max(y.get_lo() * l.get_lo(), y.get_hi() * l.get_hi()));
        }
    }
    Interval res;
    fesetround(FE_DOWNWARD);
    res.set_lo(exp(m.get_lo()));
    fesetround(FE_UPWARD);
    res.set_hi(exp(m.get_hi()));
    fesetround(originalRounding);
    return res;
}

// explicit instantiation of <<
template<> std::ostream &operator
<<<Interval>(
std::ostream &ostream,
const std::pair<Interval, Interval> &pair
) {
ostream << "{ " << pair.first << " ; " << pair.second << " }\n";
return
ostream;
}

template<> std::ostream &operator
<<<double>(
std::ostream &ostream,
const std::pair<double, double> &pair
) {
ostream << "[ " << pair.first << " ; " << pair.second << " ]\n";
return
ostream;
}

