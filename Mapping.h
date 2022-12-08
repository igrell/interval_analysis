//#include "vector"
//#include "IPoint.h"
//
//using std::vector, std::pair;
//
//// abstraction of R2 -> R2 mapping
//template<class T>
//class Mapping {
//    vector<T> coeffs;
//
//    explicit Mapping(const vector<T> &coeffs) : coeffs(coeffs) {}
//
//public:
//    virtual T map_1(T &x, T &y);
//
//    virtual T map_2(T &x, T &y);
//
//    pair<T, T> map(T &x, T &y);
//
//    pair<T, T> compose_map(const T &x, const T &y, int n);
//};
//
//template<class T>
//pair<T, T> Mapping<T>::map(T &x, T &y) {
//    return {map_1(x, y), map_2(x, y)};
//}
//
//// composes mapping n times
//template<class T>
//pair<T, T> Mapping<T>::compose_map(const T &x, const T &y, const int n) {
//    pair<T, T> temp = map(x, y);
//    for (int i = 1; i < n; ++i) temp = map(temp.first, temp.second);
//    return temp;
//}
