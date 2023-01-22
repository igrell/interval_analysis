#include "SiviaGraph.h"

SiviaGraphNode::SiviaGraphNode(SiviaNode &node) {
    val = node.getValue();
    operation = node.getOperation();
}

void SiviaGraphNode::setLeft(const int a) {
    left = a;
}

void SiviaGraphNode::setRight(const int a) {
    right = a;
}
