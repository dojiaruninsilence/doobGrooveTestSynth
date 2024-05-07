/*
  ==============================================================================

    DVecMatOps.cpp
    Created: 7 May 2024 5:19:35am
    Author:  Zubin

  ==============================================================================
*/

#include "DVecMatOps.h"

template <typename Type>
void DVector<Type>::push_back(const Type& value) {
    if (size >= capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

template <typename Type>
void DVector<Type>::push_back(const Type* values, size_t numValues) {
    for (size_t i = 0; i < numValues; ++i) {
        push_back(values[i]);
    }
}

template <typename Type>
void DVector<Type>::push_back(const DVector<Type>& otherVector) {
    for (size_t i = 0; i < otherVector.getSize(); ++i) {
        push_back(otherVector[i]);
    }
}

template <typename Type>
void DVector<Type>::reserve(size_t newCapacity) {
    if (newCapacity > capacity) {
        Type* newData = new Type[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}