#ifndef HITABLEH
#define HITABLEH

#include "vec3.h"
#include "ray.h"

template <typename T> class material;

template <typename T>
struct hit_record {
    T t;
    vec3<T> p;
    vec3<T> normal;
    material<T> *material;
};

template <typename T>
class hitable {
public:
    virtual bool hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const = 0;
};

#endif