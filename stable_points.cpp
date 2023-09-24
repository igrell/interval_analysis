#include "Interval.h"
#include "vector"

using std::cout, std::vector;

Interval fun(const Interval &x, const Interval &y) { return x * x * x * y; }


vector<pair<Interval, Interval>>
gridDomain(const pair<const Interval &, const Interval &> &domain, const unsigned GRID_FACTOR) {
    double x_dist = domain.first.width() / GRID_FACTOR;
    double y_dist = domain.second.width() / GRID_FACTOR;
    vector<pair<Interval, Interval>> res;
    pair<Interval, Interval> pair_temp;
    for (unsigned i = 0; i < GRID_FACTOR; ++i) {
        pair_temp = {{domain.first.get_lo() + i * x_dist,  domain.first.get_lo() + (i + 1) * x_dist},
                     {domain.second.get_lo() + i * y_dist, domain.second.get_lo() + (i + 1) * y_dist}};
        res.emplace_back(pair_temp);
    }
    return res;
}

void
rootFinder(Interval (*fun)(const Interval &, const Interval &), pair<const Interval &, const Interval &> domain,
           const unsigned GRID_FACTOR) {
    vector<pair<Interval, Interval>> domainGridded = gridDomain(domain, GRID_FACTOR);
    for (const auto &pair: domainGridded) std::cout << pair.first << " " << pair.second << "\n";
    vector<pair < Interval, Interval>>
            domainContainingZero; // TODO efektywniejsza metoda
    for (const auto &domainCube: domainGridded) {
        if (fun(domainCube.first, domainCube.second).containsZero()) {
            domainContainingZero.emplace_back(domainCube);
        }
    }
//    cout << "\n\n";
//    for (const auto &el: domainContainingZero) cout << el.first << " " << el.second << "\n";
}

int main() {
    pair<Interval, Interval> domain = {{-2, 2},
                                       {2,  6}};
    rootFinder(fun, domain, 3);
}