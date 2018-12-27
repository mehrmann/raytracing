#ifndef MATERIALH
#define MATERIALH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

template <typename T>
class material {
public:
    virtual bool scatter(const ray<T>& ray_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const = 0;
};

template <typename T>
class lambertian : public material<T> {
public:
    lambertian(vec3<T> a) : albedo(a) {}
    virtual bool scatter(const ray<T>& ray_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const {
        vec3<T> target = rec.p + rec.normal + randomInUnitSphere<T>();
        scattered = ray<T>(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    vec3<T> albedo;
};

template <typename T>
class metal : public material<T> {
public:
    metal(vec3<T> a) : albedo(a) {}
    virtual bool scatter(const ray<T>& ray_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const {
        vec3<T> reflected = reflect(unitVector(ray_in.direction()), rec.normal);
        scattered = ray<T>(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    vec3<T> albedo;
};
#endif