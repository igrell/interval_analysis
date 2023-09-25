#include "Interval.h"
#include "SiviaNode.h"
#include "list"
#include "EmptyIntersectionException.h"

#define FUN x * x * x * y

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

template<typename T, template<typename> class Fun>
void rootFinder( Fun<T> &fun,
                pair<const Interval &, const Interval &> domain,
                const unsigned GRID_FACTOR, const unsigned TOL) {
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
    for (const auto &domainCube: domainCubes) {
        x.setValue(domainCube.first);
        y.setValue(domainCube.second);
        SiviaNode& f = fun(x,y);
        f.setValue(0);
        try { f.contract(); } catch (EmptyIntersectionException &warning) {} // TODO jak to zawęzić?
        cout << "x" << x << ", y" << y << "\n";
    }
}

int main() {
    pair<Interval, Interval> domain = {{-2, 2},
                                       {2,  6}};
    rootFinder<Interval>(fun, domain, 3, static_cast<unsigned int>(1e-5));
}