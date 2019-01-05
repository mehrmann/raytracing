#ifndef SPHEREH
#define SPHEREH

#include "Vec3.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object {
public:
    Sphere() {}
    Sphere(const Vec3& cen, float r, std::shared_ptr<Material> m) : center(cen), radius(r), material(m) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, Hit& rec) const;

    Vec3 center;
    float radius;
    std::shared_ptr<Material> material;
};

/**
 * Ray intersects with Sphere when:
 * O = Ray.origin()
 * D = Ray.direction()
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
bool Sphere::hit(const Ray& Ray, float t_min, float t_max, Hit& rec) const {
    Vec3 oc = Ray.origin() - center;
    float a = dot(Ray.direction(), Ray.direction());
    float b = dot(oc, Ray.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant) ) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = Ray.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }
        temp = (-b + sqrt(discriminant) ) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = Ray.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.material = material;
            return true;
        }
    }
    return false;
}

#endif
