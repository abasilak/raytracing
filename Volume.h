#ifndef __VOLUME_H__
#define __VOLUME_H__

#include "Utils.h"
#include "Object.h"
#include "Aabb.h"

class Volume : public Object {

private:
	Object   *m_object;
    Material *m_material;
	float	  m_density;

public:
    explicit Volume() : m_object(nullptr), m_material(nullptr), m_density(0.0f) { }
    explicit Volume(Object *object, Texture *texture, float density) : m_object(object), m_material(new Isotropic(texture)), m_density(density) { }
	~Volume() { m_object = nullptr; m_material = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
    virtual bool CreateBoundingBox(float t_start, float t_end, AABB& aabb) const override;
};

#endif
