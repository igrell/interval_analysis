#ifndef INTERVAL_ANALYSIS_SIVIANODE_H
#define INTERVAL_ANALYSIS_SIVIANODE_H

#include "../interval_arithmetic_tools/Interval.h"

enum Operator {
    add, sub, mul, dv
};

class SiviaNode {
    Interval val = Interval();
    double constant = INT_MIN; // useful when doing a unary operation by a constant
    SiviaNode *left_parent = nullptr;
    SiviaNode *right_parent = nullptr;
    Operator parents_operator = Operator(-1);

public:

    SiviaNode() = default;

    explicit SiviaNode(const Interval &val) : val(val) {}

    explicit SiviaNode(const Operator &prev_operator) : parents_operator(prev_operator) {}

    SiviaNode(SiviaNode *prev_left, SiviaNode *prev_right, Operator prev_operator);

    /* assumption - when changing by a constant, we make changing node the left parent */
    SiviaNode(SiviaNode *prev_left, double constant, Operator prev_operator);

    friend ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode);

};

ostream &operator<<(ostream &ostream, Operator prev_operator);

#endif //INTERVAL_ANALYSIS_SIVIANODE_H
