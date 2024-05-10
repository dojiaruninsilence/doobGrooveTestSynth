/*
  ==============================================================================

    DSpectralAnalysis.cpp
    Created: 7 May 2024 3:35:43pm
    Author:  Zubin

  ==============================================================================
*/

#include "DSpectralAnalysis.h"

namespace DDsp {
    template <typename Type>
    DSpectralAnalysis<Type>::DSpectralAnalysis() 
        : fftSize(1024), frameSize(512), hopSize(256), samplingRate(44100), windowFunctionType(0) {
        // Initialize FFT object
        fft = DFft<Type>();

        // Default values for FFT window and other parameters
        fftWindow.clear();
    }

    template <typename Type>
    DSpectralAnalysis<Type>::~DSpectralAnalysis() {
        // destructor implementation
    }

    template <typename Type>
    DMath::DVector<Type> DSpectralAnalysis<Type>::analyze(const DMath::DVector<Type>& inputSignal) {
        // validate input signal
        validateInputSignal(inputSignal);

        // preprocess input signal (normalize and zero-pad)
        DMath::DVector<Type> processedSignal = inputSignal;
        preprocessSignal(processedSignal);

        // split input signal into frames
        DMath::DVector<DMath::DVector<Type>> frames = splitIntoFrames(processedSignal);

        // initialize vector to store resulting spectral data
        DMath::DVector<DMath::DVector<Type>> spectralData(frames.getSize());

        // process each frame
        for (size_t i = 0; i < frames.getSize(); ++i) {
            // apply window function
            applyWindowFunction(frames[i]);

            // compute FFT
            DMath::DVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

            // compute magnitude spectrum
            DMath::DVector<Type> magnitude = computeMagnitude(spectrum);

            // store magnitude spectrum
            spectralData[i] = magnitude;
        }

        // optionally, you can do further processing on spectralData
        // for example, you can apply spectral smoothing, peak detection, etc.

        return spectralData; // return the resulting spectral data
    }

    template <typename Type>
    DMath::DVector<Type> DSpectralAnalysis<Type>::computeMagnitude(const DMath::DVectorComplex<std::complex<Type>>& spectrum) {
        // initialize vector to store magnitudes
        DMath::DVector<Type> magnitudes(spectrum.getSize());

        // compute magnitude for each complex value in the spectrum
        for (size_t i = 0; i < spectrum.getSize(); ++i) {
            magnitudes[i] = DDspUtils<Type>::complexMagnitude(spectrum[i]);
        }

        return magnitudes;
    }

