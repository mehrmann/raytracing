#ifndef UTILH
#define UTILH

#include "vec3.h"

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

template <typename T>
bool refract(const vec3<T>&v, const vec3<T>&n, T ni_over_nt, vec3<T>& refracted) {
    vec3<T> uv = unitVector(v);
    T dt = dot(uv, n);
    T discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n*dt) - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

template <typename T>
T schlick(T cosine, T ref_idx) {
    T r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}

#endif