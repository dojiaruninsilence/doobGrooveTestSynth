/*
  ==============================================================================

    DSqrRootAbsFunctions.cpp
    Created: 6 May 2024 8:45:08pm
    Author:  Zubin

  ==============================================================================
*/

#include "DSqrRootAbsFunctions.h"

#include <cmath>

namespace DMath {
    // Square Root
    template <typename Type>
    Type DSqrRootAbsFunctions<Type>::sqrt(Type x) {
        return std::sqrt(x);
    }

    // Absolute Value
    template <typename Type>
    Type DSqrRootAbsFunctions<Type>::abs(Type x) {
        return std::abs(x);
    }
}