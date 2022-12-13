#include "Rossler.h"
#include "Henon.h"
#include "deque"

using std::deque, std::function, std::ofstream;
#define GRID_PRECISION 100

//line from segment ab, checking condition for point c
// 1 - point left of line, -1 - point right of line, 0 - colinear
template<typename T>
int pointRelativeToLine(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> c) {
    double det = ((b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first));
    return det == 0 ? 0 : (det > 0 ? 1 : -1);
}

bool isIPointLeftOfSegment(const Segment segment, const IPoint &iPoint) {
    int res_1 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_lo()});
    int res_2 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_lo()});
    int res_3 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_hi()});
    int res_4 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_hi()});
    return res_1 == 1 and res_2 == 1 and res_3 == 1 and res_4 == 1;
}

bool isIPointRightOfSegment(const Segment segment, const IPoint &iPoint) {
    int res_1 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_lo()});
    int res_2 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_lo()});
    int res_3 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_hi()});
    int res_4 = pointRelativeToLine(segment.first, segment.second,
                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_hi()});
    return res_1 == -1 and res_2 == -1 and res_3 == -1 and res_4 == -1;
}

template<class T>
bool mappingInside(const TSet &tSet1, const TSet &tSet2, const T &mapping) { //TODO
    bool up = true;
    bool down = true;
    bool up_inverted = true;
    bool down_inverted = true;
    for (IPoint iPoint: tSet1.gridUpEdge(GRID_PRECISION)) {
        if (!isIPointRightOfSegment(tSet2.getUpEdge(), mapping(iPoint))) up = false;
        if (!isIPointLeftOfSegment(tSet2.getDownEdge(), mapping(iPoint))) up_inverted = false;
    }
    for (IPoint iPoint: tSet1.gridDownEdge(GRID_PRECISION)) {
        if (!isIPointLeftOfSegment(tSet2.getDownEdge(), mapping(iPoint))) down = false;
        if (!isIPointRightOfSegment(tSet2.getUpEdge(), mapping(iPoint))) down_inverted = false;
    }
    return (up and down)
           or (up_inverted and down_inverted);
}

template<typename T>
bool edgesOnTheOutside(const TSet &tSet1, const TSet &tSet2, const T &mapping) {
    bool tset1_N_l_rossler_left_of_tset2_N_l = true;
    bool tset1_N_r_rossler_right_of_tSet2_N_r = true;
    //or
    bool tset1_N_l_rossler_right_of_tSet2_N_r = true;
    bool tset1_N_r_rossler_left_of_tSet2_N_l = true;

    for (IPoint iPoint: tSet1.gridLeftEdge(GRID_PRECISION)) {
        if (!isIPointLeftOfSegment(tSet2.N_l, mapping(iPoint))) tset1_N_l_rossler_left_of_tset2_N_l = false;
        if (!isIPointRightOfSegment(tSet2.N_r, mapping(iPoint)))tset1_N_l_rossler_right_of_tSet2_N_r = false;
    }
    for (IPoint iPoint: tSet1.gridRightEdge(GRID_PRECISION)) {
        if (!isIPointRightOfSegment(tSet2.N_r, mapping(iPoint))) tset1_N_r_rossler_right_of_tSet2_N_r = false;
        if (!isIPointLeftOfSegment(tSet2.N_l, mapping(iPoint))) tset1_N_r_rossler_left_of_tSet2_N_l = false;
    }
    return (tset1_N_l_rossler_left_of_tset2_N_l and tset1_N_r_rossler_right_of_tSet2_N_r) or
           (tset1_N_l_rossler_right_of_tSet2_N_r and
            tset1_N_r_rossler_left_of_tSet2_N_l);
}

//testing whether tSet1 => tSet2 with mapping transform
template<class T>
bool isCovering(const TSet &tSet1, const TSet &tSet2, const T &mapping) {
    return edgesOnTheOutside(tSet1, tSet2, mapping)
           and mappingInside(tSet1, tSet2, mapping);
}

void display_TSet_grid(const std::string &label, TSet &tSet) {
    cout << "\n" << label << "' N_l:\n";
    for (const IPoint &iPoint: tSet.gridLeftEdge(GRID_PRECISION)) {
        cout << iPoint.area.first << ", " << iPoint.area.second << "\n";
    }
    cout << "\n" << label << "' N_r:\n";
    for (const IPoint &iPoint: tSet.gridRightEdge(GRID_PRECISION)) {
        cout << iPoint.area.first << ", " << iPoint.area.second << "\n";
    }
    cout << "\n" << label << "' N_u:\n";
    for (const IPoint &iPoint: tSet.gridUpEdge(GRID_PRECISION)) {
        cout << iPoint.area.first << ", " << iPoint.area.second << "\n";
    }
    cout << "\n" << label << "' N_d:\n";
    for (const IPoint &iPoint: tSet.gridDownEdge(GRID_PRECISION)) {
        cout << iPoint.area.first << ", " << iPoint.area.second << "\n";
    }
}

