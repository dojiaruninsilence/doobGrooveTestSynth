/*
  ==============================================================================

    DWindowFunc.h
    Created: 7 May 2024 3:35:11pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {
    template <typename Type>
    class DWindowFunc {
    public:
        // generate a rectangular window function
        static DMath::DVector<Type> rectangular(size_t size);

        // generate a hamming window function
        static DMath::DVector<Type> hamming(size_t size);

        // generate a hanning window function
        static DMath::DVector<Type> hanning(size_t size);

        // generate a blackman window function
        static DMath::DVector<Type> blackman(size_t size);
    };
}