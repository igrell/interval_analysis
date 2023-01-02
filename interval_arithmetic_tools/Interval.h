#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include <iostream>
#include "algorithm"
#include <cfenv>
#include <utility>
#include <bits/stdc++.h>
#include "sstream"

using std::cout, std::string,std::ostream, std::pair;


class Interval {
//    string label = " ";
    double lo, hi;

public:

    Interval() : lo(0), hi(0) {};

    explicit Interval(double number) : lo(number), hi(number) {} //for a thin interval - no label

//    Interval(double number, string label) : lo(number), hi(number), label(std::move(label)) {} //with label

    Interval(const Interval &interval) : lo(interval.get_lo()), hi(interval.get_hi()) {} //copying constructor

    Interval(double lo, double hi);

//    Interval(double lo, double hi, string label);

    [[nodiscard]] double get_lo() const { return lo; }

    [[nodiscard]] double get_hi() const { return hi; }

//    string get_label() { return label; }

    void set_lo(double new_lo) { lo = new_lo; }

    void set_hi(double new_hi) { hi = new_hi; }

//    void set_label(string new_label) { label = std::move(new_label); }

    [[nodiscard]] double width() const;

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

ostream &operator<<(ostream &ostream, const Interval &interval);

template<typename T>
ostream &operator<<(ostream &, const pair<T, T> &);

#endif