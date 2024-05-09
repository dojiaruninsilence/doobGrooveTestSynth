/*
  ==============================================================================

    DSqrRootAbsFunctions.h
    Created: 6 May 2024 8:45:08pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

namespace DMath {
    template <typename Type>
    class DSqrRootAbsFunctions {
    public:
        // calculate the square root of x
        static Type sqrt(Type x);

        // calculate the absolute value of x
        static Type abs(Type x);
    };
}