#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

template <typename T>
class camera {
public:
    camera() : lowerLeftCorner(-2.0, -1.0, -1.0), 
               horizontal(4.0, 0.0, 0.0),
               vertical(0.0, 2.0, 0.0),
               origin(0.0, 0.0, 0.0) {}

    ray<T> getRay(T u, T v) {
        return ray<T>(origin, lowerLeftCorner + u*horizontal + v*vertical);
    }

    vec3<T> lowerLeftCorner;
    vec3<T> horizontal;
    vec3<T> vertical;
    vec3<T> origin;
};

#endif