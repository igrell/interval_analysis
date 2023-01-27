#include "SiviaNode.h"
#include "DivisionByZeroIntervalException.h"

using std::find;

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
    }
    return ostream;
}

ostream &operator<<(ostream &ostream, const SiviaNode &node) {
    bool left_null = node.left == nullptr;
    bool right_null = node.right == nullptr;
    if (!left_null) ostream << node.left->getValue();
    ostream << node.operation;
    if (!right_null) ostream << node.right->getValue();
    ostream << " = " << node.val;
    return ostream;
}


SiviaNode::SiviaNode(const Interval &val) : val(val) {}

SiviaNode::SiviaNode(SiviaNode *left_parent, SiviaNode *right_parent, Operator parents_operator) :
        left(left_parent), right(right_parent), operation(parents_operator) {}

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
    switch (operation) {
        case nil:
            return this->val;
        case add:
            return this->val = left->evaluate() + right->evaluate();
        case sub:
            return this->val = left->evaluate() - right->evaluate();
        case mul:
            return this->val = left->evaluate() * right->evaluate();
        case dv:
            return this->val = left->evaluate() / right->evaluate();
    }
}

/* Backwards propagating constrains to narrow down the solution intervals */
void SiviaNode::contract() {
    switch (operation) {
        case nil:
            return;
        case add:
            try {
                left->setValue(left->getValue() && (val - right->getValue()));
            } catch (DivisionByZeroIntervalException &warning) {}
            try {
                right->setValue(right->getValue() && (val - left->getValue()));
            } catch (DivisionByZeroIntervalException &warning) {}
            left->contract();
            right->contract();
            break;
        case sub:
            try {
                left->setValue(left->getValue() && (val + right->getValue()));
            } catch (DivisionByZeroIntervalException &warning) {}
            try {
                right->setValue(right->getValue() && (left->getValue() - val));
            } catch (DivisionByZeroIntervalException &warning) {}
            left->contract();
            right->contract();
            break;
        case mul:
            try {
                left->setValue(left->getValue() && (val / right->getValue()));
            } catch (DivisionByZeroIntervalException &warning) {}
            try {
                right->setValue(right->getValue() && (val / left->getValue()));
            } catch (DivisionByZeroIntervalException &warning) {}
            left->contract();
            right->contract();
            break;
        case dv:
            try {
                left->setValue(left->getValue() && (right->getValue() * val));
            } catch (DivisionByZeroIntervalException &warning) {}
            try {
                right->setValue(right->getValue() && (right->getValue() / val));
            } catch (DivisionByZeroIntervalException &warning) {}
            left->contract();
            right->contract();
    }
}


Interval SiviaNode::getValue() { return val; }

void SiviaNode::getNodesVector(vector<SiviaNode *> &vector, SiviaNode *nodePtr) {
    if (find(vector.begin(), vector.end(), nodePtr) != vector.end()) return; // to avoid duplicates
    vector.push_back(nodePtr);
    if (nodePtr->left != nullptr) getNodesVector(vector, nodePtr->left);
    if (nodePtr->right != nullptr) getNodesVector(vector, nodePtr->right);
}

void SiviaNode::free() {
    vector<SiviaNode *> nodesVector;
    getNodesVector(nodesVector, this);
    for (auto &el: nodesVector) delete el;
}

Operator SiviaNode::getOperation() {
    return operation;
}

SiviaNode &operator+(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, add); }

SiviaNode &operator-(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, sub); }

SiviaNode &operator*(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, mul); }

SiviaNode &operator/(SiviaNode &a, SiviaNode &b) { return *new SiviaNode(&a, &b, dv); }
