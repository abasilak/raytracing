#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Object.h"

class Sphere : public Object {

private:
    Vec3      m_center;
    float     m_radius;
    Material *m_material;

public:
    explicit Sphere() : m_material(nullptr) { }
    explicit Sphere(const Vec3& center, float radius, Material *material) : m_center(center), m_radius(radius), m_material(material) { };
    ~Sphere() { m_material = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
};

#endif