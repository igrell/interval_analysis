#ifndef INTERVAL_ANALYSIS_SIVIANODE_H
#define INTERVAL_ANALYSIS_SIVIANODE_H

#include "../interval_arithmetic_tools/Interval.h"

enum Operator {
    add, sub, mul, dv
};

class SiviaNode {
    Interval val = Interval();
    Operator parents_operator = Operator(-1);
//    double constant = INT_MIN; // useful when doing a unary operation by a constant
    SiviaNode *left_parent = nullptr;
    SiviaNode *right_parent = nullptr;

public:

    SiviaNode() = default;

    explicit SiviaNode(const Operator &prev_operator) : parents_operator(prev_operator) {}

    SiviaNode(SiviaNode *prev_left, SiviaNode *prev_right, Operator prev_operator);

    ~SiviaNode() = default;

//    /* assumption - when changing by a constant, we make changing node the left parent */
//    SiviaNode(SiviaNode *prev_left, double constant, Operator prev_operator);

    void setValue(const Interval);

    void setValue(const double);

    void setValue(const double, const double);

    void evaluate();

    void contract();

    SiviaNode operator+(const SiviaNode &) const;

    SiviaNode operator-(const SiviaNode &) const;

    SiviaNode operator*(const SiviaNode &) const;

    SiviaNode operator/(const SiviaNode &) const;

    SiviaNode operator+(SiviaNode *) const;

    SiviaNode operator-(const SiviaNode *) const;

    SiviaNode operator*(const SiviaNode *) const;

    SiviaNode operator/(const SiviaNode *) const;

    friend ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode);

};

ostream &operator<<(ostream &ostream, Operator prev_operator);

#endif //INTERVAL_ANALYSIS_SIVIANODE_H
