/*
  ==============================================================================

    DVectorComplex.cpp
    Created: 7 May 2024 7:11:39pm
    Author:  Zubin

  ==============================================================================
*/

#include "DVectorComplex.h"

namespace DMath {
    template <typename Type>
    void DVectorComplex<Type>::push_back(const std::complex<Type>& value) {
        //value = static_cast<std::complex<float>>(value);
        data.push_back(value);
    }

    template <typename Type>
    void DVectorComplex<Type>::push_back(const std::complex<Type>* values, size_t numValues) {
        for (size_t i = 0; i < numValues; ++i) {
            push_back(values[i]);
        }
    }

    template <typename Type>
    void DVectorComplex<Type>::push_back(const DVectorComplex<std::complex<Type>>& otherVector) {
        for (size_t i = 0; i < otherVector.getSize(); ++i) {
            push_back(otherVector[i]);
        }
    }
}