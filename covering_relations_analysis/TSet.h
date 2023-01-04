#ifndef _TSET_H_
#define _TSET_H_

#include "IPoint.h"
#include "vector"

using std::vector;
typedef pair<Point, Point> Segment;

class TSet {
public:
    Segment N_l = pair<Point, Point>(pair<double, double>(0, 0), pair<double, double>(0, 0));
    Segment N_r = pair<Point, Point>(pair<double, double>(0, 0), pair<double, double>(0, 0));

    TSet(Segment &N_l, Segment &N_r) : N_l(N_l), N_r(N_r) {}

    [[nodiscard]]  static vector<IPoint> gridEdge(const Segment *, int grid_precision);

    [[nodiscard]] vector<IPoint> gridLeftEdge(int grid_precision) const;

    [[nodiscard]] vector<IPoint> gridRightEdge(int grid_precision) const;

    [[nodiscard]] vector<IPoint> gridUpEdge(int grid_precision) const;

    [[nodiscard]] vector<IPoint> gridDownEdge(int grid_precision) const;

    [[nodiscard]] Segment getUpEdge() const;

    [[nodiscard]] Segment getDownEdge() const;

};

Segment &operator+(Segment &segment, double eps);

ostream &operator<<(ostream &, const TSet &);

ostream &operator<<(ostream &, const Segment &);

#endif