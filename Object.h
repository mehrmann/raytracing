#ifndef OBJECTH
#define OBJECTH

#include "Vec3.h"
#include "Ray.h"

class Material;

struct Hit {
    float t;
    Vec3 p;
    Vec3 normal;
    std::shared_ptr<Material> material;
};

class Object {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, Hit& rec) const = 0;
};

#endif