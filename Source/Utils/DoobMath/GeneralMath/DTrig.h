/*
  ==============================================================================

    DTrig.h
    Created: 6 May 2024 8:41:48pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include "DMathDefines.h"

template <typename Type>
class DTrig {
public:
    DTrig() {}
    ~DTrig() {}

    // function to convert degrees to radians
    Type degreeToRadians(Type angleDegrees);

    // function to convert radians to degrees
    Type radianToDegrees(Type angleRadians);

    // function to compute the sine of an angle in radians
    Type sin(Type angleRadians);

    // function to compute the sine of an angle in degrees
    Type sinDegrees(Type angleDegrees);

    // function to compute the cosine of an angle in radians
    Type cos(Type angleRadians);

    // function to compute the cosine of an angle in degrees
    Type cosDegrees(Type angleDegrees);

    // function to compute the tangent of an angle in radians
    Type tan(Type angleRadians);

    // function to compute the tangent of an angle in degrees
    Type tanDegrees(Type angleDegrees);
private:

};