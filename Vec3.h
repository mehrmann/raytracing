#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3 {
    public:
    Vec3() {}
    Vec3(float x, float y, float z) : e0(x), e1(y), e2(z) {}
    
    //access and inversion
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-x, -y, -z); }
    
    //basic math
    inline Vec3& operator+=(const Vec3& other);
    inline Vec3& operator-=(const Vec3& other);
    inline Vec3& operator*=(const Vec3& other);
    inline Vec3& operator/=(const Vec3& other);

    inline Vec3& operator*=(const float f);
    inline Vec3& operator/=(const float f);

    inline float length() const {
        return sqrt(x * x + y * y + z * z);
    }
    inline float squaredLength() const {
        return x * x + y * y + z * z;
    }

    inline void makeUnitVector();
    
    union {
        float e0;
        float x;
        float r;
    };
    union {
        float e1;
        float y;
        float g;
    };
    union {
        float e2;
        float b;
        float z;
    };


};

inline Vec3& Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

inline Vec3& Vec3::operator*=(const float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

inline Vec3& Vec3::operator/=(const float f) {
    float k = 1.0 / f;
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

inline void Vec3::makeUnitVector() {
    *this /= length();
}

inline std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x,
                   a.y + b.y,
                   a.z + b.z);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x,
                   a.y - b.y,
                   a.z - b.z);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b) {
    return Vec3(a.x * b.x,
                   a.y * b.y,
                   a.z * b.z);
}

inline Vec3 operator/(const Vec3& a, const Vec3& b) {
    return Vec3(a.x / b.x,
                   a.y / b.y,
                   a.z / b.z);
}

inline Vec3 operator*(const float f, const Vec3& v) {
    return Vec3(v.x * f,
                   v.y * f,
                   v.z * f);
}

inline Vec3 operator*(const Vec3& v, const float f) {
    return Vec3(v.x * f,
                v.y * f,
                v.z * f);
}

/**
 * dot product
 * aka scalar product or inner product
 * 
 * if the dot product of two non zero vectors is zero, then these vectors are orthogonal
 */
inline float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x +
           a.y * b.y +
           a.z * b.z;
}

/**
 * cross product
 * aka vector product
 * 
 * given two linearly independent vectors the cross product is a vector that is
 * perpendicular to both vectors and thus normal to the plane containing them.
 * 
 * If two vectors have the same direction, are exact opposite, or one of them has zero length
 * then their cross product is zero.
 */
inline Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3( (a.y * b.z - a.z * b.y),
                -(a.x * b.z - a.z * b.x),
                 (a.x * b.y - a.y * b.x));
}

inline Vec3 operator/(const Vec3& v, const float f) {
    const float k = 1.0/f;
    return Vec3(v.x * k,
                v.y * k,
                v.z * k);
}

inline Vec3 unitVector(const Vec3& v) {
    return v / v.length();
}

#endif