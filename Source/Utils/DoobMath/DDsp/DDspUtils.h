/*
  ==============================================================================

    DDspUtils.h
    Created: 7 May 2024 3:36:10pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <complex>

#include "../DGeneralMath/DVectorComplex.h"
#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {
    template <typename Type>
    class DDspUtils {
    public:
        // constructor/destructor
        DDspUtils() {}
        ~DDspUtils() {}

        // function to calculate the magnitude of a complex number
        static Type complexMagnitude(const std::complex<Type>& value);

        // function to convert a vector of complex numbers to their magnitudes
        static DMath::DVectorComplex<Type> complexVectorMagnitude(
            const DMath::DVectorComplex<std::complex<Type>>& spectrum);

        // function to normalize a signal to a specified range
        static DMath::DVector<Type> normalizeSignal(
            const DMath::DVector<Type>& signal, Type minRange, Type maxRange);

        // function to trim leading zeros from a signal
        static DMath::DVector<Type> trimLeadingZeros(const DMath::DVector<Type>& signal);

        // function to trim trailing zeros from a signal
        static DMath::DVector<Type> trimTrailingZeros(const DMath::DVector<Type>& signal);

        // function to trim signal between start and end indices
        static DMath::DVector<Type> trimSignal(
            const DMath::DVector<Type>& signal, size_t start, size_t end);

        // function to zero pad a signal to a specified length
        static DMath::DVector<Type> zeroPadSignal(
            const DMath::DVector<Type>& signal, size_t paddedLength);
        
        // function to compute moving average of a vector
        static DMath::DVector<Type> movingAverage(
            const DMath::DVector<Type>& input, size_t windowSize);
    };

    //template class DDspUtils<float>;
    //template class DDspUtils<double>;
}