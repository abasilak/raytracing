#include "Sphere.h"

bool
Sphere::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const
{
    Vec3  oc = ray.GetOrigin() - m_center;
    float a  = dot(ray.GetDirection(), ray.GetDirection());
    float b  = dot(oc, ray.GetDirection());
    float c  = dot(oc, oc) - m_radius*m_radius;
    float discriminant = b*b - a*c;

    if (discriminant > 0) {
        float t;
        
        t = (-b - sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {

            hit_record.m_t        = t;
            hit_record.m_point    = ray.GetPoint(t);
            hit_record.m_normal   = (hit_record.m_point - m_center) / m_radius;
            hit_record.m_material = m_material;

            return true;
        }
        
        t = (-b + sqrt(discriminant)) / a;
        if (t < t_max && t > t_min) {

            hit_record.m_t        = t;
            hit_record.m_point    = ray.GetPoint(t);
            hit_record.m_normal   = (hit_record.m_point - m_center) / m_radius;
            hit_record.m_material = m_material;

            return true;
        }

    }
    return false;
}