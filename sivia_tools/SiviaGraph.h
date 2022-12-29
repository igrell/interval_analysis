#ifndef INTERVAL_ANALYSIS_SIVIAGRAPH_H
#define INTERVAL_ANALYSIS_SIVIAGRAPH_H

#include <utility>

#include "SiviaNode.h"
#include "vector"

using std::vector;

enum Restriction { // == 0, >= 0, <= 0, > 0, < 0
    eq, geq, leq, g, l
};

class SiviaGraph {
    SiviaNode expression = SiviaNode();
    vector<Restriction> restrictions;

public:
    explicit SiviaGraph(SiviaNode expression) : expression(std::move(expression)) {} // no initial restrictions

    SiviaGraph(SiviaNode expression, vector<Restriction> restrictions) : // multiple initial restrictions
            expression(std::move(expression)), restrictions(std::move(restrictions)) {}

    SiviaGraph(SiviaNode expression, Restriction restriction) : // one initial restriction
            expression(std::move(expression)) {
        restrictions.push_back(restriction);
    }

    void add_restriction(Restriction restriction);

    void print_restrictions();

    void contract_solutions(); // backwards propagation of restrictions to contract solutions


    friend ostream &operator<<(ostream &ostream, const SiviaGraph &siviaGraph);
};

ostream &operator<<(ostream &ostream, const Restriction &restriction);

#endif //INTERVAL_ANALYSIS_SIVIAGRAPH_H