template<class T>
void display_TSet_grid_mapped(const std::string &label, T &mapping, TSet &tSet) {
    cout << "\n" << label << "' N_l:\n";
    for (IPoint iPoint: tSet.gridLeftEdge(GRID_PRECISION)) {
        IPoint res = mapping(iPoint);
        cout << res.area.first << ", " << res.area.second << "\n";
    }
    cout << "\n" << label << "' N_r:\n";
    for (IPoint iPoint: tSet.gridRightEdge(GRID_PRECISION)) {
        IPoint res = mapping(iPoint);
        cout << res.area.first << ", " << res.area.second << "\n";
    }
    cout << "\n" << label << "' N_u:\n";
    for (IPoint iPoint: tSet.gridUpEdge(GRID_PRECISION)) {
        IPoint res = mapping(iPoint);
        cout << res.area.first << ", " << res.area.second << "\n";
    }
    cout << "\n" << label << "' N_d:\n";
    for (IPoint iPoint: tSet.gridDownEdge(GRID_PRECISION)) {
        IPoint res = mapping(iPoint);
        cout << res.area.first << ", " << res.area.second << "\n";
    }
}


vector<deque<IPoint>> sivia(const function<IPoint(IPoint)> &F, const IPoint &Y, const IPoint &x0, double TOL) {
    deque<IPoint> S; // solution set
    deque<IPoint> N; // non-solution set
    deque<IPoint> U; // unidentified set
    deque<IPoint> T = {x0}; // temporary set of analyzed IPoints
    while (!T.empty()) {
        IPoint x = T.front();
        T.pop_front();
        if (F(x) < Y) S.push_front(x);
        else if ((emptyIntersection(F(x), Y))) N.push_front(x);
        else if (x.width() < TOL) U.push_front(x);
        else {
            pair<IPoint, IPoint> x_bisected = x.bisect();
            T.push_front(x_bisected.first);
            T.push_front(x_bisected.second);
        }
    }
    return {S, N, U};
}


int main() {
    //data
    Point a0 = {0.6230, 0.1000};
    Point b0 = {0.6590, 0.0920};
    Point c0 = {0.6600, 0.1320};
    Point d0 = {0.6240, 0.1400};
    Point a1 = {0.7094, 0.0808};
    Point b1 = {0.7670, 0.0680};
    Point c1 = {0.7680, 0.1080};
    Point d1 = {0.7104, 0.1208};
    Point a2 = {0.9250, -0.0070};
    Point b2 = {0.8950, -0.0370};
    Point c2 = {0.9100, -0.0520};
    Point d2 = {0.9400, -0.0220};

    Segment N0_l = {a0, d0};
    Segment N0_r = {b0, c0};
    Segment N1_l = {a1, d1};
    Segment N1_r = {b1, c1};
    Segment N2_l = {b2, c2};
    Segment N2_r = {a2, d2};

//    double epsilon = 0.006; // 5 of 5 for 0.0006, 4 of 5 for 0.0007,  3 of 5 for 0.01, nothing for 0.1
//    N0_l = N0_l + epsilon;
//    N0_r = N0_r + epsilon;
//    N1_l = N1_l + epsilon;
//    N1_r = N1_r + epsilon;
//    N2_l = N2_l + epsilon;
//    N2_r = N2_r + epsilon;

    TSet N0(N0_l, N0_r);
    TSet N1(N1_l, N1_r);
    TSet N2(N2_l, N2_r);

    cout << "N0:\n" << N0 << "\n";
    cout << "N1:\n" << N1 << "\n";
    cout << "N2:\n" << N2 << "\n";

//    Rossler rossler(3.8, 0.1, 0.2, 1.2, 1.9);
    Interval coeff_1 = Interval(38) / Interval(10);
    Interval coeff_2 = Interval(1) / Interval(10);
    Interval coeff_3 = Interval(2) / Interval(10);
    Interval coeff_4 = Interval(12) / Interval(10);
    Interval coeff_5 = Interval(19) / Interval(10);
    Rossler rossler(coeff_1, coeff_2, coeff_3, coeff_4, coeff_5, 3);

//    display_TSet_grid_mapped("N0", rossler, N0);

//    display_TSet_grid_mapped("N1", rossler, N1);

//    display_TSet_grid_mapped("N2", rossler, N2);

    // results
    cout << "N1 => N0 : " << isCovering(N1, N0, rossler) << "\n";
    cout << "N2 => N0 : " << isCovering(N2, N0, rossler) << "\n";
    cout << "N1 => N1 : " << isCovering(N1, N1, rossler) << "\n";
    cout << "N2 => N1 : " << isCovering(N2, N1, rossler) << "\n";
    cout << "N0 => N2 : " << isCovering(N0, N2, rossler) << "\n";

//    Interval coeff_a = Interval(14) / Interval(10);
//    Interval coeff_b = Interval(3) / Interval(10);
//    Henon henon(coeff_a, coeff_b, 7);


    return 0;
}
