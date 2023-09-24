#include "Interval.h"
#include "vector"
#include "list"

using std::cout, std::vector, std::list;

Interval fun(const Interval &x, const Interval &y) { return x * x * x * y; }

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
rootFinder(Interval (*fun)(const Interval &, const Interval &), pair<const Interval &, const Interval &> domain,
           const unsigned GRID_FACTOR) {
    list<pair<Interval, Interval>> domainGridded = gridDomain(domain, GRID_FACTOR);
    for (const auto &pair: domainGridded) std::cout << pair.first << " " << pair.second << "\n";
    auto it = domainGridded.begin();
    while (it != domainGridded.end()) {
        if (!fun(it->first, it->second).containsZero()) {
            it = domainGridded.erase(it);
        } else ++it;
    }


//    cout << "\n";
//    for (const auto &el: domainGridded) cout << el << "\n";

}

int main() {
    pair<Interval, Interval> domain = {{-2, 2},
                                       {2,  6}};
    rootFinder(fun, domain, 3);
}