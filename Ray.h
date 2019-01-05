#ifndef RAYH
#define RAYH

#include "Vec3.h"

class Ray {
public:
    Ray() {}
    Ray(const Vec3& origin, const Vec3& direction) : o(origin), d(direction) {}
    Vec3 origin() const { return o; }
    Vec3 direction() const { return d; }
    Vec3 pointAtParameter(const float t) const { return o + t*d; }

private:
    Vec3 o;
    Vec3 d;
};

#endif