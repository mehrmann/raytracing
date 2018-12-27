#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

template <typename T> class vec3 {
    public:
    vec3() {}
    vec3(T x, T y, T z) { e[0]=x; e[1]=y; e[2]=z; }
    
    inline T x() { return e[0]; }
    inline T y() { return e[1]; }
    inline T z() { return e[2]; }
    
    inline T r() { return e[0]; }
    inline T g() { return e[1]; }
    inline T b() { return e[2]; }

    //access and inversion
    inline const vec3<T>& operator+() const { return *this; }
    inline vec3<T> operator-() const { return vec3<T>(-e[0], -e[1], -e[2]); }
    
    //element access
    inline T operator[](int i) const { return e[i]; }
    inline T& operator[](int i) { return e[i]; }

    //basic math
    inline vec3<T>& operator+=(const vec3<T>& v2);
    inline vec3<T>& operator-=(const vec3<T>& v2);
    inline vec3<T>& operator*=(const vec3<T>& v2);
    inline vec3<T>& operator/=(const vec3<T>& v2);

    inline vec3<T>& operator*=(const T f);
    inline vec3<T>& operator/=(const T f);

    inline T length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
    inline T squaredLength() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline void makeUnitVector();

    inline vec3<T> apply(T (*f)(const T& t)) {
        e[0] = f(e[0]);
        e[1] = f(e[1]);
        e[2] = f(e[2]);
    }
    
    T e[3];
};

template <typename T>
inline std::istream& operator>>(std::istream& is, vec3<T>& v) {
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const vec3<T>& v) {
    os << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return os;
}

template <typename T>
inline vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1.e[0] + v2.e[0],
                   v1.e[1] + v2.e[1],
                   v1.e[2] + v2.e[2]);
}

template <typename T>
inline vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1.e[0] - v2.e[0],
                   v1.e[1] - v2.e[1],
                   v1.e[2] - v2.e[2]);
}

template <typename T>
inline vec3<T> operator*(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1.e[0] * v2.e[0],
                   v1.e[1] * v2.e[1],
                   v1.e[2] * v2.e[2]);
}

template <typename T>
inline vec3<T> operator/(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1.e[0] / v2.e[0],
                   v1.e[1] / v2.e[1],
                   v1.e[2] / v2.e[2]);
}

template <typename T>
inline vec3<T> operator*(const T f, const vec3<T>& v) {
    return vec3<T>(v.e[0] * f,
                   v.e[1] * f,
                   v.e[2] * f);
}

template <typename T>
inline vec3<T> operator*(const vec3<T>& v, const T f) {
    return vec3<T>(v.e[0] * f,
                   v.e[1] * f,
                   v.e[2] * f);
}

template <typename T>
inline T dot(const vec3<T>& v1, const vec3<T>& v2) {
    return v1.e[0] * v2.e[0] +
           v1.e[1] * v2.e[1] +
           v1.e[2] * v2.e[2];
}

template <typename T>
inline vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>( (v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
                 (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

template <typename T>
inline vec3<T> operator/(const vec3<T>& v, const float f) {
    const T k = 1.0/f;
    return vec3<T>(v.e[0] * k,
                   v.e[1] * k,
                   v.e[2] * k);
}

template <typename T>
inline vec3<T>& vec3<T>::operator+=(const vec3<T>& v2) {
    e[0] += v2.e[0];
    e[1] += v2.e[1];
    e[2] += v2.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator-=(const vec3<T>& v2) {
    e[0] -= v2.e[0];
    e[1] -= v2.e[1];
    e[2] -= v2.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator*=(const vec3<T>& v2) {
    e[0] *= v2.e[0];
    e[1] *= v2.e[1];
    e[2] *= v2.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator/=(const vec3<T>& v2) {
    e[0] /= v2.e[0];
    e[1] /= v2.e[1];
    e[2] /= v2.e[2];
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator*=(const T f) {
    e[0] *= f;
    e[1] *= f;
    e[2] *= f;
    return *this;
}

template <typename T>
inline vec3<T>& vec3<T>::operator/=(const T f) {
    T k = 1.0 / f;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

template <typename T>
inline void vec3<T>::makeUnitVector() {
    *this /= length();
}

template <typename T>
inline vec3<T> unitVector(const vec3<T>& v) {
    return v / v.length();
}

template <typename T>
inline vec3<T> lerp(const vec3<T>& v1, const vec3<T>& v2, T t) {
    return (T)(1.0-t) * v1 + t * v2;
}

template <typename T>
vec3<T> randomInUnitSphere() {
    vec3<T> p;
    do {
        p = 2.0 * vec3<T>(drand48(), drand48(), drand48()) - vec3<T>(1,1,1);
    } while (p.squaredLength() >= 1.0);
    return p;
}

/**
 * \     /|
 *  \v r/ | B
 *   \ /  |
 *  --*-----
 *     \  |
 *      \v| B
 *       \|
 * 
 * length of B = dot(v,n)
 * direction of B is n
 */
template <typename T>
vec3<T> reflect(const vec3<T>& v, const vec3<T>& n) {
    return v - 2*dot(v,n) * n;
}

#endif