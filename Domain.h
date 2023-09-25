#ifndef INTERVAL_ANALYSIS_DOMAIN_H
#define INTERVAL_ANALYSIS_DOMAIN_H
#include "Interval.h"

class Domain {
    static Interval xDomain;
    static Interval yDomain;

public:
    class domain_iterator : public std::iterator<Interval, Interval, const Interval *, Interval> {
        double xDist, yDist;
        double xVal, yVal;

    public:
        domain_iterator(const unsigned GRID_FACTOR) : xDist(xDomain.width() / GRID_FACTOR),
                                                      yDist(yDomain.width() / GRID_FACTOR),
                                                      xVal(xDomain.get_lo()),
                                                      yVal(yDomain.get_lo()) {}

        domain_iterator &operator++() {
            xVal += xDist;
            yVal += yDist;
            return *this;
        }


        domain_iterator operator++(int) {
            domain_iterator res = *this;
            ++(*this);
            return res;
        }

        bool operator==(domain_iterator other) const {
            return (xVal == other.xVal and yVal == other.yVal);
        }

        bool operator!=(domain_iterator other) const {
            return !(*this == other);
        }

        pair<Interval, Interval> operator*() const {
            return {{xVal, xVal + xDist},
                    {yVal, yVal + yDist}};
        }


        pair<Interval, Interval> operator->() const {
            return {{xVal, xVal + xDist},
                    {yVal, yVal + yDist}};
        }

    };
};
#endif //INTERVAL_ANALYSIS_DOMAIN_H