    template <typename Type>
    DMath::DVector<DMath::DVector<Type>> DSpectralAnalysis<Type>::generateSpectrogram(const DMath::DVector<Type>& inputSignal, size_t frameSize, size_t hopSize) {
        // validate input signal
        validateInputSignal(inputSignal);

        // preprocess input signal (normalize and zero-pad)
        DMath::DVector<Type> processedSignal = inputSignal;
        preprocessSignal(processedSignal);

        // split input signal into frames
        DMath::DVector<DMath::DVector<Type>> frames = splitIntoFrames(processedSignal);

        // initialize vector of vectors to store spectrogram
        DMath::DVector<DMath::DVector<Type>> spectrogram(frames.getSize());

        // process each frame
        for (size_t i = 0; i < frames.getSize(); ++i) {
            // apply window function
            applyWindowFunction(frames[i]);

            // compute FFT
            DMath::DVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

            // compute magnitude spectrum
            DMath::DVector<Type> magnitude = computeMagnitude(spectrum);

            // store magnitude spectrum in spectrogram
            spectrogram[i] = magnitude;
        }

        return spectrogram;
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::plotFrequencySpectrum(const DMath::DVector<Type>& inputSignal) {
        // Validate input signal
        validateInputSignal(inputSignal);

        // Apply window function to the entire signal
        DMath::DVector<Type> windowedSignal = inputSignal;
        applyWindowFunction(windowedSignal);

        // Compute FFT
        DMath::DVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(windowedSignal);

        // Compute magnitude spectrum
        DMath::DVector<Type> magnitude = computeMagnitude(spectrum);

        // Plot the magnitude spectrum using your preferred plotting library
        // Example: You can print the magnitude values to the console for now
        for (size_t i = 0; i < magnitude.getSize(); ++i) {
            std::cout << "Frequency bin " << i << ": " << magnitude[i] << std::endl;
        }

        // After obtaining the magnitude spectrum, you can use your preferred plotting library
        // to visualize it (e.g., Matplotlib in Python, or plotting libraries in C++)
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::initializeFFT(size_t fftSize) {
        this->fftSize = fftSize;

        // initialize FFT object
        fft = DFft<Type>();

        // generate FFT window function
        generateWindow(fftSize);
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::applyWindowFunction(DMath::DVector<Type>& signal) {
        // check if the signal size matches the window size
        if (signal.getSize() != fftSize) {
            throw std::invalid_argument("Signal size does not match FFT window size.");
        }

        // apply the window function to the signal
        for (size_t i = 0; i < fftSize; ++i) {
            signal[i] *= fftWindow[i];
        }
    }

    template <typename Type>
    DMath::DVector<DMath::DVector<Type>> DSpectralAnalysis<Type>::splitIntoFrames(const DMath::DVector<Type>& inputSignal) {
        // Check if input signal size is less than or equal to frame size
        if (inputSignal.getSize() <= frameSize) {
            throw std::invalid_argument("Input signal size is less than or equal to frame size.");
        }

        // Calculate number of frames
        size_t numFrames = 1 + (inputSignal.getSize() - frameSize) / hopSize;

        // Initialize vector of vectors to store frames
        DMath::DVector<DMath::DVector<Type>> frames(numFrames);

        // Populate frames
        for (size_t i = 0; i < numFrames; ++i) {
            size_t startIdx = i * hopSize;
            size_t endIdx = startIdx + frameSize;

            // Extract frame from input signal
            frames[i] = inputSignal.subVector(startIdx, endIdx);
        }

        return frames;
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::validateInputSignal(const DMath::DVector<Type>& inputSignal) {
        // check if the input signal is empty
        if (inputSignal.getSize() == 0) {
            throw std::invalid_argument("Input signal is empty.");
        }

        // check if the size of the input signal is less than or equal to the FFT size
        if (inputSignal.getSize() <= fftSize) {
            throw std::invalid_argument("Input signal size is less than or equal to FFT size.");
        }
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::preprocessSignal(DMath::DVector<Type>& inputSignal) {
        // normalize the input signal to the range [0, 1]
        inputSignal = DDsp::DDspUtils<Type>::normalizeSignal(inputSignal, Type(0), Type(1));

        // zero-pad the input signal to match the FFT window size
        size_t originalSize = inputSignal.getSize();
        if (originalSize < fftSize) {
            inputSignal.resize(fftSize, Type(0));
        }
        else if (originalSize > fftSize) {
            // trim the input signal to match the FFT window size
            inputSignal.resize(fftSize);
        }
    }

    //------------------need to add a switch case for multiple window function types--------------
    template <typename Type>
    void DSpectralAnalysis<Type>::generateWindow(size_t size) {
        // generate the FFT window function
        fftWindow = DWindowFunc<Type>::hamming(size);
    }

    template <typename Type>
    void DSpectralAnalysis<Type>::processSpectralData(DMath::DVector<DMath::DVectorComplex<std::complex<Type>>>& frames) {
        // perform spectral processing on each frame
        for (size_t i = 0; i < frames.getSize(); ++i) {
            // apply FFT on the frame
            DMath::DVectorComplex<std::complex<Type>> spectrum = fft.forwardReal(frames[i]);

            // you can add additional processing steps here based on your requirements
            // example: Apply filtering, feature extraction, etc.

            // compute magnitude spectrum from the complex spectrum
            DMath::DVector<Type> magnitude = computeMagnitude(spectrum);

            // example additional processing: Smoothing (moving average)
            // you may replace this with a more sophisticated filter
            magnitude = DDspUtils<Type>::movingAverage(magnitude, 5); // smooth with a window size of 5

            // store the processed magnitude spectrum or do further processing as needed
            frames[i] = magnitude;
        }
    }
}