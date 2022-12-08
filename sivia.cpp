//#include "IPoint.h"
//#include "Rossler.h"
//
//using std::function, std::vector, std::deque;
//
//// F - interval function, Y - solution IPoint for F, x0 - initial IPoint, TOL - tolerance (epsilon)
//vector<deque<IPoint>> sivia(const function<IPoint(IPoint)> &F, const IPoint &Y, const IPoint &x0, double TOL) {
//    deque<IPoint> S; // solution set
//    deque<IPoint> N; // non-solution set
//    deque<IPoint> U; // unidentified set
//    deque<IPoint> T = {x0}; // temporary set of analyzed IPoints
//    while (!T.empty()) {
//        IPoint x = T.front();
//        T.pop_front();
//        if (F(x) < Y) S.push_front(x);
//        else if ((emptyIntersection(F(x), Y))) N.push_front(x);
//        else if (x.width() < TOL) U.push_front(x);
//        else {
//            pair<IPoint, IPoint> x_bisected = x.bisect();
//            T.push_front(x_bisected.first);
//            T.push_front(x_bisected.second);
//        }
//    }
//    return {S, N, U};
//}