#include "Sphere.h"

Vec3
Sphere::GetCenter(float t) const
{
    Vec3 m_center_end = m_center + Vec3(0.0f, 2.0f*m_radius*drand48(), 0.0f);

    return (!m_animated || (t <= m_animation_start)) ? m_center :
    m_center + ((std::min(t, m_animation_end) - m_animation_start)/(m_animation_end - m_animation_start)) * (m_center_end - m_center);
}

bool
Sphere::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const
{
    Vec3  _center = GetCenter(ray.GetTime());

    Vec3  oc = ray.GetOrigin() - _center;
    float a  = dot(ray.GetDirection(), ray.GetDirection());
    float b  = dot(oc, ray.GetDirection());
    float c  = dot(oc, oc) - m_radius*m_radius;
    float discriminant = b*b - a*c;

    if (discriminant > 0) {
        float _t;
        float _neg_ba  = -b/a;
        float _sqrt_da = sqrt(discriminant)/a;
        
        _t = _neg_ba - _sqrt_da;
        if (_t < t_max && _t > t_min) {

            hit_record.m_t        = _t;
            hit_record.m_point    = ray.GetPoint(_t);
            hit_record.m_normal   = (hit_record.m_point - _center) / m_radius;
            hit_record.m_material = m_material;

            return true;
        }
        
        _t = _neg_ba + _sqrt_da;
        if (_t < t_max && _t > t_min) {

            hit_record.m_t        = _t;
            hit_record.m_point    = ray.GetPoint(_t);
            hit_record.m_normal   = (hit_record.m_point - _center) / m_radius;
            hit_record.m_material = m_material;

            return true;
        }
    }
    return false;
}

bool
Sphere::CreateBoundingBox(float t_start, float t_end, AABB& aabb) const
{
    Vec3 _aabb_min = m_center - Vec3(m_radius, m_radius, m_radius);
    Vec3 _aabb_max = m_center + Vec3(m_radius, m_radius, m_radius);

    aabb = AABB(_aabb_min,_aabb_max);

    return true;
}