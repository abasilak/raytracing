#include "Material.h"

float
schlick(float cosine, float ref_idx)
{   
    float  _r0 = (1.0f-ref_idx) / (1.0f+ref_idx); _r0 = _r0*_r0;

    return _r0 + (1.0f-_r0)*powf((1.0f - cosine),5.0f);
}

Material *
Material::Create(Material::Type type, const Vec3& albedo, float f)
{
    if (type == Material::lambertian) {
        return new Lambertian(albedo);
    }
    else if (type == Material::metal) {
        return new Metal(albedo, f);
    }
    else {
        return new Dielectric(albedo, f);
    }
}

bool
Lambertian::Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const
{
    Vec3 _target = hit_record.m_point + hit_record.m_normal + random_in_unit_disk();

    ray_out      = Ray(hit_record.m_point, _target - hit_record.m_point, ray_in.GetTime());
    attenuation  = m_albedo;

    return true;
}

bool
Metal::Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const
{
    Vec3 _reflected = reflect(ray_in.GetDirection(), hit_record.m_normal);
    ray_out         = Ray(hit_record.m_point, _reflected + m_fuzz*random_in_unit_disk(), ray_in.GetTime());
    attenuation     = m_albedo;

    return (dot(_reflected, hit_record.m_normal) > 0.0f);
}

bool
Dielectric::Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const
{
    Vec3 _reflected = reflect(ray_in.GetDirection(), hit_record.m_normal);
    attenuation     = m_albedo; 
    
    float angle;
    float cosine;
    float ni_over_nt;
    Vec3  outward_normal;
    
    if ((angle = dot(ray_in.GetDirection(), hit_record.m_normal)) > 0.0f) {
        outward_normal = -hit_record.m_normal;
        ni_over_nt     = m_ref_idx;
        cosine = angle / ray_in.GetDirection().length(); // cosine *= m_ref_idx;
        cosine = sqrt(1.0f - m_ref_idx*m_ref_idx*(1.0f - cosine*cosine));
    }
    else {
        outward_normal = hit_record.m_normal;
        ni_over_nt     = 1.0f / m_ref_idx;
        cosine         = -angle / ray_in.GetDirection().length();
    }

    Vec3  _refracted;
    float _reflect_prob = 1.0f;
    if (refract(ray_in.GetDirection(), outward_normal, ni_over_nt, _refracted)) {
        _reflect_prob = schlick(cosine, m_ref_idx);
    }

    Vec3  _scattered = (drand48() < _reflect_prob) ? _reflected : _refracted;
    ray_out          = Ray(hit_record.m_point, _scattered, ray_in.GetTime());
    
    return true;
}
