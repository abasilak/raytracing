#ifndef __AABB_H__
#define __AABB_H__

#include "Ray.h"

class AABB {

private:

    Vec3      m_min;
    Vec3      m_max;

public:
    explicit AABB() { };
    explicit AABB(const Vec3& a, const Vec3& b) : m_min(a), m_max(b) { };
    ~AABB() { }

    bool Intersect(const Ray& ray, float t_min, float t_max) const;

    inline Vec3  GetMin(void) const { return m_min; }
    inline Vec3  GetMax(void) const { return m_max; }

    static AABB  Merge(const AABB& aabb0, const AABB& aabb1);
};

#endif