#include "SiviaGraph.h"


//ostream &operator<<(ostream &ostream, const SiviaGraph &siviaGraph) { //TODO
//    SiviaNode node = siviaGraph.expression;
//    ostream << node;
//    return ostream;
//}

ostream &operator<<(ostream &ostream, const Restriction &restriction) {
    switch (restriction) {
        case eq:
            ostream << "==";
            break;
        case geq:
            ostream << ">=";
            break;
        case leq:
            ostream << "<=";
            break;
        case g:
            ostream << ">";
            break;
        case l:
            ostream << "<";
            break;
    }
    return ostream;
}

void SiviaGraph::add_restriction(const Restriction restriction) {
    restrictions.push_back(restriction);
}

void SiviaGraph::print_restrictions() {
    for(auto restriction: restrictions) {
        cout << restriction << "  ";
    }
    cout << "\n";
}

void SiviaGraph::contract_solutions() {

}

