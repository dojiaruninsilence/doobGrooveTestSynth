/*
  ==============================================================================

    DRng.cpp
    Created: 7 May 2024 5:21:31am
    Author:  Zubin

  ==============================================================================
*/

#include "DRng.h"
namespace DMath {
    template<typename Type>
    Type DRng<Type>::next(Type min, Type max) {
        if (min > max) {
            std::swap(min, max);
        }

        if (std::is_same<Type, int>{}) {
            min = static_cast<float>(min);
            max = static_cast<float>(max);
            std::uniform_real_distribution<float> dist(min, max);
            int result = static_cast<int>(dist(rng));
            return result;
        }
        else if (std::is_same<Type, float>{}) {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(rng);
        }
        else if (std::is_same<Type, double>{}) {
            std::uniform_real_distribution<double> dist(min, max);
            return dist(rng);
        }
        else if (std::is_same<Type, long double>{}) {
            std::uniform_real_distribution<long double> dist(min, max);
            return dist(rng);
        }
        else {
            return 0;
        }
    }

    template<typename Type>
    Type DRng<Type>::nextGaussian(Type mean, Type stddev) {
        if (std::is_same<Type, int>{}) {
            mean = static_cast<float>(mean);
            stddev = static_cast<float>(stddev);
            std::normal_distribution<float> dist(mean, stddev);
            int result = static_cast<int>(dist(rng));
            return result;
        }
        else if (std::is_same<Type, float>{}) {
            std::normal_distribution<float> dist(mean, stddev);
            return dist(rng);
        }
        else if (std::is_same<Type, double>{}) {
            std::normal_distribution<double> dist(mean, stddev);
            return dist(rng);
        }
        else if (std::is_same<Type, long double>{}) {
            std::normal_distribution<long double> dist(mean, stddev);
            return dist(rng);
        }
        else {
            return 0;
        }
    }

    template<typename Type>
    Type DRng<Type>::nextElement(const DVector<Type>& collection) {
        if (collection.getSize() == 0) {
            throw std::out_of_range("Empty collection");
        }

        std::uniform_int_distribution<size_t> dist(0, collection.getSize() - 1);
        return collection[dist(rng)];
    }

    template<typename Type>
    void DRng<Type>::setSeed(Type seed) {
        rng.seed(seed);
    }
}