#ifndef INTERVAL_ANALYSIS_SIVIANODE_H
#define INTERVAL_ANALYSIS_SIVIANODE_H

#include "../interval_arithmetic_tools/Interval.h"

// respectively + , - , * , / , no operator
enum Operator {
    add, sub, mul, dv, nil
};

class SiviaNode {
    Interval val = Interval();
    Operator parents_operator = nil;
    SiviaNode *left_parent = nullptr;
    SiviaNode *right_parent = nullptr;

public:

    SiviaNode() = default;

    explicit SiviaNode(const Interval &val);

    SiviaNode(SiviaNode *left_parent, SiviaNode *right_parent, Operator parents_operator);

    ~SiviaNode() = default;

    Interval evaluate();

    Interval getValue();

    void setValue(double);

    void setValue(const Interval &);

    void setValue(double, double);

    void contract();

    friend ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode);

};

SiviaNode &operator+(SiviaNode &, SiviaNode &);

SiviaNode &operator-(SiviaNode &, SiviaNode &);

SiviaNode &operator*(SiviaNode &, SiviaNode &);

SiviaNode &operator/(SiviaNode &, SiviaNode &);

ostream &operator<<(ostream &ostream, Operator parent_operator);

#endif //INTERVAL_ANALYSIS_SIVIANODE_H
