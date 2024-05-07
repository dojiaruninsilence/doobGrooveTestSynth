/*
  ==============================================================================

    DStats.cpp
    Created: 6 May 2024 8:55:37pm
    Author:  Zubin

  ==============================================================================
*/

#include "DStats.h"
#include "DSqrRootAbsFunctions.h"

#include <algorithm>

template <typename Type>
Type DStats<Type>::mean(const DVector<Type>& vector) {
    Type sum = 0;
    for (size_t i = 0; i < vector.getSize(); ++i) {
        sum += vector[i];
    }
    return sum / vector.getSize();
}

template <typename Type>
Type DStats<Type>::standardDeviation(const DVector<Type>& vector) {
    Type meanValue = mean(vector);
    Type sum = 0;
    for (size_t i = 0; i < vector.getSize(); ++i) {
        sum += (vector[i] - meanValue) * (vector[i] - meanValue);
    }
    return DSqrRootAbsFunctions<Type>::sqrt(sum / vector.getSize());
}

template <typename Type>
Type DStats<Type>::variance(const DVector<Type>& vector) {
    Type meanValue = mean(vector);
    Type sum = 0;
    for (size_t i = 0; i < vector.getSize(); ++i) {
        sum += (vector[i] - meanValue) * (vector[i] - meanValue);
    }
    return sum / vector.getSize();
}

template <typename Type>
Type DStats<Type>::median(const DVector<Type>& vector) {
    DVector<Type> sortedVector = vector; 
    std::sort(sortedVector.data, sortedVector.data + sortedVector.size); 

    if (sortedVector.size % 2 == 0) {
        size_t middleIndex1 = sortedVector.size / 2 - 1;
        size_t middleIndex2 = middleIndex1 + 1;
        return (sortedVector[middleIndex1] + sortedVector[middleIndex2]) / static_cast<Type>(2);
    } else {
        size_t middleIndex = sortedVector.size / 2;
        return sortedVector[middleIndex];
    }
}

template <typename Type>
DVector<Type> DStats<Type>::mode(const DVector<Type>& vector) {
    std::unordered_map<Type, size_t> frequencyMap;

    for (size_t i = 0; i < vector.getSize(); ++i) {
        frequencyMap[vector[i]]++;
    }

    size_t maxFrequency = 0;
    for (const auto& pair : frequencyMap) {
        maxFrequency = std::max(maxFrequency, pair.second);
    }

    DVector<Type> modes;
    for (const auto& pair : frequencyMap) {
        if (pair.second == maxFrequency) {
            modes.push_back(pair.first);
        }
    }

    return modes;
}

template <typename Type>
Type DStats<Type>::range(const DVector<Type>& vector) {
    if (vector.getSize() == 0) {
        return Type();
    }

    Type minVal = vector[0];
    Type maxVal = vector[0];

    for (size_t i = 1; i < vector.getSize(); ++i) {
        minVal = std::min(minVal, vector[i]);
        maxVal = std::max(maxVal, vector[i]);
    }

    return maxVal - minVal;
}