/*
  ==============================================================================

    DFft.h
    Created: 7 May 2024 3:34:14pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVectorComplex.h"
#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {
    template <typename Type>
    class DFft {
    public:
        // compute the forward fft of a complex signal
        static DMath::DVectorComplex<std::complex<Type>> forward(
            const DMath::DVectorComplex<std::complex<Type>>& signal);

        // compute the inverse fft of a complex signal
        static DMath::DVectorComplex<std::complex<Type>> inverse(
            const DMath::DVectorComplex<std::complex<Type>>& spectrum);
        
        // compute the forward fft of a real signal
        static DMath::DVectorComplex<std::complex<Type>> forwardReal(const DMath::DVector<Type>& signal);

        // perform complex multiplication in the frequency domain
        static DMath::DVectorComplex<std::complex<Type>> complexMultiply(
            const DMath::DVectorComplex<std::complex<Type>>& spectrum1, 
            const DMath::DVectorComplex<std::complex<Type>>& spectrum2);
    };
}