/*
  ==============================================================================

    DIirFilt.h
    Created: 7 May 2024 3:33:28pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {
    // enum to define filter types
    enum class FilterType {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        BAND_STOP
    };

    template <typename Type>
    class DIirFilt {
    public:
        // constructor
        DIirFilt(FilterType type, Type cutoffFreq, Type resonance);

        // destructor
        ~DIirFilt() {}

        // method to set filter coefficients based on type, cutoff frequency, and resonance
        void setFilterCoefficients(FilterType type, Type cutoffFreq, Type resonance);

        // methos to process a single sample through the filter
        Type processSample(Type input);

        // method to process a block of samples through the filter
        DMath::DVector<Type> processBlock(const DMath::DVector<Type>& input);

        //------------------------------------------------------------------------------------------------------
        // method to analyze the filter's frequency response -- come back to when we start workin on all this
        void analyzeFreqResponse();
    private:
        // Private functions for filter calculation
        Type calculateOutputSample(Type input);
        void updateFilterState(Type input);

        // coefficient calculation methods
        void calculateCoefficients(FilterType type, Type cutoffFreq, Type resonance);

        // lowpass coefficient calculation method
        DMath::DVector<Type> calculateLowPassCoefficients(Type cutoffFreq, Type resonance);

        // highpass coefficient calculation method
        DMath::DVector<Type> calculateHighPassCoefficients(Type cutoffFreq, Type resonance);

        // bandpass coefficient calculation method
        DMath::DVector<Type> calculateBandPassCoefficients(Type cutoffFreq, Type resonance);

        // bandstop coefficient calculation method
        DMath::DVector<Type> calculateBandStopCoefficients(Type cutoffFreq, Type resonance);

        // denominator coefficient calculattion method
        DMath::DVector<Type> calculateDenominatorCoefficients(Type cutoffFreq, Type resonance);

        // filter coefficients
        DMath::DVector<Type> bCoefficients;
        DMath::DVector<Type> aCoefficients;

        // state variables for the filter
        DMath::DVector<Type> xHistory; // input
        DMath::DVector<Type> yHistory; // output

        // filter type
        FilterType filterType;
    };
}