#include "SiviaNode.h"

//ostream &operator<<(ostream &ostream, const Operator prev_operator) {
//    switch (prev_operator) {
//        case add:
//            ostream << " + ";
//            break;
//        case sub:
//            ostream << " - ";
//            break;
//        case mul:
//            ostream << " * ";
//            break;
//        case dv:
//            ostream << " / ";
//            break;
//    }
//    return ostream;
//}
//
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
//
//SiviaNode::SiviaNode(SiviaNode *prev_left, SiviaNode *prev_right, const Operator prev_operator) :
//        left_parent(prev_left), right_parent(prev_right), parents_operator(prev_operator) {
//    switch (prev_operator) {
//        case add:
//            val = (*prev_left).val + (*prev_right).val;
//            break;
//        case sub:
//            val = (*prev_left).val - (*prev_right).val;
//            break;
//        case mul:
//            val = (*prev_left).val * (*prev_right).val;
//            break;
//        case dv:
//            val = (*prev_left).val / (*prev_right).val;
//            break;
//    }
//
//}
//
//SiviaNode::SiviaNode(SiviaNode *prev_left, double constant, Operator prev_operator) :
//        left_parent(prev_left), parents_operator(prev_operator), constant(constant) {
//    switch (prev_operator) {
//        case add:
//            val = (*prev_left).val + constant;
//            break;
//        case sub:
//            val = (*prev_left).val - constant;
//            break;
//        case mul:
//            val = (*prev_left).val * constant;
//            break;
//        case dv:
//            val = (*prev_left).val / constant;
//            break;
//    }
//}
//
//SiviaNode SiviaNode::operator+(const SiviaNode &node) const {
//    return SiviaNode(val + node.val);
//}
//
//SiviaNode SiviaNode::operator-(const SiviaNode &node) const {
//    return SiviaNode(val - node.val);
//}
//
//SiviaNode SiviaNode::operator*(const SiviaNode &node) const {
//    return SiviaNode(val * node.val);
//}
//
//SiviaNode SiviaNode::operator/(const SiviaNode &node) const {
//    return SiviaNode(val / node.val);
//}

//SiviaNode *SiviaNode::operator+(const SiviaNode *node_ptr) const {
//    return SiviaNode(val + node_ptr->val);
//}

void SiviaNode::setValue(const Interval val) {
    this->val = val;
}

void SiviaNode::setValue(const double val) {
    setValue(Interval(val));
}

void SiviaNode::setValue(const double lo, const double hi) {
    setValue(Interval(lo, hi));

}

void SiviaNode::evaluate() {

}

void SiviaNode::contract() {

}

SiviaNode SiviaNode::operator+(SiviaNode *node_ptr) const {
    return (*this) + (*node_ptr);
}
