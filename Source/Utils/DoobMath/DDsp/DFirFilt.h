/*
  ==============================================================================

    DFirFilt.h
    Created: 7 May 2024 3:32:44pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "../DGeneralMath/DVecMatOps.h"

namespace DDsp {

    enum class FilterType {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        BAND_STOP
    };

    enum class FilterDesignMethod {
        WINDOWING,
        FREQUENCY_SAMPLING,
        PARKS_MCCLELLAN
    };

    template <typename Type>
    class DFirFilt {
    public:
        // constructor
        DFirFilt(
            const DMath::DVector<Type>& coefficients,
            size_t filterLength,
            FilterType filterType,
            Type samplingFrequency,
            FilterDesignMethod designMethod);

        // destructor
        ~DFirFilt() {}

        // method to apply the fir filter to an input signal
        DMath::DVector<Type> filterSignal(const DMath::DVector<Type>& inputSignal);
    private:
        // private member variables for filter coefficients, state, ect
        DMath::DVector<Type> m_coefficients;
        DMath::DVector<Type> m_filterState;
        size_t m_filterLength;
        FilterType m_filterType;
        Type m_samplingFrequency;
        FilterDesignMethod m_designMethod;

        // private methods
        // coefficient calculation method
        void calculateCoefficients();

        // method to initialize filter state
        void initializeFilterState();

        // method to update filter state
        void updateFilterState(Type latest_input_sample);

        // method to apply the filter to a single input sample
        Type applyFilter(const DMath::DVector<Type>& inputSignal, size_t index);
    };
}