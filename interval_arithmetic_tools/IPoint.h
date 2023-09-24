#ifndef _IPOINT_H_
#define _IPOINT_H_

#include "Interval.h"


typedef pair<double, double> Point;
using std::vector;

class IPoint {
public:
    pair<Interval, Interval> area = pair<Interval, Interval>(0, 0);

    IPoint();

    IPoint(const Interval &x, const Interval &y) : area(x, y) {}

    IPoint(Point point, double diff);

    bool operator<=(const IPoint &) const; // set-theory inclusion of this in a

    bool operator<(const IPoint &) const; // set-theory proper-inclusion of this in a

    IPoint operator&&(const IPoint &) const; // intersection

    [[nodiscard]] double width() const;

    [[nodiscard]] vector<IPoint> bisect() const; //bisecting the horizontal interval by half

    vector<IPoint> grid(const unsigned);

};

bool emptyIntersection(const IPoint &,const IPoint &);

ostream& operator<<(ostream& ostream, const IPoint& iPoint);


#endif