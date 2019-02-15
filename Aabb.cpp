#include "Aabb.h"

bool
AABB::Intersect(const Ray& ray, float t_min, float t_max) const
{

// for all axis (x,y,z)
    for(int i=0; i<3; ++i) {
        
// compute t0,t1 overlap intervals
        float _inv_d = 1.0f / ray.GetDirection()[i];
        float _t_min = (GetMin()[i] - ray.GetOrigin()[i]) * _inv_d;
        float _t_max = (GetMax()[i] - ray.GetOrigin()[i]) * _inv_d;
        
        if(_inv_d < 0.0f) {
            std::swap(_t_min, _t_max);
        }

        t_min = std::max(_t_min, t_min);
        t_max = std::min(_t_max, t_max);

// no collision in this axis
        if(t_max <= t_min) {
            return false;
        }
    }

// we have overlap on all axes
    return true;
}

AABB
AABB::Merge(const AABB& aabb0, const AABB& aabb1)
{
    Vec3 _min = Vec3(
        std::min(aabb0.GetMin().x(), aabb1.GetMin().x()),
        std::min(aabb0.GetMin().y(), aabb1.GetMin().y()),
        std::min(aabb0.GetMin().z(), aabb1.GetMin().z()));

    Vec3 _max = Vec3(
        std::max(aabb0.GetMax().x(), aabb1.GetMax().x()),
        std::max(aabb0.GetMax().y(), aabb1.GetMax().y()),
        std::max(aabb0.GetMax().z(), aabb1.GetMax().z()));

    return AABB(_min, _max);
}