#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Utils.h"
#include "Object.h"
#include "Aabb.h"

class Sphere : public Object {

private:
    Vec3      m_center;
    Vec3      m_center_end;
    float     m_radius;
    Material *m_material;

    bool      m_animated;
    float     m_animation_start;
    float     m_animation_end;

public:
    explicit Sphere() : m_material(nullptr), m_animated(false) { }
    explicit Sphere(const Vec3& center, float radius, Material *material, bool animated=false, float animation_start=0.0f, float animation_end=1.0f) :
     m_center(center), m_radius(radius), m_material(material), m_animated(animated), m_animation_start(animation_start), m_animation_end(animation_end)
     { m_center_end = m_center + Vec3(0.0f, 2.0f*m_radius*RANDOM_GEN(), 0.0f); }; // random center at 't_end' time
    ~Sphere() { m_material = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
    virtual bool CreateBoundingBox(float t_start, float t_end, AABB& aabb) const override;

    Vec3     GetCenter(float t) const;
	void	 GetUV(const Vec3& pos, float& u, float& v) const;
};

#endif
