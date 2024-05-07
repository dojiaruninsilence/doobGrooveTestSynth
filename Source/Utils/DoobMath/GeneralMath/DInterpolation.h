/*
  ==============================================================================

    DInterpolation.h
    Created: 7 May 2024 5:18:42am
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "DVecMatOps.h"

template <typename Type>
class DInterpolation {
public:
    DInterpolation() {}
    ~DInterpolation() {}

    // linear interpolation
    static Type linearInterpolation(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x);

    // cubic interoplation
    static Type cubicInterpolation(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x);
private:
    // helper funtions for cubic interpolation
    static Type cubicInterpolationHelper(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x, size_t index);
};