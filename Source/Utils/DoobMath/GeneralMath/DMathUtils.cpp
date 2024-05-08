/*
  ==============================================================================

    DMathUtils.cpp
    Created: 8 May 2024 1:08:00pm
    Author:  Zubin

  ==============================================================================
*/

#include "DMathUtils.h"

#include "DSqrRootAbsFunctions.h"

namespace DMath {
    template <typename Type>
    Type DMathUtils<Type>::sinc(Type x) {
        if (x == Type(0)) {
            return Type(1);
        }
        else {
            return DSqrRootAbsFunctions<Type>::sqrt(x) / x;
        }
    }
}
