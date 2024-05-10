/*
  ==============================================================================

    DSpectralAnalysis.h
    Created: 7 May 2024 3:35:43pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVecMatOps.h"
#include "../DGeneralMath/DVectorComplex.h"
#include "DFft.h"
#include "DWindowFunc.h"
#include "DDspUtils.h"

namespace DDsp {

    template <typename Type>
    class DSpectralAnalysis {
    public:
        // constructor/destructor
        DSpectralAnalysis();
        ~DSpectralAnalysis();

        // function to perform spectral analysis on input signal
        DMath::DVector<Type> analyze(const DMath::DVector<Type>& inputSignal);

        // Function to compute the magnitude spectrum from the complex spectrum
        DMath::DVector<Type> computeMagnitude(const DMath::DVectorComplex<std::complex<Type>>& spectrum);

        // Function to generate a spectrogram from the input signal
        // This function returns a 2D array representing the spectrogram
        DMath::DVector<DMath::DVector<Type>> generateSpectrogram(const DMath::DVector<Type>& inputSignal, size_t frameSize, size_t hopSize);

        // Function to plot the frequency spectrum of the input signal
        void plotFrequencySpectrum(const DMath::DVector<Type>& inputSignal);

    private:
        int fftSize; // size of the fft window
        DMath::DVector<Type> fftWindow; // fft window function
        DFft<Type> fft; // fft object for computing fft
        DWindowFunc<Type> windowFunc; // window function object
        size_t frameSize; // size of each analysis frame
        size_t hopSize;   // hop size between consecutive frames
        double samplingRate; // sampling rate of the input signal
        int windowFunctionType; // type of window function (e.g., hamming, hann, etc.)

        // private helper functions
        void initializeFFT(size_t fftSize);
        void applyWindowFunction(DMath::DVector<Type>& signal);

        DMath::DVector<DMath::DVector<Type>> splitIntoFrames(const DMath::DVector<Type>& inputSignal);
        void validateInputSignal(const DMath::DVector<Type>& inputSignal);
        void preprocessSignal(DMath::DVector<Type>& inputSignal);
        void generateWindow(size_t size);
        void processSpectralData(DMath::DVector<DMath::DVectorComplex<std::complex<Type>>>& frames);
    };
}