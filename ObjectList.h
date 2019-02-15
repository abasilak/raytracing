#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

#include "Object.h"

class ObjectList : public Object {

private:
    Object **m_list;
    int      m_size;

public:
    explicit ObjectList() : m_list(nullptr), m_size(0) { }
    explicit ObjectList(Object **list, int size) : m_list(list), m_size(size) { }
    ~ObjectList() { m_list = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
    virtual bool CreateBoundingBox(float t_start, float t_end, AABB& aabb) const override;
};

#endif
