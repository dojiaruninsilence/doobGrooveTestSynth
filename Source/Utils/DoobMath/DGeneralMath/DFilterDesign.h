/*
  ==============================================================================

    DFilterDesign.h
    Created: 8 May 2024 1:34:51pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "DVecMatOps.h"

namespace DMath {
    template <typename Type>
    class DFilterDesign {
    public:
        // design a low pass filter using specified parameters
        static DVector<Type> designLowPassFilter(Type cutoffFrequency, size_t filterOrder, Type samplingFrequency);

        // Design a high-pass filter using specified parameters
        static DVector<Type> designHighPassFilter(Type cutoffFrequency, size_t filterOrder, Type samplingFrequency);
        
        // design a band pass filter using specified parameters
        static DVector<Type> designBandPassFilter(Type lowCutoffFrequency, Type highCutoffFrequency, size_t filterOrder, Type samplingFrequency);
        
        // design a band stop filter using specified parameters
        static DVector<Type> designBandStopFilter(Type lowCutoffFrequency, Type highCutoffFrequency, size_t filterOrder, Type samplingFrequency);
    };
}