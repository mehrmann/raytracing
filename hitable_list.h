#ifndef HITABLELISTH
#define HITABLELISTH

#include <limits>
#include <list>
#include "vec3.h"
#include "ray.h"
#include "hitable.h"

template <typename T>
class hitable_list : public hitable<T>, public std::list< hitable<T>* > {
public:
    virtual bool hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const;

    typedef hitable<T>* tElem_ptr;
};

template <typename T>
bool hitable_list<T>::hit(const ray<T>& r, T t_min, T t_max, hit_record<T>& rec) const {
    hit_record<T> temp_rec;
    bool hitAnything = false;
    T closest_so_far = t_max;
    for (typename std::list< tElem_ptr >::const_iterator i = this->begin(); i != this->end() ; i++) {
        if ((*i)->hit(r, t_min, closest_so_far, temp_rec)) {
            hitAnything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hitAnything;
}

#endif