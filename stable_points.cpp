#include "Interval.h"
#include "SiviaNode.h"
#include "vector"
#include "list"

using std::cout, std::vector, std::list;

template<typename T>
T fun(const T &x, const T &y) { return x * x * x * y; }

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

void
rootFinder(Interval (*fun)(const Interval &, const Interval &),
           pair<const Interval &, const Interval &> domain,
           const unsigned GRID_FACTOR) {
    list<pair<Interval, Interval>> domainCubes = gridDomain(domain, GRID_FACTOR);
    for (const auto &pair: domainCubes) std::cout << pair.first << " " << pair.second << "\n";
    auto it = domainCubes.begin();
    while (it != domainCubes.end()) {
        if (!fun(it->first, it->second).containsZero()) {
            it = domainCubes.erase(it);
        } else ++it;
    }
    SiviaNode &x = *new SiviaNode();
    SiviaNode &y = *new SiviaNode();
    for (const auto& domainCube: domainCubes) {
        x.setValue(domainCube.first);
        y.setValue(domainCube.second);
    }

}

int main() {
    pair<Interval, Interval> domain = {{-2, 2},
                                       {2,  6}};
    rootFinder(fun, domain, 3);
}