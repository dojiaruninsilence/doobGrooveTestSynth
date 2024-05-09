/*
  ==============================================================================

    DExpLogFunctions.cpp
    Created: 6 May 2024 8:42:43pm
    Author:  Zubin

  ==============================================================================
*/
#include <cmath>

#include "DExpLogFunctions.h"

namespace DMath {
    template <typename Type>
    Type DExpLogFuntions<Type>::exp(Type x) {
        return std::exp(x);
    }

    template <typename Type>
    Type DExpLogFuntions<Type>::log(Type x) {
        return std::log(x);
    }

    template <typename Type>
    Type DExpLogFuntions<Type>::log10(Type x) {
        return std::log10(x);
    }

    template <typename Type>
    Type DExpLogFuntions<Type>::log2(Type x) {
        return std::log2(x);
    }

    template <typename Type>
    Type DExpLogFuntions<Type>::pow(Type x, Type y) {
        return std::pow(x, y);
    }
}
