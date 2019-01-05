#ifndef MATERIALH
#define MATERIALH

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"
#include "Util.h"

class Material {
public:
    virtual bool scatter(const Ray& Ray_in, const Hit& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

class Lambert : public Material {
public:
    Lambert(Vec3 a) : albedo(a) {}
    virtual bool scatter(const Ray& Ray_in, const Hit& rec, Vec3& attenuation, Ray& scattered) const {
        Vec3 target = rec.p + rec.normal + randomInUnitSphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vec3 albedo;
};

class Metal : public Material {
public:
    Metal(Vec3 a, float f) : albedo(a) { 
        if (f < 1) {
            fuzz = f;
        } else {
            fuzz = 1;
        }
    }
    virtual bool scatter(const Ray& Ray_in, const Hit& rec, Vec3& attenuation, Ray& scattered) const {
        Vec3 reflected = reflect(unitVector(Ray_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
    
    Vec3 albedo;
    float fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const Ray& Ray_in, const Hit& rec, Vec3& attenuation, Ray& scattered) const {
        Vec3 outward_normal;
        Vec3 reflected = reflect(unitVector(Ray_in.direction()), rec.normal);
        float ni_over_nt;
        attenuation = Vec3(1.0, 1.0, 1.0);
        Vec3 refracted;
        float reflect_prob;
        float cosine;
        if (dot(Ray_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * dot(Ray_in.direction(), rec.normal) / Ray_in.direction().length();
        } else {    
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(Ray_in.direction(), rec.normal) / Ray_in.direction().length();
        }
        if (refract(Ray_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            scattered = Ray(rec.p, reflected);
            reflect_prob = 1.0;
        }
        if (drand48() < reflect_prob) {
            scattered = Ray(rec.p, reflected);
        } else {
            scattered = Ray(rec.p, refracted);
        }
        return true;
    }

    float ref_idx;
};

#endif