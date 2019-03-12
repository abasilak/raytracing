#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Ray.h"
#include "Texture.h"
#include "Ray.h"

struct hit_record_t
{
    float           m_t;
    Vec3            m_point;
    Vec3            m_normal;
    class Material *m_material;
};

class Material
{
protected:
    Texture        *m_albedo;

public:
    enum Type { lambertian, metal, dielectric };

    explicit Material(Texture *albedo) : m_albedo(albedo) { }
    virtual ~Material() { }

    static Material *Create(Material::Type type, Texture *albedo, float f);

    virtual bool Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const = 0;
};

class Lambertian : public Material
{

public:
    explicit Lambertian(Texture *albedo) : Material(albedo) { }
    ~Lambertian() { }

    virtual bool Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const override;
};

class Metal : public Material
{
private:
    float    m_fuzz;

public:
    explicit Metal(Texture *albedo, float fuzz) : Material(albedo) { m_fuzz = (fuzz < 1.0f) ? fuzz : 1.0f; }
    ~Metal() { }

    virtual bool Scatter(const Ray& ray_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const override;
};

class Dielectric : public Material { 

private:
    float m_ref_idx;
public:
    explicit Dielectric(Texture *albedo, float ref_idx) : Material(albedo), m_ref_idx(ref_idx) { }

    virtual bool Scatter(const Ray& r_in, hit_record_t& hit_record, Vec3& attenuation, Ray& ray_out) const override;
};


#endif 
