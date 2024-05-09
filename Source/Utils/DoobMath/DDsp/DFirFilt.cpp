/*
  ==============================================================================

    DFirFilt.cpp
    Created: 7 May 2024 3:32:44pm
    Author:  Zubin

  ==============================================================================
*/

#include "DFirFilt.h"

#include "DWindowFunc.h"

namespace DDsp {
    template <typename Type>
    DFirFilt<Type>::DFirFilt(const DMath::DVector<Type>& coefficients,
        size_t filterLength,
        FilterType filterType,
        Type samplingFrequency,
        FilterDesignMethod designMethod)
        : m_coefficients(coefficients),
        m_filterLength(filterLength),
        m_filterType(filterType),
        m_samplingFrequency(samplingFrequency),
        m_designMethod(designMethod) {
        // Calculate coefficients and initialize filter state
        calculateCoefficients();
        initializeFilterState();
    }

    template <typename Type>
    DMath::DVector<Type> DFirFilt<Type>::filterSignal(const DMath::DVector<Type>& inputSignal) {
        // create a vector to store the filtered output signal
        DMath::DVector<Type> outputSignal;

        // interate over each sample in the input signal
        for (size_t i = 0; i < inputSignal.getSize(); ++i) {
            // apply the filter to the current input sample and add the filtered sample to the output signal
            outputSignal.push_back(applyFilter(inputSignal, i));

            // update the filter state with the latest input sample
            updateFilterState(inputSignal[i]);
        }

        return outputSignal;
    }

    template <typename Type>
    void DFirFilt<Type>::calculateCoefficients() {
        // clear existing coefficients
        m_coefficients.resize(0);

        // calculate coefficients using hamming window function
        DMath::DVector<Type> window = DDsp::DWindowFunc::hamming(m_filterLength);

        // calculate ideal response based on filter type
        DMath::DVector<Type> idealResponse;
        switch (m_filterType) {
        case FilterType::LOW_PASS:
            // generate ideal low-pass filter response using designLowPassFilter function
            idealResponse = DMath::DFilterDesign<Type>::designLowPassFilter(
                cutoffFrequency, m_filterLength, m_samplingFrequency);
            break;
        case FilterType::HIGH_PASS:
            // generate ideal high-pass filter response using designHighPassFilter function
            idealResponse = DMath::DFilterDesign<Type>::designHighPassFilter(
                cutoffFrequency, m_filterLength, m_samplingFrequency);
            break;
        case FilterType::BAND_PASS:
            // generate ideal band-pass filter response using designBandPassFilter function
            idealResponse = DMath::DFilterDesign<Type>::designBandPassFilter(
                lowCutoffFrequency, highCutoffFrequency, m_filterLength, m_samplingFrequency);
            break;
        case FilterType::BAND_STOP:
            // generate ideal band-stop filter response using designBandStopFilter function
            idealResponse = DMath::DFilterDesign<Type>::designBandStopFilter(
                lowStopFrequency, highStopFrequency, m_filterLength, m_samplingFrequency);
            break;
        }

        // apply window to ideal response
        for (size_t n = 0; n < m_filterLength; ++n) {
            m_coefficients.push_back(window[n] * idealResponse[n]);
        }
    }

    template <typename Type>
    void DFirFilt<Type>::initializeFilterState() {
        // initialize the filter state vector with zeros
        m_filterState.resize(m_filterLength, Type(0));
    }

    template <typename Type>
    void DFirFilt<Type>::updateFilterState(Type latest_input_sample) {
        // shift existing filter state to the left
        for (size_t i = m_filterLength - 1; i > 0; --i) {
            m_filterState[i] = m_filterState[i - 1];
        }

        // update the first element of the filter state with the latest input sample
        m_filterState[0] = latest_input_sample;
    }

    template <typename Type>
    Type DFirFilt<Type>::applyFilter(const DMath::DVector<Type>& inputSignal, size_t index) {
        // ensure that the current index is within the valid range
        if (index >= m_filterLength || index >= inputSignal.getSize()) {
            throw std::out_of_range("Index out of range in applyFilter function");
        }

        Type filteredValue = Type(0);

        // apply the convolution operation
        for (size_t i = 0; i < m_filterLength; ++i) {
            // ensure that the index is within the valid range for the filter state
            size_t stateIndex = index + (m_filterLength - 1) - i;
            if (stateIndex >= m_filterLength) {
                throw std::out_of_range("Filter state index out of range in applyFilter function");
            }

            filteredValue += m_coefficients[i] * m_filterState[stateIndex];
        }

        return filteredValue;
    }
}