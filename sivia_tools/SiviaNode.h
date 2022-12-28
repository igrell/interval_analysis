#ifndef INTERVAL_ANALYSIS_SIVIANODE_H
#define INTERVAL_ANALYSIS_SIVIANODE_H

#include "../interval_arithmetic_tools/Interval.h"

enum Operator {
    add, sub, mul, dv, pw
};

class SiviaNode {
    Interval val = Interval();
    SiviaNode *prev_left = nullptr;
    SiviaNode *prev_right = nullptr;
    Operator prev_operator = Operator(-1);

public:

    SiviaNode() = default;

    explicit SiviaNode(const Interval &val) : val(val) {}

    explicit SiviaNode(const Operator &prev_operator) : prev_operator(prev_operator) {}

    SiviaNode(SiviaNode *prev_left, SiviaNode *prev_right, const Operator prev_operator) :
            prev_left(prev_left), prev_right(prev_right), prev_operator(prev_operator) {


    }

};

ostream &operator<<(ostream &ostream, Operator prev_operator);

ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode);

#endif //INTERVAL_ANALYSIS_SIVIANODE_H
