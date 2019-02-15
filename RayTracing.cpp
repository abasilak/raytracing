#include "RayTracing.h"
#include "Utils.h"

#define MAX_DEPTH           50
#define MIN_INTERSECTION_T  0.001f

Vec3
compute_gamma_corrected_color(const Vec3& _color, float _gamma)
{
    return Vec3(powf(_color[0], _gamma), powf(_color[1], _gamma), powf(_color[2], _gamma));
}

Vec3
compute_background_color(const Ray& ray)
{
    // Background color
    const Vec3  _a(1.0f,1.0f,1.0f);
    const Vec3  _b(0.5f,0.7f,1.0f);

    const Vec3  _unit_dir = unit_vector(ray.GetDirection());  
    const float _t = 0.5f * (_unit_dir.y() + 1.0f); // [-1,1] -> [0,1]

    return lerp(_a, _b, _t);
}

Vec3
compute_sample_color(const Ray& ray, Object *list, int depth)
{
    hit_record_t _hit_record;
    if(list->Intersect(ray, MIN_INTERSECTION_T, MAXFLOAT, _hit_record)) {
        Ray  _scattered;
        Vec3 _attenuation;
        if (depth < MAX_DEPTH && _hit_record.m_material->Scatter(ray, _hit_record, _attenuation, _scattered)) {
            return _attenuation * compute_sample_color(_scattered, list, depth+1);
        }
        else {
            return Vec3::ColorBlack();
        }
    }

    return compute_background_color(ray);
}