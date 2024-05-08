/*
  ==============================================================================

    DVecMatOps.cpp
    Created: 7 May 2024 5:19:35am
    Author:  Zubin

  ==============================================================================
*/

#include "DVecMatOps.h"
namespace DMath {
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

    template <typename Type>
    Type DVector<Type>::min() const {
        if (size == 0) {
            return 0;
        }
        Type minValue = data[0];
        for (size_t i = 1; i < size; ++i) {
            if (data[i] < minValue) {
                minValue = data[i];
            }
        }
        return minValue;
    }

    template <typename Type>
    Type DVector<Type>::max() const {
        if (size == 0) {
            return 0;
        }
        Type maxValue = data[0];
        for (size_t i = 1; i < size; ++i) {
            if (data[i] > maxValue) {
                maxValue = data[i];
            }
        }
        return maxValue;
    }

    template <typename Type>
    DVector<Type> DVector<Type>::subVector(size_t start, size_t end) const {
        start = std::min(start, size);
        end = std::min(end, size);

        DVector<Type> subvec;
        size_t subvecSize = end - start;
        subvec.reserve(subvecSize);

        for (size_t i = start; i < end; ++i) {
            subvec.push_back(data[i]);
        }

        return subvec;
    }

    template <typename Type>
    DVector<Type> DVector<Type>::subVector(size_t start) const {
        return subVector(start, size);
    }
}