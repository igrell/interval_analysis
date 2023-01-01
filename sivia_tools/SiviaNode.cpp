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

//ostream &operator<<(ostream &ostream, const SiviaNode &node) {
//    bool left_null = node.left_parent == nullptr;
//    bool right_null = node.right_parent == nullptr;
//    if (left_null and right_null) ostream << node.val << "\n"; // leaf
//    else if (left_null) ostream << node.right_parent->val << "\n";
//    else if (right_null) {
//        if (node.constant != INT_MIN) { // there is a constant to display
//            ostream << node.left_parent->val << node.parents_operator << node.constant << " = "
//                    << node.val << "\n";
//        } else {
//            ostream << node.left_parent->val << "\n";
//        }
//    } else {
//        ostream << node.left_parent->val << node.parents_operator << node.right_parent->val
//                << " = " << node.val << "\n";
//    }
//    return ostream;
//}


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

void SiviaNode::contract() {


}

Interval SiviaNode::getValue() {
    return val;
}

SiviaNode &operator+(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, add); }

SiviaNode &operator-(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, sub); }

SiviaNode &operator*(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, mul); }

SiviaNode &operator/(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, dv); }
