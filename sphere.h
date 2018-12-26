#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

template<class T>
class sphere : public hitable<T> {
public:
    sphere() {}
    sphere(const vec3<T>& cen, T r) : center(cen), radius(r) {}
    virtual bool hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const;

    vec3<T> center;
    T radius;
};

/**
 * ray intersects with sphere when:
 * O = ray.origin()
 * D = ray.direction()
 * C = center()
 * r = radius
 * 
 * dot(O + t*D - C, O + t*D - C) = r*r
 * t*t*dot(D, D) + 2*t*dot(D, O-C) + dot(O-D, O-D) - r*r = 0
 * 
 * which is a quadratic formula (a*x*x + b*x + c) (with t=x)
 * x = (-b +- sqrt(b*b - 4*a*c))/ 2*a
 * 
 * The discriminant is the part of the quadratic formula under the square root.
 * 
 * we can leave out some 2's
 * 
 */
template <typename T>
bool sphere<T>::hit(const ray<T>& ray, T t_min, T t_max, hit_record<T>& rec) const {
    vec3<T> oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant) ) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = ray.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant) ) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = ray.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif
