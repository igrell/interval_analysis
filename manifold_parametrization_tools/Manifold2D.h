#ifndef INTERVAL_ANALYSIS_MANIFOLD2D_H
#define INTERVAL_ANALYSIS_MANIFOLD2D_H

#include "Mapping.h"
#include "Autodiff.h"

template<typename T>
class Manifold2D {
    Mapping<T> mapping = nullptr;
    FunJet<T> diffMapping = nullptr;
    size_t GRID_CONST = 0;
    size_t EPS = 0;

    Manifold2D(const Mapping<T> &_mapping) : mapping(_mapping), diffMapping(autodiff(mapping)) {}

    void set_grid(const size_t &_GRID_CONST) { GRID_CONST = _GRID_CONST; }

    void set_eps(const size_t &_EPS) { EPS = _EPS; }

    void findInvariantManifold(const size_t &_GRID_CONST, const size_t &_EPS) {
        set_grid(_GRID_CONST);
        set_eps(_EPS);

        // ALGORITHM
    }
};


#endif //INTERVAL_ANALYSIS_MANIFOLD2D_H
