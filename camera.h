#ifndef CAMERAH
#define CAMERAH

#include "ray.h"
#include "util.h"

template <typename T>
class camera {
public:
    camera() : lowerLeftCorner(-2.0, -1.0, -1.0), 
               horizontal(4.0, 0.0, 0.0),
               vertical(0.0, 2.0, 0.0),
               origin(0.0, 0.0, 0.0) {}
    
    camera(vec3<T> lookFrom, vec3<T> lookAt, vec3<T> up, float vfov, float aspect, float aperture, float focusDistance) {
        lens_radius = aperture / 2;
        float theta = vfov*M_PI/180;
        T halfHeight = tan(theta/2);
        T halfWidth = aspect * halfHeight;
        origin = lookFrom;
        w = unitVector(lookFrom - lookAt);
        u = unitVector(cross(up, w));
        v = cross(w, u);
        lowerLeftCorner = origin - halfWidth*focusDistance*u - halfHeight*focusDistance*v - focusDistance*w;
        horizontal = 2*halfWidth*focusDistance*u;
        vertical = 2*halfHeight*focusDistance*v;
    }

    ray<T> getRay(T x, T y) {
        vec3<T> rd = lens_radius * randomInUnitDisk<T>();
        vec3<T> offset = u * rd.x() + v * rd.y();
        return ray<T>(origin + offset, lowerLeftCorner + x*horizontal + y*vertical - origin - offset);
    }

    vec3<T> lowerLeftCorner;
    vec3<T> horizontal;
    vec3<T> vertical;
    vec3<T> origin;
    vec3<T> u, v, w;
    T lens_radius;
};

#endif