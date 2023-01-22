#ifndef INTERVAL_ANALYSIS_SIVIAGRAPH_H
#define INTERVAL_ANALYSIS_SIVIAGRAPH_H

#include "SiviaNode.h"


struct SiviaGraphNode {
    Interval val = Interval();
    Operator operation = nil;
    int left = -1;
    int right = -1;

public:
    explicit SiviaGraphNode(SiviaNode &node);

    void setLeft(int);

    void setRight(int);

};


class SiviaGraph {
    vector<SiviaGraphNode> nodes;


public:
    SiviaGraph();


};


#endif //INTERVAL_ANALYSIS_SIVIAGRAPH_H
