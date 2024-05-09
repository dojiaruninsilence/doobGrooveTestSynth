/*
  ==============================================================================

    DConvolution.cpp
    Created: 7 May 2024 3:33:58pm
    Author:  Zubin

  ==============================================================================
*/

#include "DConvolution.h"

#include "DFft.h"

#include "../DGeneralMath/DVectorComplex.h"

namespace DDsp {
    template <typename Type>
    DMath::DVector<Type> DConvolution<Type>::linearConvolution(const DMath::DVector<Type>& signal, const DMath::DVector<Type>& kernel) {
        size_t signalSize = signal.getSize();
        size_t kernelSize = kernel.getSize();
        size_t convSize = signalSize + kernelSize - 1;

        DMath::DVector<Type> result(convSize, Type(0));

        for (size_t n = 0; n < convSize; ++n) {
            for (size_t k = 0; k < kernelSize; ++k) {
                if (n >= k && n - k < signalSize) {
                    result[n] += signal[n - k] * kernel[k];
                }
            }
        }

        return result;
    }

    template <typename Type>
    DMath::DVector<Type> DConvolution<Type>::overlapAddConvolution(
        const DMath::DVector<Type>& signal,
        const DMath::DVector<Type>& kernel) {
        size_t signalSize = signal.getSize();
        size_t kernelSize = kernel.getSize();

        // compute the segment size (usually chosen as a power of 2 for fft efficiency)
        size_t segmentSize = 64; // choose an appropriate segment size

        // compute the hop size (overlap)
        size_t hopSize = segmentSize - kernelSize + 1;

        // compute the number of segments needed to cover the entire signal
        size_t numSegments = (signalSize + hopSize - 1) / hopSize;

        // initialize the convolved signal with zeros
        DMath::DVector<Type> convolvedSignal(signalSize + kernelSize - 1, Type(0));

        // iterate over each segment
        for (size_t i = 0; i < numSegments; ++i) {
            // compute the start and end indices for the current segment
            size_t startIdx = i * hopSize;
            size_t endIdx = std::min(startIdx + segmentSize, signalSize);

            // extract the current segment of the signal
            DMath::DVector<Type> segment = signal.subVector(startIdx, endIdx);

            // pad the segment with zeros to match the kernel size
            if (segment.getSize() < kernelSize) {
                segment.resize(kernelSize, Type(0));
            }

            // perform linear convolution on the segment with the kernel
            DMath::DVector<Type> convSegment = linearConvolution(segment, kernel);

            // add the convolution result to the appropriate location in the convolved signal
            size_t convStartIdx = startIdx;
            size_t convEndIdx = std::min(startIdx + kernelSize - 1, convolvedSignal.getSize());
            for (size_t j = 0; j < convSegment.getSize(); ++j) {
                convolvedSignal[convStartIdx + j] += convSegment[j];
            }
        }

        return convolvedSignal;
    }

    template <typename Type>
    DMath::DVector<Type> DConvolution<Type>::fftConvolution(
        const DMath::DVector<Type>& signal,
        const DMath::DVector<Type>& kernel) {
        size_t signalSize = signal.getSize();
        size_t kernelSize = kernel.getSize();

        // compute the size of the fft (next power of two for efficiency)
        size_t fftSize = 1;
        while (fftSize < (signalSize + kernelSize - 1)) {
            fftSize *= 2;
        }

        // pad the signal and kernal with zeros to match the fft size
        DMath::DVector<Type> paddedSignal(fftSize, Type(0));
        DMath::DVector<Type> paddedKernel(fftSize, Type(0));
        paddedSignal.setSubVector(0, signal);
        paddedKernel.setSubVector(0, kernel);

        // compute the fft of the padded signal and kernel
        DMath::DVectorComplex<std::complex<Type>> fftSignal = DFft<Type>::forwardReal(paddedSignal);
        DMath::DVectorComplex<std::complex<Type>> fftKernel = DFft<Type>::forwardReal(paddedKernel);

        // perform element wise complex multiplication
        DMath::DVectorComplex<std::complex<Type>> fftResult = DFft<Type>::complexMultiply(fftSignal, fftKernel);

        // compute the inverse fft of the result
        DMath::DVector<Type> convolvedSignal = DFft<Type>::inverse(fftResult);

        // Extract the valid part of the convolution result
        convolvedSignal.resize(signalSize + kernelSize - 1);

        return convolvedSignal;
    }
}