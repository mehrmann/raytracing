#ifndef MATERIALH
#define MATERIALH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "util.h"

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
    metal(vec3<T> a, T f) : albedo(a) { 
        if (f < 1) {
            fuzz = f;
        } else {
            fuzz = 1;
        }
    }
    virtual bool scatter(const ray<T>& ray_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const {
        vec3<T> reflected = reflect(unitVector(ray_in.direction()), rec.normal);
        scattered = ray<T>(rec.p, reflected + fuzz * randomInUnitSphere<T>());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    vec3<T> albedo;
    T fuzz;
};

template <typename T>
class dielectric : public material<T> {
public:
    dielectric(T ri) : ref_idx(ri) {}
    virtual bool scatter(const ray<T>& ray_in, const hit_record<T>& rec, vec3<T>& attenuation, ray<T>& scattered) const {
        vec3<T> outward_normal;
        vec3<T> reflected = reflect(unitVector(ray_in.direction()), rec.normal);
        T ni_over_nt;
        attenuation = vec3<T>(1.0, 1.0, 1.0);
        vec3<T> refracted;
        T reflect_prob;
        T cosine;
        if (dot(ray_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
        } else {    
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
        }
        if (refract(ray_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            scattered = ray<T>(rec.p, reflected);
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob) {
            scattered = ray<T>(rec.p, reflected);
        } else {
            scattered = ray<T>(rec.p, refracted);
        }
        return true;
    }

    T ref_idx;
};

#endif