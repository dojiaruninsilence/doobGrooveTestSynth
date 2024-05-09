/*
  ==============================================================================

    DFft.cpp
    Created: 7 May 2024 3:34:14pm
    Author:  Zubin

  ==============================================================================
*/

#include "DFft.h"

#include "../DGeneralMath/DMathDefines.h"

#include <cmath>

namespace DDsp {
    template <typename Type>
    DMath::DVectorComplex<std::complex<Type>> DFft<Type>::forward(
        const DMath::DVectorComplex<std::complex<Type>>& signal) {
        size_t N = signal.getSize();

        // base case of recursion: if the size of the signal is 1, return it as is 
        if (N == 1) {
            return signal;
        }

        DMath::DVectorComplex<std::complex<Type>> even(N / 2), odd(N / 2);
        for (size_t i = 0; i < N / 2; ++i) {
            even[i] = signal[2 * i];
            odd[i] = signal[2 * i + 1];
        }

        // recursive fft computation for even and odd parts
        DMath::DVectorComplex<std::complex<Type>> even_fft = forward(even);
        DMath::DVectorComplex<std::complex<Type>> odd_fft = forward(odd);

        // combine the results
        DMath::DVectorComplex<std::complex<Type>> result(N);
        for (size_t k = 0; k < N / 2; ++k) {
            Type theta = -2.0 * D_PI * k / N;
            std::complex<Type> twiddle = std::polar((Type)1.0, theta) * odd_fft[k];
            result[k] = even_fft[k] + twiddle;
            result[k + N / 2] = even_fft[k] - twiddle;
        }

        return result;
    }
    
    template <typename Type>
    DMath::DVectorComplex<std::complex<Type>> DFft<Type>::inverse(
        const DMath::DVectorComplex<std::complex<Type>>& spectrum) {
        // get the size of the spectrum
        size_t N = spectrum.getSize();

        // conjugate the spectrum
        DMath::DVectorComplex<std::complex<Type>> conjugat_spectrum = spectrum;
        for (size_t i = 0; i < N; ++i) {
            conjugat_spectrum[i] = std::conj(spectrum[i]);
        }

        // apply forward fft on the conjugated spectrum
        DMath::DVectorComplex<std::complex<Type>> time_domain_signal = forward(conjugat_spectrum);

        // conjugate the time domain signal and scale
        for (size_t i = 0; i < N; ++i) {
            time_domain_signal[i] = std::conj(time_domain_signal[i]) / static_cast<Type>(N);
        }

        return time_domain_signal;
    }

    template <typename Type>
    DMath::DVectorComplex<std::complex<Type>> DFft<Type>::forwardReal(
        const DMath::DVector<Type>& signal) {
        size_t N = signal.getSize();

        DMath::DVectorComplex<std::complex<Type>> spectrum(N);

        DMath::DVectorComplex<std::complex<Type>> complexSignal(N);
        for (size_t i = 0; i < N; ++i) {
            complexSignal[i] = std::complex<Type>(signal[i], 0);
        }

        spectrum = forward(complexSignal);

        return spectrum;
    }

    template <typename Type>
    DMath::DVectorComplex<std::complex<Type>> DFft<Type>::complexMultiply(
        const DMath::DVectorComplex<std::complex<Type>>& spectrum1,
        const DMath::DVectorComplex<std::complex<Type>>& spectrum2) {
        size_t N = spectrum1.getSize();

        DMath::DVectorComplex<std::complex<Type>> result(N);
        for (size_t i = 0; i < N; ++i) {
            result[i] = spectrum1[i] * spectrum2[i];
        }

        return result;
    }
}