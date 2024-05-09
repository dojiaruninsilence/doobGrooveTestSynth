/*
  ==============================================================================

    DStats.h
    Created: 6 May 2024 8:55:37pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "DVecMatOps.h"

namespace DMath {
    template <typename Type>
    class DStats {
    public:
        // function to calculate the mean of a vector
        static Type mean(const DVector<Type>& vector);

        // function to calculate the standard deviation of a vector
        static Type standardDeviation(const DVector<Type>& vector);

        // function to calculate the variance of a vector
        static Type variance(const DVector<Type>& vector);

        // function to calculate the median of a vector
        static Type median(const DVector<Type>& vector);

        // function to calculate the modes of a verctor
        static DVector<Type> mode(const DVector<Type>& vector);

        // function to calculate the range of a vector
        static Type range(const DVector<Type>& vector);
    };
}