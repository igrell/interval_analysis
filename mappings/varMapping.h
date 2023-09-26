#ifndef INTERVAL_ANALYSIS_VARMAPPING_H
#define INTERVAL_ANALYSIS_VARMAPPING_H

#include "tuple"
#include "vector"

using std::tuple, std::size_t, std::vector;

// Abstraction of R^N -> R^N mapping
template<typename T, unsigned long N, typename ...Vars>
class varMapping2 {
protected:
    size_t composition_constant = 0;
    vector<T (*)(Vars...)> oneDimMappings;

public:

    explicit varMapping2(size_t _composition_constant) : composition_constant(_composition_constant) {}

    virtual tuple<T> map() const;

};

class varRossler : public varMapping2<> {

};

// template<typename T>
// class varMapping {
// protected:
//     size_t composition_constant = 0;
//
// public:
//
//     explicit varMapping(int composition_constant) : composition_constant(composition_constant) {}
//
//     template<typename ...Vars>
//     constexpr tuple<T> map(const Vars &...vars) const;
//
//     template<typename ...Vars>
//     tuple<T> compose_map(const Vars &...vars) const {
//         tuple<T> composed_map = map(vars...);
//         for (size_t i = 0 ; i < composed_map) composed_map = map()
//     }
//
// //    pair<T, T> map(const T &x, const T &y) const;
//
// //    pair<T, T> compose_map(const T &x, const T &y) const;
//
// //    IPoint operator()(IPoint &iPoint) const;
//
// };

int main(){

}


#endif //INTERVAL_ANALYSIS_VARMAPPING_H
