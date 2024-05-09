/*
  ==============================================================================

    DFilterDesign.cpp
    Created: 8 May 2024 1:34:51pm
    Author:  Zubin

  ==============================================================================
*/

#include "DFilterDesign.h"
#include "DMathDefines.h"
#include "DTrig.h"

namespace DMath {
    template<typename Type>
    DVector<Type> DFilterDesign<Type>::designLowPassFilter(Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {
        Type wc = (Type(2.0) * cutoffFrequency) / samplingFrequency;

        DVector<Type> filterCoefficients(filterOrder + 1);
        Type sum = Type(0);
        for (size_t n = 0; n <= filterOrder; ++n) {
            Type hn = (n == filterOrder / 2) ? wc / Type(D_PI) : DTrig<Type>::sin(wc * (n - filterOrder / 2)) / (Type(D_PI) * (n - filterOrder / 2));
            filterCoefficients[n] = hn * Type(0.54) - Type(0.46) * DTrig<Type>::cos(Type(2.0) * Type(D_PI) * n / Type(filterOrder));
            sum += filterCoefficients[n];
        }

        for (size_t n = 0; n <= filterOrder; ++n) {
            filterCoefficients[n] /= sum;
        }

        return filterCoefficients;
    }

    template<typename Type>
    DVector<Type> DFilterDesign<Type>::designHighPassFilter(Type cutoffFrequency, size_t filterOrder, Type samplingFrequency) {
        Type wc = (Type(2.0) * cutoffFrequency) / samplingFrequency;

        DVector<Type> filterCoefficients(filterOrder + 1);
        Type sum = Type(0);
        for (size_t n = 0; n <= filterOrder; ++n) {
            Type hn = (n == filterOrder / 2) ? Type(1.0) - wc / Type(D_PI) : -DTrig<Type>::sin(wc * (n - filterOrder / 2)) / (Type(D_PI) * (n - filterOrder / 2));
            filterCoefficients[n] = hn * Type(0.54) - Type(0.46) * DTrig<Type>::cos(Type(2.0) * Type(D_PI) * n / Type(filterOrder));
            sum += filterCoefficients[n];
        }

        for (size_t n = 0; n <= filterOrder; ++n) {
            filterCoefficients[n] /= sum;
        }

        for (size_t n = 0; n <= filterOrder; ++n) {
            filterCoefficients[n] = -filterCoefficients[n];
        }
        filterCoefficients[filterOrder / 2] += Type(1.0);

        return filterCoefficients;
    }

    template<typename Type>
    DVector<Type> DFilterDesign<Type>::designBandPassFilter(Type lowCutoffFrequency, Type highCutoffFrequency, size_t filterOrder, Type samplingFrequency) {
        Type lowwc = (Type(2.0) * lowCutoffFrequency) / samplingFrequency;
        Type highwc = (Type(2.0) * highCutoffFrequency) / samplingFrequency;

        DVector<Type> lowPassCoefficients = designLowPassFilter(highCutoffFrequency, filterOrder, samplingFrequency);

        DVector<Type> highPassCoefficients = designHighPassFilter(lowCutoffFrequency, filterOrder, samplingFrequency);

        DVector<Type> bandPassCoefficients(filterOrder + 1);
        for (size_t n = 0; n <= filterOrder; ++n) {
            bandPassCoefficients[n] = lowPassCoefficients[n] + highPassCoefficients[n];
        }

        return bandPassCoefficients;
    }

    template<typename Type>
    DVector<Type> DFilterDesign<Type>::designBandStopFilter(Type lowStopFrequency, Type highStopFrequency, size_t filterOrder, Type samplingFrequency) {
        Type lowws = (Type(2.0) * lowStopFrequency) / samplingFrequency;
        Type highws = (Type(2.0) * highStopFrequency) / samplingFrequency;

        DVector<Type> highPassCoefficients = designHighPassFilter(lowStopFrequency, filterOrder, samplingFrequency);

        DVector<Type> lowPassCoefficients = designLowPassFilter(highStopFrequency, filterOrder, samplingFrequency);

        DVector<Type> bandStopCoefficients(filterOrder + 1);
        for (size_t n = 0; n <= filterOrder; ++n) {
            bandStopCoefficients[n] = highPassCoefficients[n] + lowPassCoefficients[n];
        }

        return bandStopCoefficients;
    }
}