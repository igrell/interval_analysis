#include "IPoint.h"

using std::min, std::max;

IPoint::IPoint() {
//    Interval a = Interval();
//    Interval b = Interval();
    area.first = Interval();
    area.second = Interval();
}

IPoint::IPoint(Point point, double diff) { //initializing area around a given point with a given range 'diff'
    area = {Interval(point.first - diff, point.first + diff), Interval(point.second - diff, point.second + diff)};
}

bool IPoint::operator<=(const IPoint &a) const {
    return (area.first <= a.area.first) and (area.second <= a.area.second);
}

bool IPoint::operator<(const IPoint &a) const {
    return (area.first < a.area.first) and (area.second < a.area.second);
}

IPoint IPoint::operator&&(const IPoint &a) const {
    if ((area.first && a.area.first) == Interval(0)) {
//        cout << "Warning: empty intersection.";
        return {};
    }
    return {area.first && a.area.first, area.second && a.area.second};
}

double IPoint::width() const {
    return max(area.first.width(), area.second.width());
}

pair<IPoint, IPoint> IPoint::bisect() const {
    IPoint part_1(Interval(area.first.get_lo(), area.first.get_lo() + (width() / 2)), area.second);
    IPoint part_2(Interval(area.first.get_lo() + (width() / 2), area.first.get_hi()), area.second);
    return {part_1, part_2};
}

bool emptyIntersection(const IPoint &a, const IPoint &b) {
    IPoint inter = a && b;
    return (inter.area.first == Interval(0) and inter.area.second == Interval(0));
}
