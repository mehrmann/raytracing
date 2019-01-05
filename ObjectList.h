#ifndef HITABLELISTH
#define HITABLELISTH

#include <limits>
#include <list>
#include "Vec3.h"
#include "Ray.h"
#include "Object.h"

class ObjectList : public Object, public std::list< std::shared_ptr<Object> > {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, Hit& rec) const;
};

bool ObjectList::hit(const Ray& r, float t_min, float t_max, Hit& rec) const {
    Hit temp_rec;
    bool hitAnything = false;
    float closest_so_far = t_max;
    for (typename std::list< std::shared_ptr<Object> >::const_iterator i = this->begin(); i != this->end() ; i++) {
        if ((*i)->hit(r, t_min, closest_so_far, temp_rec)) {
            hitAnything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hitAnything;
}

#endif