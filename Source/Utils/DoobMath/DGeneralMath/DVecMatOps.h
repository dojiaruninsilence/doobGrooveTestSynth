/*
  ==============================================================================

    DVecMatOps.h
    Created: 7 May 2024 5:19:35am
    Author:  Zubin

  ==============================================================================
*/

#pragma once

namespace DMath {
    template <typename Type>
    class DVec2 {
    public:
        Type x, y;

        DVec2(Type x = Type(), Type y = Type()) : x(x), y(y) {}
    };

    template <typename Type>
    class DVec3 {
    public:
        Type x, y, z;

        DVec3(Type x = Type(), Type y = Type(), Type z = Type()) : x(x), y(y), z(z) {}
    };

    template <typename Type>
    class DVec4 {
    public:
        Type x, y, z, w;

        DVec4(Type x = Type(), Type y = Type(), Type z = Type(), Type w = Type()) : x(x), y(y), z(z), w(w) {}
    };

    template <typename Type>
    class DVector {
    private:
        Type* data; // Pointer to the dynamic array holding the elements
        size_t size; // Number of elements in the vector
        size_t capacity; // Capacity of the dynamic array

    public:
        // constructor
        DVector() : data(nullptr), size(0), capacity(0) {}

        // destructor
        ~DVector() { delete[] data; }

        // method to add an element to the end of the vector
        void push_back(const Type& value);
        void push_back(const Type* values, size_t numValues);
        void push_back(const DVector<Type>& otherVector);

        // method to reserve space for a certain number of elements
        void reserve(size_t newCapacity);

        // method to get the number of elements in the vector
        size_t getSize() const { return size; }
        
        // method to find the minimum and maximum values in the vector
        Type min() const;
        Type max() const;

        // method to resize the vector
        void resize(size_t newSize);
        void resize(size_t newSize, const Type& value);

        DVector<Type> subVector(size_t start, size_t end) const;
        DVector<Type> subVector(size_t start) const;

        // method to set a sub-vector from another vector
        void setSubVector(size_t startIndex, const DVector<Type>& otherVector);

        // method to access elements by index
        Type& operator[](size_t index) { return data[index]; }
        const Type& operator[](size_t index) const { return data[index]; }
    };
}
