#include "ObjectList.h"

bool
ObjectList::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const {

    hit_record_t temp_hit;
    bool         hit       = false;
    double       t_closest = t_max;

    for (int i = 0; i < m_size; i++) {
        if (m_list[i]->Intersect(ray, t_min, t_closest, temp_hit)) {
            hit        = true;
            t_closest  = temp_hit.m_t;
            hit_record = temp_hit;
        }
    }
    return hit;
}

bool 
ObjectList::CreateBoundingBox(float t_start, float t_end, AABB& aabb) const
{
    if(m_size < 1) {
        return false;
    }

    AABB _temp_aabb;
    if(m_list[0]->CreateBoundingBox(t_start, t_end, _temp_aabb)) {
        aabb = _temp_aabb;
    }
    else {
        return false;
    }

    for (int i = 1; i < m_size; i++) {
        if(!m_list[i]->CreateBoundingBox(t_start, t_end, _temp_aabb)) {
            return false;
        }
        aabb = AABB::Merge(aabb, _temp_aabb);
    }

    return true;
}