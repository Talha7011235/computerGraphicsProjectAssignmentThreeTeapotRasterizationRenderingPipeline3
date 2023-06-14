// Computer Graphics Project Assignment 3 Rasterization Rendering Pipeline
// Vector.h Templated Vector Class
#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <iostream>

template<typename T, unsigned int Size>
struct Vector
{
public:
    Vector();
    Vector(const Vector<T, Size>&);
    Vector(const std::array<T, Size>&);
    virtual ~Vector();

    static Vector<T, Size> zero();
    static Vector<T, Size> one();
    static Vector<T, Size> up();
    static Vector<T, Size> right();
    static Vector<T, Size> forward();

    T& operator[](const unsigned int&);
    const T& operator[](const unsigned int&) const;
    Vector<T, Size> operator +(const Vector<T, Size>&) const;
    Vector<T, Size> operator -(const Vector<T, Size>&) const;

    template<typename U, unsigned int uSize>
    friend Vector<U, uSize> operator *(const float&, const Vector<U, uSize>&);
    Vector<T, Size> operator *(const float&) const;

    template<typename U, unsigned int uSize>
    friend Vector<U, uSize> operator /(const float&, const Vector<U, uSize>&);
    Vector<T, Size> operator /(const float&) const;

    Vector<T, Size>& operator +=(const Vector<T, Size>&);
    Vector<T, Size>& operator -=(const Vector<T, Size>&);
    Vector<T, Size>& operator *=(const float&);
    Vector<T, Size>& operator /=(const float&);
    bool operator ==(const Vector<T, Size>&) const;
    bool operator !=(const Vector<T, Size>&) const;

    static Vector<T, Size> cross(const Vector<T, Size>&, const Vector<T, Size>&);
    static float dot(const Vector<T, Size>&, const Vector<T, Size>&);

    float squareMagnitude() const;
    float magnitude() const;
    float getAngle(const Vector<T, Size>&) const;
    Vector<T, Size> reflect(const Vector<T, Size>&) const;
    Vector<T, Size> refract(const Vector<T, Size>&, const float&) const;

    static Vector<T, Size> normalize(const Vector<T, Size>&);
    static Vector<T, Size> invert(const Vector<T, Size>&);

    static Vector<T, Size> min(const Vector<T, Size>&, const Vector<T, Size>&);
    static Vector<T, Size> max(const Vector<T, Size>&, const Vector<T, Size>&);
    static Vector<T, Size> clamp(const Vector<T, Size>&, const Vector<T, Size>&, const Vector<T, Size>&);
    static Vector<T, Size> lerp(const Vector<T, Size>&, const Vector<T, Size>&, const float&);

    template<typename U, unsigned int uSize>
    friend std::istream& operator >> (std::istream&, Vector<U, uSize>&);

    template<typename U, unsigned int uSize>
    friend std::ostream& operator << (std::ostream&, const Vector<U, uSize>&);

    std::string toString() const;
protected:
    std::array<T, Size> data;
};

#include "Vector.cpp"

typedef Vector<float, 2> Vector2f;
typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;
typedef Vector<int, 2> Vector2i;
typedef Vector<int, 3> Vector3i;

#endif

