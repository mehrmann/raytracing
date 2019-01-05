#ifndef UTILH
#define UTILH

#include "Vec3.h"

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
Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n) * n;
}

bool refract(const Vec3&v, const Vec3&n, float niOverNt, Vec3& refracted) {
    Vec3 uv = unitVector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - niOverNt*niOverNt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = niOverNt * (uv - n*dt) - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}

Vec3 randomInUnitSphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1,1,1);
    } while (p.squaredLength() >= 1.0);
    return p;
}

Vec3 randomInUnitDisk() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), 0) - Vec3(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}

template <typename X>
inline X lerp(const X& x1, const X& x2, float t) {
    return (1.0-t) * x1 + t * x2;
}

#endif