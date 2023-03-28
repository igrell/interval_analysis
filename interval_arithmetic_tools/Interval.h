#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include <iostream>
#include "algorithm"
#include <cfenv>
#include <utility>
#include <bits/stdc++.h>
#include "sstream"

using std::cout, std::string, std::ostream, std::pair;


class Interval {
//    string label = " ";
    double lo, hi;

public:

    Interval() : lo(0), hi(0) {};

    explicit Interval(double number) : lo(number), hi(number) {} //for a thin interval - no label

//    Interval(double number, string label) : lo(number), hi(number), label(std::move(label)) {} //with label

    Interval(const Interval &interval) : lo(interval.get_lo()), hi(interval.get_hi()) {} //copying constructor

    Interval(double lo, double hi);

//    Interval(initializer_list<double> list) : lo(*list.begin()), hi(*(list.begin()++)) {}

//    Interval(double lo, double hi, string label);

    [[nodiscard]] double get_lo() const { return lo; }

    [[nodiscard]] double get_hi() const { return hi; }

//    string get_label() { return label; }

    void set_lo(double new_lo) { lo = new_lo; }

    void set_hi(double new_hi) { hi = new_hi; }

//    void set_label(string new_label) { label = std::move(new_label); }

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

Interval sqrt(const Interval &);

Interval cbrt(const Interval &);

enum Rounding {
    up, down
};

template<Rounding, double(*)(double)>
double applyFunWithRounding(double);

template<Rounding, double(*)(double, double)>
double applyFunWithRounding(double, double);

ostream &operator<<(ostream &ostream, const Interval &interval);

template<typename T>
ostream &operator<<(ostream &, const pair<T, T> &);

#endif