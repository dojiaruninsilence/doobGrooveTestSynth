/*
  ==============================================================================

    DRng.h
    Created: 7 May 2024 5:21:31am
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <random>
#include "DVecMatOps.h"

namespace DMath {
    template <typename Type>
    class DRng {
    public:
        // constructor/destuctor
        DRng() : rng(std::random_device{}()) {}
        ~DRng() {}

        // generate a random value between min (inclusive and max(exclusive)
        Type next(Type min, Type max);

        // generate a random value following a gaussian(normal) distribution
        Type nextGaussian(Type mean, Type stddev);

        // return a random element from the given collection
        Type nextElement(const DVector<Type>& collection);

        void setSeed(Type seed);
    private:
        std::mt19937 rng;
    };

    template class DRng<float>;
    template class DRng<int>;
    template class DRng<double>;
    template class DRng<bool>;
}