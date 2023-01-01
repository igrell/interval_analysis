#include "SiviaNode.h"

ostream &operator<<(ostream &ostream, const Operator parent_operator) {
    switch (parent_operator) {
        case nil:
            break;
        case add:
            ostream << " + ";
            break;
        case sub:
            ostream << " - ";
            break;
        case mul:
            ostream << " * ";
            break;
        case dv:
            ostream << " / ";
            break;
    }
    return ostream;
}

ostream &operator<<(ostream &ostream, const SiviaNode &node) {
    bool left_null = node.left_parent == nullptr;
    bool right_null = node.right_parent == nullptr;
    if (!left_null) ostream << node.left_parent->getValue();
    ostream << node.parents_operator;
    if (!right_null) ostream << node.right_parent->getValue();
    ostream << " = " << node.val;
    return ostream;
}


SiviaNode::SiviaNode(const Interval &val) : val(val) {}

SiviaNode::SiviaNode(SiviaNode *left_parent, SiviaNode *right_parent, Operator parents_operator) :
        left_parent(left_parent), right_parent(right_parent), parents_operator(parents_operator) {}

void SiviaNode::setValue(const Interval &interval) {
    val = interval;
}

void SiviaNode::setValue(const double value) {
    setValue(Interval(value));
}

void SiviaNode::setValue(const double lo, const double hi) {
    setValue(Interval(lo, hi));

}

Interval SiviaNode::evaluate() {
    switch (parents_operator) {
        case nil:
            return this->val;
        case add:
            return this->val = left_parent->evaluate() + right_parent->evaluate();
        case sub:
            return this->val = left_parent->evaluate() - right_parent->evaluate();
        case mul:
            return this->val = left_parent->evaluate() * right_parent->evaluate();
        case dv:
            return this->val = left_parent->evaluate() / right_parent->evaluate();
    }
}

/* Backwards propagating constrains to narrow down the solution intervals */
void SiviaNode::contract() {
    cout << this->getValue() << "\n";
    switch (parents_operator) {
        case nil:
            return;
        case add:
//            cout << "before: " << left_parent << right_parent << "\n";
            left_parent->setValue(left_parent->getValue() && (val - right_parent->getValue()));
            right_parent->setValue(right_parent->getValue() && (val - left_parent->getValue()));
//            cout << "after: " << left_parent << right_parent << "\n";
            left_parent->contract();
            right_parent->contract();
            break;
        case sub:
            left_parent->setValue(left_parent->getValue() && (val + right_parent->getValue()));
            right_parent->setValue(right_parent->getValue() && (left_parent->getValue() - val));
            left_parent->contract();
            right_parent->contract();
            break;
        case mul:
            left_parent->setValue(left_parent->getValue() && (val / right_parent->getValue()));
            right_parent->setValue(right_parent->getValue() && (val / left_parent->getValue()));
            left_parent->contract();
            right_parent->contract();
            break;
        case dv:
            left_parent->setValue(left_parent->getValue() && (right_parent->getValue() * val));
            right_parent->setValue(right_parent->getValue() && (right_parent->getValue() / val));
            left_parent->contract();
            right_parent->contract();
            break;
    }


}

Interval SiviaNode::getValue() {
    return val;
}

SiviaNode &operator+(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, add); }

SiviaNode &operator-(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, sub); }

SiviaNode &operator*(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, mul); }

SiviaNode &operator/(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, dv); }
