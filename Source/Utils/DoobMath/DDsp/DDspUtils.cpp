/*
  ==============================================================================

    DDspUtils.cpp
    Created: 7 May 2024 3:36:10pm
    Author:  Zubin

  ==============================================================================
*/

#include "DDspUtils.h"

#include "../DGeneralMath/DSqrRootAbsFunctions.h"

namespace DDsp {
    template <typename Type>
    Type DDspUtils<Type>::complexMagnitude(const std::complex<Type>& value) {
        return DMath::DSqrRootAbsFunctions<Type>::sqrt(value.real() * value.real() + value.imag() * value.imag());
    }

    template <typename Type>
    DMath::DVectorComplex<Type> DDspUtils<Type>::complexVectorMagnitude(const DMath::DVectorComplex<std::complex<Type>>& complexVector) {
        DMath::DVectorComplex<Type> magnitudes;

        for (size_t i = 0; i < complexVector.getSize(); ++i) {
            magnitudes.push_back(complexMagnitude(complexVector[i]));
        }

        return magnitudes;
    }

    template <typename Type>
    DMath::DVector<Type> DDspUtils<Type>::normalizeSignal(const DMath::DVector<Type>& signal, Type minRange, Type maxRange) {
        Type minSignal = signal.min();
        Type maxSignal = signal.max();

        Type scale = (maxRange - minRange) / (maxSignal - minSignal);

        DVector<Type> normalizedSignal(signal.getSize());
        for (size_t i = 0; i < signal.getSize(); ++i) {
            normalizedSignal[i] = minRange + (signal[i] - minSignal) * scale;
        }

        return normalizedSignal;
    }

    template <typename Type>
    DMath::DVector<Type> DDspUtils<Type>::trimLeadingZeros(const DMath::DVector<Type>& signal) {
        size_t start = 0;
        while (start < signal.getSize() && signal[start] == 0) {
            ++start;
        }

        return signal.subVector(start);
    }

    template <typename Type>
    DMath::DVector<Type> DDspUtils<Type>::trimTrailingZeros(const DMath::DVector<Type>& signal) {
        size_t end = signal.getSize();
        while (end > 0 && signal[end - 1] == 0) {
            --end;
        }

        return signal.subVector(0, end);
    }

    template <typename Type>
    DMath::DVector<Type> DDspUtils<Type>::trimSignal(const DMath::DVector<Type>& signal, size_t start, size_t end) {
        start = std::min(start, signal.getSize());
        end = std::min(end, signal.getSize());

        return signal.subVector(start, end);
    }

    template <typename Type>
    DMath::DVector<Type> DDspUtils<Type>::zeroPadSignal(const DMath::DVector<Type>& signal, size_t paddedLength) {
        size_t paddingSize = std::max<size_t>(paddedLength - signal.getSize(), 0);

        DMath::DVector<Type> paddedSignal(paddedLength);

        for (size_t i = 0; i < signal.getSize(); ++i) {
            paddedSignal[i] = signal[i];
        }

        for (size_t i = signal.getSize(); i < paddedLength; ++i) {
            paddedSignal[i] = Type(0);
        }

        return paddedSignal;
    }

    template<typename Type>
    DMath::DVector<Type> DDspUtils<Type>::movingAverage(const DMath::DVector<Type>& input, size_t windowSize) {
        DMath::DVector<Type> result(input.getSize());

        for (size_t i = 0; i < input.getSize(); ++i) {
            // compute the average of the values within the window
            size_t start = (i < windowSize / 2) ? 0 : i - windowSize / 2;
            size_t end = (i + windowSize / 2 >= input.getSize()) ? input.getSize() - 1 : i + windowSize / 2;

            Type sum = Type(0);
            for (size_t j = start; j <= end; ++j) {
                sum += input[j];
            }
            result[i] = sum / static_cast<Type>(end - start + 1);
        }

        return result;
    }
}

