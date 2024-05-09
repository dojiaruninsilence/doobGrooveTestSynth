/*
  ==============================================================================

    DWindowFunc.cpp
    Created: 7 May 2024 3:35:11pm
    Author:  Zubin

  ==============================================================================
*/

#include "DWindowFunc.h"

#include "../DGeneralMath/DTrig.h"
#include "../DGeneralMath/DMathDefines.h"

namespace DDsp {
    template <typename Type>
    DMath::DVector<Type> DWindowFunc<Type>::rectangular(size_t size) {
        DMath::DVector<Type> window(size);
        for (size_t i = 0; i < size; ++i) {
            window[i] = Type(1);
        }
        return window;
    }

    template <typename Type>
    DMath::DVector<Type> DWindowFunc<Type>::hamming(size_t size) {
        DMath::DVector<Type> window(size);
        const double alpha = 0.54;
        const double beta = 0.46;
        const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);

        for (size_t i = 0; i < size; ++i) {
            window[i] = Type(alpha - beta * DMath::DTrig<Type>::cos(two_pi_over_N_minus_1 * i));
        }

        return window;
    }

    template <typename Type>
    DMath::DVector<Type> DWindowFunc<Type>::hanning(size_t size) {
        DMath::DVector<Type> window(size);
        const double alpha = 0.5;
        const double beta = 0.5;
        const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);

        for (size_t i = 0; i < size; ++i) {
            window[i] = Type(alpha - beta * DMath::DTrig<Type>::cos(two_pi_over_N_minus_1 * i));
        }

        return window;
    }

    template <typename Type>
    DMath::DVector<Type> DWindowFunc<Type>::blackman(size_t size) {
        DMath::DVector<Type> window(size);
        const double alpha = 0.5 * (1.0 - 0.08);
        const double beta = 0.5;
        const double gamma = 0.08;
        const double two_pi_over_N_minus_1 = 2.0 * D_PI / (size - 1);
        const double four_pi_over_N_minus_1 = 4.0 * D_PI / (size - 1);

        for (size_t i = 0; i < size; ++i) {
            window[i] = Type(alpha - beta * DMath::DTrig<Type>::cos(two_pi_over_N_minus_1 * i) + gamma * DMath::DTrig<Type>::cos(four_pi_over_N_minus_1 * i));
        }

        return window;
    }
}