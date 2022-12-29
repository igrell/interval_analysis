#include "SiviaNode.h"

ostream &operator<<(ostream &ostream, const Operator prev_operator) {
    switch (prev_operator) {
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

ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode) {
    bool left_null = siviaNode.left_parent == nullptr;
    bool right_null = siviaNode.right_parent == nullptr;
    if (left_null and right_null) ostream << siviaNode.val << "\n"; // leaf
    else if (left_null) ostream << siviaNode.right_parent->val << "\n";
    else if (right_null) {
        if (siviaNode.constant != INT_MIN) { // there is a constant to display
            ostream << siviaNode.left_parent->val << siviaNode.parents_operator << siviaNode.constant << " = "
                    << siviaNode.val << "\n";
        } else {
            ostream << siviaNode.left_parent->val << "\n";
        }
    } else {
        ostream << siviaNode.left_parent->val << siviaNode.parents_operator << siviaNode.right_parent->val
                << " = " << siviaNode.val << "\n";
    }
    return ostream;
}

SiviaNode::SiviaNode(SiviaNode *prev_left, SiviaNode *prev_right, const Operator prev_operator) :
        left_parent(prev_left), right_parent(prev_right), parents_operator(prev_operator) {
    switch (prev_operator) {
        case add:
            val = (*prev_left).val + (*prev_right).val;
            break;
        case sub:
            val = (*prev_left).val - (*prev_right).val;
            break;
        case mul:
            val = (*prev_left).val * (*prev_right).val;
            break;
        case dv:
            val = (*prev_left).val / (*prev_right).val;
            break;
    }

}

SiviaNode::SiviaNode(SiviaNode *prev_left, double constant, Operator prev_operator) :
        left_parent(prev_left), parents_operator(prev_operator), constant(constant) {
    switch (prev_operator) {
        case add:
            val = (*prev_left).val + constant;
            break;
        case sub:
            val = (*prev_left).val - constant;
            break;
        case mul:
            val = (*prev_left).val * constant;
            break;
        case dv:
            val = (*prev_left).val / constant;
            break;
    }
}
