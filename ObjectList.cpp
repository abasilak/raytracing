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