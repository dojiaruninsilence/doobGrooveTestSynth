/*
  ==============================================================================

    DTrig.cpp
    Created: 6 May 2024 8:41:48pm
    Author:  Zubin

  ==============================================================================
*/

#include "DTrig.h"

#include <cmath>

template <typename Type>
Type DTrig<Type>::degreeToRadians(Type angleDegrees) {
    return angleDegrees * static_cast<Type>(D_PI) / static_cast<Type>(180.0);
}

template <typename Type>
Type DTrig<Type>::radianToDegrees(Type angleRadians) {
    return angleRadians * static_cast<Type>(180.0) / static_cast<Type>(D_PI);
}

template <typename Type>
Type DTrig<Type>::sin(Type angleRadians) {
    return std::sin(angleRadians);
}

template <typename Type>
Type DTrig<Type>::sinDegrees(Type angleDegrees) {
    Type angleRadians = degreeToRadians(angleDegrees);
    return std::sin(angleRadians);
}

template <typename Type>
Type DTrig<Type>::cos(Type angleRadians) {
    return std::cos(angleRadians);
}

template <typename Type>
Type DTrig<Type>::cosDegrees(Type angleDegrees) {
    Type angleRadians = degreeToRadians(angleDegrees);
    return std::cos(angleRadians);
}

template <typename Type>
Type DTrig<Type>::tan(Type angleRadians) {
    return std::tan(angleRadians);
}

template <typename Type>
Type DTrig<Type>::tanDegrees(Type angleDegrees) {
    Type angleRadians = degreeToRadians(angleDegrees);
    return std::tan(angleRadians);
}