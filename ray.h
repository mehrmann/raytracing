#ifndef RAYH
#define RAYH

#include "vec3.h"

template <typename T>
class ray {
public:
    ray() {}
    ray(const vec3<T>& o, const vec3<T>& d) : O(o), D(d) {}
    vec3<T> origin() const { return O; }
    vec3<T> direction() const { return D; }
    vec3<T> pointAtParameter(const T t) const { return O + t*D; }

private:
    vec3<T> O;
    vec3<T> D;
};

#endif