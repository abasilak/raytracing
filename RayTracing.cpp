#include "Utils.h"
#include "RayTracing.h"

#define RT_MAX_DEPTH           50
#define RT_MIN_INTERSECTION_T  0.001f

Vec3
compute_gamma_corrected_color(const Vec3& _color, float _gamma)
{
    return Vec3(powf(_color[0], _gamma), powf(_color[1], _gamma), powf(_color[2], _gamma));
}

Vec3
compute_background_color(const Ray& ray)
{
    // Background color
    const Vec3  _a(0.0f,0.0f,0.0f);
    const Vec3  _b(0.05f,0.05f,0.05f);

    const Vec3  _unit_dir = unit_vector(ray.GetDirection());  
    const float _t = 0.5f * (_unit_dir.y() + 1.0f); // [-1,1] -> [0,1]

    return lerp(_a, _b, _t);
}

Vec3
compute_sample_color(const Ray& ray, Object *list, int depth)
{
    hit_record_t _hit_record;
    if(list->Intersect(ray, RT_MIN_INTERSECTION_T, std::numeric_limits<float>::max(), _hit_record)) {
        Ray  _scattered;
        Vec3 _attenuation;
		Vec3 _emitted = _hit_record.m_material->Emitted(_hit_record.m_point, _hit_record.m_u, _hit_record.m_v);
        if (depth < RT_MAX_DEPTH && _hit_record.m_material->Scatter(ray, _hit_record, _attenuation, _scattered)) {
            return _emitted + _attenuation * compute_sample_color(_scattered, list, depth+1);
        }
        else {
            return _emitted;
        }
    }

    return compute_background_color(ray);
}