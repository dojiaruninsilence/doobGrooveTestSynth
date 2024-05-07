/*
  ==============================================================================

    DRoundingTruncFunctions.cpp
    Created: 6 May 2024 8:48:07pm
    Author:  Zubin

  ==============================================================================
*/

#include "DRoundingTruncFunctions.h"

#include <cmath>

template <typename Type>
Type DRoundingTruncFunctions<Type>::round(Type x) {
    return std::round(x);
}

template <typename Type>
Type DRoundingTruncFunctions<Type>::floor(Type x) {
    return std::floor(x);
}

template <typename Type>
Type DRoundingTruncFunctions<Type>::ceil(Type x) {
    return std::ceil(x);
}

template <typename Type>
Type DRoundingTruncFunctions<Type>::trunc(Type x) {
    int temp = static_cast<int>(x);
    if (x >= 0) {
        return static_cast<Type>(temp);
    }
    else if (temp == x) {
        return x;
    } else {
        return static_cast<Type>(temp + 1);
    }
}