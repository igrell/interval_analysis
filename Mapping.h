#ifndef _MAPPING_H_
#define _MAPPING_H_ 1

using std::vector, std::pair;

// abstraction of R2 -> R2 mapping
template<typename T>
class Mapping {
protected:
    int composition_constant = 0;

public:

    explicit Mapping(int composition_constant) : composition_constant(composition_constant) {}

    virtual T map_1(const T &x, const T &y) const = 0;

    virtual T map_2(const T &x, const T &y) const = 0;

    pair<T, T> map(const T &x, const T &y) const;

    pair<T, T> compose_map(const T &x, const T &y) const;

    IPoint operator()(IPoint &iPoint) const;

};

template<class T>
pair<T, T> Mapping<T>::map(const T &x, const T &y) const {
    return {map_1(x, y), map_2(x, y)};
}

// composes mapping n times
template<class T>
pair<T, T> Mapping<T>::compose_map(const T &x, const T &y) const {
    pair<T, T> composed_map = map(x, y);
    for (int i = 1; i < composition_constant; ++i) composed_map = map(composed_map.first, composed_map.second);
    return composed_map;
}

//template<class T>
//T Mapping<T>::map_1(const T &x, const T &y) const {
//    return nullptr;
//}

//template<class T>
//T Mapping<T>::map_2(const T &x, const T &y) const {
//    return nullptr;
//}

template<class T>
IPoint Mapping<T>::operator()(IPoint &iPoint) const {
    //     IPoint res = {Interval((iPoint.area.first.get_lo() + iPoint.area.first.get_hi()) / 2),Interval((iPoint.area.second.get_lo() + iPoint.area.second.get_hi()) / 2) };
    pair<T, T> res = compose_map(iPoint.area.first, iPoint.area.second);
    return {res.first, res.second};
}

#endif