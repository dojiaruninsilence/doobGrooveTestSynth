/*
  ==============================================================================

    DConvolution.h
    Created: 7 May 2024 3:33:58pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {
    template <typename Type>
    class DConvolution {
    public:
        // perform linear convolution between two signals
        static DMath::DVector<Type> linearConvolution(
            const DMath::DVector<Type>& signal,
            const DMath::DVector<Type>& kernel);

        static DMath::DVector<Type> overlapAddConvolution(
            const DMath::DVector<Type>& signal,
            const DMath::DVector<Type>& kernel);
        
        // perform overlap add convolution using fft
        static DMath::DVector<Type> fftConvolution(
            const DMath::DVector<Type>& signal,
            const DMath::DVector<Type>& kernel);
    };
}