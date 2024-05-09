/*
  ==============================================================================

    DInterpolation.cpp
    Created: 7 May 2024 5:18:42am
    Author:  Zubin

  ==============================================================================
*/

#include "DInterpolation.h"

#pragma once

#include "DVecMatOps.h"

namespace DMath {
    template<typename Type>
    Type DInterpolation<Type>::linearInterpolation(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x) {
        // find the two nearest data points in the xValues array
        size_t i = 0;
        while (i < xValues.getSize() && xValues[i] < x) {
            ++i;
        }

        // perform linear interpolation between the two nearest points
        if (i == 0) {
            // extrapolate using the first two points
            return yValues[0] + (yValues[1] - yValues[0]) * (x - xValues[0]) / (xValues[1] - xValues[0]);
        }
        else if (i == xValues.getSize()) {
            // extrapolate using the last two points
            return yValues[i - 2] + (yValues[i - 1] - yValues[i - 2]) * (x - xValues[i - 2]) / (xValues[i - 1] - xValues[i - 2]);
        }
        else {
            // interpolate between two points
            return yValues[i - 1] + (yValues[i] - yValues[i - 1]) * (x - xValues[i - 1]) / (xValues[i] - xValues[i - 1]);
        }
    }

    template<typename Type>
    Type DInterpolation<Type>::cubicInterpolation(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x) {
        // find the index of the nearest data point in the xValues array
        size_t i = 0;
        while (i < xValues.getSize() && xValues[i] < x) {
            ++i;
        }

        // perform cubic interpolation using neighboring points
        return cubicInterpolationHelper(xValues, yValues, x, i);
    }

    template<typename Type>
    Type DInterpolation<Type>::cubicInterpolationHelper(const DVector<Type>& xValues, const DVector<Type>& yValues, Type x, size_t index) {
        // ensure index is within bounds
        if (index < 1 || index >= xValues.getSize() - 2) {
            throw std::out_of_range("Invalid index for cubic interpolation");
        }

        // define neighboring points
        Type x0 = xValues[index - 1];
        Type x1 = xValues[index];
        Type x2 = xValues[index + 1];
        Type x3 = xValues[index + 2];

        Type y0 = yValues[index - 1];
        Type y1 = yValues[index];
        Type y2 = yValues[index + 1];
        Type y3 = yValues[index + 2];

        // compute coefficients for cubic interpolation
        Type t = (x - x1) / (x2 - x1);
        Type t2 = t * t;
        Type t3 = t2 * t;

        Type c0 = y1;
        Type c1 = 0.5 * (y2 - y0);
        Type c2 = y0 - 2.5 * y1 + 2 * y2 - 0.5 * y3;
        Type c3 = 0.5 * (y3 - y0) + 1.5 * (y1 - y2);

        // perform cubic interpolation
        return c0 + c1 * t + c2 * t2 + c3 * t3;
    }
}
