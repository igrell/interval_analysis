//#include "../mappings/Rossler.h"
////#include "Henon.h"
//#include "deque"
//#include "iostream"
//#include "../DrawPolicy.h"
//#include "stack"
////#include "fstream"
//
//using std::deque, std::function, std::ofstream, std::string, std::stack;
//#define GRID_PRECISION 100
//#define TOLERANCE 0.00000000000000001
//#define DRAW_POLICY FileDrawPolicy
//
////line from segment ab, checking condition for point c
//// 1 - point left of line, -1 - point right of line, 0 - colinear
//template<typename T>
//int pointRelativeToLine(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> c) {
//    double det = ((b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first));
//    return det == 0 ? 0 : (det > 0 ? 1 : -1);
//}
//
//// 1 - iPoint left of segment, -1 - iPoint right of segment, 0 - in-between
//int isIPointLeftOfSegment(const Segment segment, const IPoint &iPoint) {
//    int res_1 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_lo()});
//    int res_2 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_lo()});
//    int res_3 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_hi()});
//    int res_4 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_hi()});
//    return (res_1 == 1 and res_2 == 1 and res_3 == 1 and res_4 == 1) ? 1 : // if all corners on the left
//           (res_1 != 1 and res_2 != 1 and res_3 != 1 and res_4 != 1) ? -1 : 0; // if all corners NOT on the left
//}
//
//// 1 - iPoint right of segment, -1 - iPoint left of segment, 0 - in-between
//int isIPointRightOfSegment(const Segment segment, const IPoint &iPoint) {
//    int res_1 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_lo()});
//    int res_2 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_lo()});
//    int res_3 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_lo(), iPoint.area.second.get_hi()});
//    int res_4 = pointRelativeToLine(segment.first, segment.second,
//                                    {iPoint.area.first.get_hi(), iPoint.area.second.get_hi()});
//    return (res_1 == -1 and res_2 == -1 and res_3 == -1 and res_4 == -1) ? 1 : // if all corners on the right
//           (res_1 != -1 and res_2 != -1 and res_3 != -1 and res_4 != -1) ? -1 : 0; // if all corners NOT on the right
//}
//
//int isIPointInTheRibbon(const Segment up_edge, const Segment down_edge, const IPoint &iPoint) {
//    int res_1 = isIPointRightOfSegment(up_edge, iPoint);
//    int res_2 = isIPointLeftOfSegment(down_edge, iPoint);
//    return (res_1 == 1 and res_2 == 1) ? 1 : (res_1 == 0 or res_2 == 0) ? 0 : -1;
//}
//
//template<class T>
//bool mappingInside(const TSet &tSet1, const TSet &tSet2, const T &mapping) { //TODO
//    bool onTheLeft = true;
//    bool onTheRight = true;
//    bool inTheRibbon = true; // 'ribbon' refering to the space between N_u and N_d of tSet2
//    stack<IPoint> mapped_iPoints;
//    for (IPoint iPoint: tSet1.gridLeftEdge(GRID_PRECISION)) mapped_iPoints.push(mapping(iPoint));
//    for (IPoint iPoint: tSet1.gridRightEdge(GRID_PRECISION)) mapped_iPoints.push(mapping(iPoint));
//    for (IPoint iPoint: tSet1.gridUpEdge(GRID_PRECISION)) mapped_iPoints.push(mapping(iPoint));
//    for (IPoint iPoint: tSet1.gridDownEdge(GRID_PRECISION)) mapped_iPoints.push(mapping(iPoint));
//    IPoint iPoint;
//    int left_check;
//    int right_check;
//    int ribbon_check;
//    vector<IPoint> iPoint_bisected;
//    while (!mapped_iPoints.empty()) {
//        iPoint = mapped_iPoints.top();
//        mapped_iPoints.pop();
//        left_check = isIPointLeftOfSegment(tSet2.N_l, iPoint);
//        right_check = isIPointRightOfSegment(tSet2.N_r, iPoint);
//        ribbon_check = isIPointInTheRibbon(tSet2.getUpEdge(), tSet2.getDownEdge(), iPoint);
//        if (onTheLeft and left_check == -1)
//            onTheLeft = false; // found at least one iPoint on the right
//        if (onTheRight and right_check == -1)
//            onTheRight = false; // found at least one iPoint on the left
//        if (inTheRibbon and ribbon_check == -1)
//            inTheRibbon = false; // found at least one iPoint on the left
//        if (left_check == 0 or right_check == 0 or ribbon_check == 0) { // ambiguities
//            iPoint_bisected = iPoint.bisect();
//            cout << iPoint;
//            for (const auto &bisection_el : iPoint_bisected) {
//                if (bisection_el.width() < TOLERANCE) return false;
//                cout << bisection_el;
//                mapped_iPoints.push(bisection_el);
//            }
//            cout << "\n";
//        }
//    }
//    return onTheLeft or onTheRight or inTheRibbon;
//}
//
//template<typename T>
//bool edgesOnTheOutside(const TSet &tSet1, const TSet &tSet2, const T &mapping) {
//    bool tset1_N_l_rossler_left_of_tset2_N_l = true;
//    bool tset1_N_r_rossler_right_of_tSet2_N_r = true;
//    //or
//    bool tset1_N_l_rossler_right_of_tSet2_N_r = true;
//    bool tset1_N_r_rossler_left_of_tSet2_N_l = true;
//
//    for (IPoint iPoint: tSet1.gridLeftEdge(GRID_PRECISION)) {
//        if (not tset1_N_l_rossler_left_of_tset2_N_l and not tset1_N_l_rossler_right_of_tSet2_N_r)
//            break; // nothing left to check
//        if (tset1_N_l_rossler_left_of_tset2_N_l and
//            isIPointLeftOfSegment(tSet2.N_l, mapping(iPoint)) != 1)
//            tset1_N_l_rossler_left_of_tset2_N_l = false;
//        if (tset1_N_l_rossler_right_of_tSet2_N_r and
//            isIPointRightOfSegment(tSet2.N_r, mapping(iPoint)) != 1)
//            tset1_N_l_rossler_right_of_tSet2_N_r = false;
//    }
//    for (IPoint iPoint: tSet1.gridRightEdge(GRID_PRECISION)) {
//        if (not tset1_N_r_rossler_right_of_tSet2_N_r and not tset1_N_r_rossler_left_of_tSet2_N_l)
//            break; // nothing left to check
//        if (tset1_N_r_rossler_right_of_tSet2_N_r and
//            isIPointRightOfSegment(tSet2.N_r, mapping(iPoint)) != 1)
//            tset1_N_r_rossler_right_of_tSet2_N_r = false;
//        if (tset1_N_r_rossler_left_of_tSet2_N_l and
//            isIPointLeftOfSegment(tSet2.N_l, mapping(iPoint)) != 1)
//            tset1_N_r_rossler_left_of_tSet2_N_l = false;
//    }
//    return (tset1_N_l_rossler_left_of_tset2_N_l and tset1_N_r_rossler_right_of_tSet2_N_r) or
//           (tset1_N_l_rossler_right_of_tSet2_N_r and
//            tset1_N_r_rossler_left_of_tSet2_N_l);
//}
//
////testing whether tSet1 => tSet2 with mapping transform
//template<class T>
//bool isCovering(const TSet &tSet1, const TSet &tSet2, const T &mapping) {
//    return edgesOnTheOutside(tSet1, tSet2, mapping)
//           and mappingInside(tSet1, tSet2, mapping)
//           ;
//}
//
//template<class DrawPolicy>
//void display_TSet_grid(const std::string &label, TSet &tSet) {
//    cout << "\n" << label << "' N_l:\n";
//    for (const IPoint &iPoint: tSet.gridLeftEdge(GRID_PRECISION)) {
//        DrawPolicy::drawIPoint(iPoint);
//    }
//    cout << "\n" << label << "' N_r:\n";
//    for (const IPoint &iPoint: tSet.gridRightEdge(GRID_PRECISION)) {
//        DrawPolicy::drawIPoint(iPoint);
//    }
////    cout << "\n" << label << "' N_u:\n";
////    for (const IPoint &iPoint: tSet.gridUpEdge(GRID_PRECISION)) {
////        DrawPolicy::drawIPoint(iPoint);
////    }
////    cout << "\n" << label << "' N_d:\n";
////    for (const IPoint &iPoint: tSet.gridDownEdge(GRID_PRECISION)) {
////        DrawPolicy::drawIPoint(iPoint);
////    }
//}
//
//template<class DrawPolicy, class T>
//void display_TSet_grid_mapped(const std::string &label, T &mapping, TSet &tSet) {
//    cout << "\n" << label << "' N_l:\n";
//    for (IPoint iPoint: tSet.gridLeftEdge(GRID_PRECISION)) {
//        IPoint res = mapping(iPoint);
//        DrawPolicy::drawIPoint(res);
////        cout << res;
//    }
//    cout << "\n" << label << "' N_r:\n";
//    for (IPoint iPoint: tSet.gridRightEdge(GRID_PRECISION)) {
//        IPoint res = mapping(iPoint);
//        DrawPolicy::drawIPoint(res);
////        cout << res;
//    }
////    cout << "\n" << label << "' N_u:\n";
////    for (IPoint iPoint: tSet.gridUpEdge(GRID_PRECISION)) {
////        IPoint res = mapping(iPoint);
////        DrawPolicy::drawIPoint(res);
////        cout << res;
////    }
////    cout << "\n" << label << "' N_d:\n";
////    for (IPoint iPoint: tSet.gridDownEdge(GRID_PRECISION)) {
////        IPoint res = mapping(iPoint);
////        DrawPolicy::drawIPoint(res);
////        cout << res;
////    }
//}
//
//
////vector<deque<IPoint>> sivia(const function<IPoint(IPoint)> &F, const IPoint &Y, const IPoint &x0, double TOL) {
////    deque<IPoint> S; // solution set
////    deque<IPoint> N; // non-solution set
////    deque<IPoint> U; // unidentified set
////    deque<IPoint> T = {x0}; // temporary set of analyzed IPoints
////    while (!T.empty()) {
////        IPoint x = T.front();
////        T.pop_front();
////        if (F(x) < Y) S.push_front(x);
////        else if ((emptyIntersection(F(x), Y))) N.push_front(x);
////        else if (x.width() < TOL) U.push_front(x);
////        else {
////            pair<IPoint, IPoint> x_bisected = x.bisect();
////            T.push_front(x_bisected.first);
////            T.push_front(x_bisected.second);
////        }
////    }
////    return {S, N, U};
////}
//
//template<class DrawPolicy>
//void emptyFile() {
//    DrawPolicy::emptyFile();
//}
//
//int main() {
//
//    //data
//    Point a0 = {0.6230, 0.1000};
//    Point b0 = {0.6590, 0.0920};
//    Point c0 = {0.6600, 0.1320};
//    Point d0 = {0.6240, 0.1400};
//    Point a1 = {0.7094, 0.0808};
//    Point b1 = {0.7670, 0.0680};
//    Point c1 = {0.7680, 0.1080};
//    Point d1 = {0.7104, 0.1208};
//    Point a2 = {0.9250, -0.0070};
//    Point b2 = {0.8950, -0.0370};
//    Point c2 = {0.9100, -0.0520};
//    Point d2 = {0.9400, -0.0220};
//
//    Segment N0_l = {a0, d0};
//    Segment N0_r = {b0, c0};
//    Segment N1_l = {a1, d1};
//    Segment N1_r = {b1, c1};
//    Segment N2_l = {b2, c2};
//    Segment N2_r = {a2, d2};
//
////    double epsilon = 0.006; // 5 of 5 for 0.0006, 4 of 5 for 0.0007,  3 of 5 for 0.01, nothing for 0.1
////    N0_l = N0_l + epsilon;
////    N0_r = N0_r + epsilon;
////    N1_l = N1_l + epsilon;
////    N1_r = N1_r + epsilon;
////    N2_l = N2_l + epsilon;
////    N2_r = N2_r + epsilon;
//
//    TSet N0(N0_l, N0_r);
//    TSet N1(N1_l, N1_r);
//    TSet N2(N2_l, N2_r);
//
//    cout << "N0:\n" << N0 << "\n";
//    cout << "N1:\n" << N1 << "\n";
//    cout << "N2:\n" << N2 << "\n";
//
////    Rossler rossler(3.8, 0.1, 0.2, 1.2, 1.9);
//    Interval coeff_1 = Interval(38) / Interval(10);
//    Interval coeff_2 = Interval(1) / Interval(10);
//    Interval coeff_3 = Interval(2) / Interval(10);
//    Interval coeff_4 = Interval(12) / Interval(10);
//    Interval coeff_5 = Interval(19) / Interval(10);
//    Rossler rossler(coeff_1, coeff_2, coeff_3, coeff_4, coeff_5, 3);
//
//    emptyFile<DRAW_POLICY>();
//
////    display_TSet_grid<DRAW_POLICY>("N0", N0);
//
////    display_TSet_grid<DRAW_POLICY>("N1", N1);
//
////    display_TSet_grid<DRAW_POLICY>("N2", N2);
//
//    display_TSet_grid_mapped<DRAW_POLICY>("N0", rossler, N0);
//
//    display_TSet_grid_mapped<DRAW_POLICY>("N1", rossler, N1);
//
//    display_TSet_grid_mapped<DRAW_POLICY>("N2", rossler, N2);
//
//    // results
////    cout << "N1 => N0 : " << isCovering(N1, N0, rossler) << "\n";
////    cout << "N2 => N0 : " << isCovering(N2, N0, rossler) << "\n";
////    cout << "N1 => N1 : " << isCovering(N1, N1, rossler) << "\n";
////    cout << "N2 => N1 : " << isCovering(N2, N1, rossler) << "\n";
////    cout << "N0 => N2 : " << isCovering(N0, N2, rossler) << "\n";
//    return 0;
//}
//
////int main() {
////    Segment Nl({0, 0}, {0, 1});
////    Segment Nr({1, 0}, {1, 1});
////    TSet N(Nl, Nr);
////    Interval x(0, 1);
////    Interval y(0, 1);
////    IPoint iPoint(x, y);
////    Segment up({-2, 2}, {2, 2});
////    Segment down({-2, 0.9}, {2, 0.9});
////    cout << isIPointInTheRibbon(up, down, iPoint);
////}