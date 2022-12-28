#ifndef INTERVAL_ANALYSIS_SIVIAGRAPH_H
#define INTERVAL_ANALYSIS_SIVIAGRAPH_H

#include <utility>

#include "SiviaNode.h"
#include "vector"

using std::vector;


class SiviaGraph {
    SiviaNode expression = SiviaNode();

public:
    explicit SiviaGraph(SiviaNode expression) : expression(std::move(expression)) {}


    void evaluate_expression();
};


#endif //INTERVAL_ANALYSIS_SIVIAGRAPH_H
