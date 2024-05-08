/*
  ==============================================================================

    DVectorComplex.h
    Created: 7 May 2024 7:11:39pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <vector>
#include <complex>

namespace DMath {
    template <typename Type>
    class DVectorComplex {
    public:
        // constuctor/destuctor
        DVectorComplex() {}
        ~DVectorComplex() {}

        // add a complex number to the vector
        void push_back(const std::complex<Type>& value);
        void push_back(const std::complex<Type>* values, size_t numValues);
        void push_back(const DVectorComplex<std::complex<Type>>& otherVector);

        // get the number of elements in the vector
        size_t getSize() const { return data.size(); }

        // access a complex number by index
        std::complex<Type>& operator[](size_t index) { return data[index]; }
        const std::complex<Type>& operator[](size_t index) const { return data[index]; }
    private:
        std::vector<std::complex<Type>> data;
    };

    //template class DVectorComplex<float>;
}