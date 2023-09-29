#ifndef INTERVAL_ANALYSIS_SIVIANODE_H
#define INTERVAL_ANALYSIS_SIVIANODE_H

#include "Interval.h"
#include "vector"

using std::vector;

// respectively + , - , * , / , no operator
enum Operator {
    add, sub, mul, dv, nil
};

class SiviaNode {
    Interval val = Interval();
    Operator operation = nil;
    SiviaNode *left = nullptr;
    SiviaNode *right = nullptr;

public:

    SiviaNode() = default;

    explicit SiviaNode(const Interval &val);

    SiviaNode(SiviaNode *left_parent, SiviaNode *right_parent, Operator parents_operator);

    Interval evaluate();

    Interval getValue();

    Operator getOperation();

    void setValue(double);

    void setValue(const Interval &);

    void setValue(double, double);

    void contract();

    static void getNodesVector(vector<SiviaNode *> &, SiviaNode *);

    void free();

    friend ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode);

    static void setValue(pair<SiviaNode, SiviaNode>&, double);

    static void setValue(pair<SiviaNode& , SiviaNode& >&, const pair<Interval, Interval>&);

    static void contract(pair<SiviaNode, SiviaNode>&);
};

SiviaNode &operator+(SiviaNode &, SiviaNode &);

SiviaNode &operator-(SiviaNode &, SiviaNode &);

SiviaNode &operator*(SiviaNode &, SiviaNode &);

SiviaNode &operator/(SiviaNode &, SiviaNode &);

ostream &operator<<(ostream &ostream, Operator parent_operator);

#endif //INTERVAL_ANALYSIS_SIVIANODE_H
