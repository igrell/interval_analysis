#ifndef INTERVAL_ANALYSIS_VARMAPPING_H
#define INTERVAL_ANALYSIS_VARMAPPING_H

#include "tuple"

using std::tuple;

template<typename T>
class varMapping {
protected:
    size_t composition_constant = 0;

public:

    explicit varMapping(int composition_constant) : composition_constant(composition_constant) {}

    template<typename ...Vars>
    constexpr tuple<T> map(const Vars &...vars) const;

    template<typename ...Vars>
    tuple<T> compose_map(const Vars &...vars) const {
        tuple<T> composed_map = map(vars...);
        for (size_t i = 0 ; i < composed_map) composed_map = map()
    }

//    pair<T, T> map(const T &x, const T &y) const;

//    pair<T, T> compose_map(const T &x, const T &y) const;

//    IPoint operator()(IPoint &iPoint) const;

};

int main(){

}


#endif //INTERVAL_ANALYSIS_VARMAPPING_H
