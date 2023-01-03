#include "TSet.h"
#include "cmath"

using std::abs;

std::ostream &operator<<(std::ostream &ostream, const TSet &tSet) {
    ostream << "N_l: " << tSet.N_l << "\nN_r: " << tSet.N_r;
    return ostream;
}

std::ostream &operator<<(std::ostream &ostream, const Segment &segment) {
    ostream << "{ (" << segment.first.first << ", " << segment.first.second << "), (" << segment.second.first << ", "
            << segment.second.second << ") }";
    return ostream;
}

Segment &operator+(Segment &segment, double eps) {
    segment.first = {segment.first.first - eps, segment.first.second - eps};
    segment.second = {segment.second.first + eps, segment.second.second + eps};
    return segment;
}

vector<IPoint> TSet::gridLeftEdge(int grid_precision) const {
    return gridEdge(&N_l, grid_precision);
}

vector<IPoint> TSet::gridRightEdge(int grid_precision) const {
    return gridEdge(&N_r, grid_precision);
}

vector<IPoint> TSet::gridUpEdge(int grid_precision) const {
    Segment up_edge = getUpEdge();
    return gridEdge(&up_edge, grid_precision);
}

vector<IPoint> TSet::gridDownEdge(int grid_precision) const {
    Segment down_edge = getDownEdge();
    return gridEdge(&down_edge, grid_precision);
}

// TODO - are absolute values of diffs important ?
vector<IPoint> TSet::gridEdge(const Segment *N_ptr, int grid_precision) {
    vector<IPoint> grid;
    Interval x_interval;
    Interval y_interval;
    double x_diff = (N_ptr->second.first - N_ptr->first.first) / grid_precision;
    double y_diff = (N_ptr->second.second - N_ptr->first.second) / grid_precision;
    for (int i = 0; i < grid_precision; i++) {
        x_interval = Interval(N_ptr->first.first + i * x_diff, N_ptr->first.first + (i + 1) * x_diff);
        y_interval = Interval(N_ptr->first.second + i * y_diff, N_ptr->first.second + (i + 1) * y_diff);
        grid.insert(grid.begin() + i, {x_interval, y_interval});
    }
    return grid;
}

Segment TSet::getUpEdge() const {
    return {N_l.second, N_r.second};
}

Segment TSet::getDownEdge() const {
    return {N_l.first, N_r.first};
}
