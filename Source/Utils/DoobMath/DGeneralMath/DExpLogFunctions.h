/*
  ==============================================================================

    DExpLogFunctions.h
    Created: 6 May 2024 8:42:43pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

namespace DMath {
    template <typename Type>
    class DExpLogFuntions {
    public:
        DExpLogFuntions() {}
        ~DExpLogFuntions() {}

        // exponetial function
        Type exp(Type x);

        // natural logarithm
        Type log(Type x);

        // base 10 logarithm
        Type log10(Type x);

        // base 2 logarithm
        Type log2(Type x);

        // power function
        Type pow(Type base, Type exponent);
    };
}