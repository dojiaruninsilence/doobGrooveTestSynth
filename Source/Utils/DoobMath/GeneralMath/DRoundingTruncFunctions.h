/*
  ==============================================================================

    DRoundingTruncFunctions.h
    Created: 6 May 2024 8:48:07pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

template <typename Type>
class DRoundingTruncFunctions {
    DRoundingTruncFunctions() {}
    ~DRoundingTruncFunctions() {}

    // round to the nearest integer
    Type round(Type x);

    // Round towards negative infinity
    Type floor(Type x);

    // Round towards positive infinity
    Type ceil(Type x);

    // Truncate towards zero
    Type trunc(Type x);
};