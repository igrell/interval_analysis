#include "IPoint.h"

using std::min, std::max;

IPoint::IPoint() {
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
        return {};
    }
    return {area.first && a.area.first, area.second && a.area.second};
}

double IPoint::width() const {
    return max(area.first.width(), area.second.width());
}

vector<IPoint> IPoint::bisect() const {
    double x_diff = area.first.width() / 2;
    double y_diff = area.second.width() / 2;
    IPoint part_1(Interval(area.first.get_lo(), area.first.get_lo() + x_diff),
                  Interval(area.second.get_lo(), area.second.get_lo() + y_diff));
    IPoint part_2(Interval(area.first.get_lo() + x_diff, area.first.get_hi()),
                  Interval(area.second.get_lo(), area.second.get_lo() + y_diff));
    IPoint part_3(Interval(area.first.get_lo(), area.first.get_lo() + x_diff),
                  Interval(area.second.get_lo() + y_diff, area.second.get_hi()));
    IPoint part_4(Interval(area.first.get_lo() + x_diff, area.first.get_hi()),
                  Interval(area.second.get_lo() + y_diff, area.second.get_hi()));
    return {part_1, part_2, part_3, part_4};
}

bool IPoint::containsZero() {
    return area.first.containsZero() and area.second.containsZero();
}

bool emptyIntersection(const IPoint &a, const IPoint &b) {
    IPoint inter = a && b;
    return (inter.area.first == Interval(0) and inter.area.second == Interval(0));
}

ostream &operator<<(ostream &ostream, const IPoint &iPoint) {
    ostream << iPoint.area.first << " , " << iPoint.area.second << "\n";
    return ostream;
}
