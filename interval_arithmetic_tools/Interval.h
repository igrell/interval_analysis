#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <iostream>
#include "algorithm"
#include <cfenv>
#include <utility>
#include <bits/stdc++.h>
#include "sstream"

using std::cout, std::string, std::ostream, std::pair;


class Interval {
    double lo, hi;

public:

    Interval() : lo(0), hi(0) {};

    explicit Interval(double number) : lo(number), hi(number) {} //for a thin interval

    Interval(const Interval &interval) : lo(interval.get_lo()), hi(interval.get_hi()) {} //copying constructor

    Interval(double lo, double hi);

    [[nodiscard]] double get_lo() const { return lo; }

    [[nodiscard]] double get_hi() const { return hi; }

    void set_lo(double new_lo) { lo = new_lo; }

    void set_hi(double new_hi) { hi = new_hi; }

    [[nodiscard]] double width() const;

    double center() const;

    Interval operator+(const Interval &) const;

    Interval &operator+=(const Interval &);

    Interval operator-(const Interval &) const;

    Interval operator*(const Interval &) const;

    Interval operator/(const Interval &) const;

    Interval operator-() const; //change of sign with switching lo and hi

    Interval operator+(const double &) const;

    Interval operator-(const double &) const;

    Interval operator*(const double &) const;

    Interval operator/(const double &);

    bool operator==(const Interval &) const;

    bool operator!=(const Interval &) const;

    bool operator<=(const Interval &) const; // set-theory inclusion

    bool operator<(const Interval &) const; // set-theory proper-inclusion

    Interval operator&&(const Interval &) const; // intersection

    Interval operator||(const Interval &) const; //hull

    bool containsZero() const;

};

Interval operator-(double, Interval);

Interval operator*(double, Interval);


template<double(*f)(double, double)>
Interval applyFunToInterval(const Interval &); // template for all simple interval math. operations with rounding

Interval log(const Interval &);

Interval exp(const Interval &);

/// Power functions by Oliver Heimlich 2013
Interval pow_naive(const Interval &, const Interval &);

Interval pow1(const Interval &, const Interval &);

template<typename F>
Interval sqrt(F f, const Interval &);

Interval cbrt(const Interval &);

/* int parameter -> rounding mode FE_DOWNWARD/FE_UPWARD */
template<double(*)(double), int>
double applyFunWithRounding(double);


template<double (*)(double ,double ), int>
double applyFunWithRounding(double, double);

/* helper function for pow1 to avoid copy-pasting code */
template<double(*)(double, double)>
void setIntervalEnds(Interval &interval, double lo_y, double lo_l, double hi_y, double hi_l);

ostream &operator<<(ostream &ostream, const Interval &interval);

template<typename T>
ostream &operator<<(ostream &, const pair<T, T> &);

#endif