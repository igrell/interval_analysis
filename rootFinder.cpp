#include "Interval.h"
#include "SiviaNode.h"
#include "IPoint.h"
#include "list"
#include "EmptyIntersectionException.h"

using std::cout, std::endl, std::vector, std::list;


list<pair<Interval, Interval>>
gridDomain(const pair<const Interval &, const Interval &> &domain, const unsigned GRID_FACTOR) {
    double x_dist = domain.first.width() / GRID_FACTOR;
    double y_dist = domain.second.width() / GRID_FACTOR;
    list<pair<Interval, Interval>> res;
    pair<Interval, Interval> pair_temp;
    for (unsigned i = 0; i < GRID_FACTOR; ++i) {
        pair_temp = {{domain.first.get_lo() + i * x_dist,  domain.first.get_lo() + (i + 1) * x_dist},
                     {domain.second.get_lo() + i * y_dist, domain.second.get_lo() + (i + 1) * y_dist}};
        res.emplace_back(pair_temp);
    }
    return res;
}

// fun : R2 -> R2
template<typename T>
pair<T, T> fun(T& x, T& y) { return {x * x * x * y ,  x + y}; }


/**
  * @brief Function for acquiring zeroes of a R2 -> R2 function in a given domain
  *  @tparam Fun    R2 -> R2 function.
  *  @param fun     Function of the form Fun.
  *  @param domain  Domain of fun().
  *  @param GRID_FACTOR      How coarsely the griding of the domain.
  *  @param TOL    Tolerance for root finding in the grided domain.
*/
template<class Fun>
void rootFinder(Fun fun,
                pair<const Interval &, const Interval &> domain,
                const unsigned GRID_FACTOR,
                const unsigned TOL) {
    list<pair<Interval, Interval>> domainCubes = gridDomain(domain, GRID_FACTOR);
    for (const auto &pair: domainCubes) std::cout << pair.first << " " << pair.second << "\n";
    auto it = domainCubes.begin();
    while (it != domainCubes.end()) {
        if (!IPoint(fun(it->first, it->second)).containsZero()) // cast to IPoint to invoke containsZero() method
            it = domainCubes.erase(it);
        else ++it;
    }
//    pair < SiviaNode & , SiviaNode &> args = {*new SiviaNode(), *new SiviaNode()};
//    SiviaNode &x = args.first, &y = args.second;
    SiviaNode &x = *new SiviaNode(); SiviaNode &y = *new SiviaNode();
    for (const auto &domainCube: domainCubes) {
//        SiviaNode::setValue(args, domainCube);
        x.setValue(domainCube.first);
        y.setValue(domainCube.second);
        pair < SiviaNode, SiviaNode > f = fun(x, y);
        SiviaNode::setValue(f, 0);
        try { SiviaNode::contract(f); } catch (EmptyIntersectionException &warning) {}
        cout << "from domainCube:" << domainCube << "restriction: " << "x" << x << ", y" << y << "\n"; // TODO nie reaguje na stałą?
    }
    // TODO ciąg dalszy
}

int main() {
    pair<Interval, Interval> domain = {{-10, 10},
                                       {-10,  10}};

    rootFinder([](auto x, auto y) { return fun(x, y); }, domain, 11, static_cast<unsigned int>(10e-5));
//    cout << Interval(-0.90909090909091006 , 0.90909090909090828) * Interval(-0.90909090909091006 , 0.90909090909090828) * Interval(-0.90909090909091006 , 0.90909090909090828) * Interval(-0.90909090909091006 , 0.90909090909090828);
}
