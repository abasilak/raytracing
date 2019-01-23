#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Material.h"

class Object {
    public:
        virtual ~Object() {} ;
        virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const = 0;
};

#endif