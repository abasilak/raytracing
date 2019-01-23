#ifndef __OBJECTLIST_H__
#define __OBJECTLIST_H__

#include "Object.h"

class ObjectList : public Object {

private:
    Object **m_list;
    int      m_size;

public:
    explicit ObjectList() : m_list(nullptr), m_size(0) { }
    explicit ObjectList(Object **l, int n) { m_list = l; m_size = n; }
    ~ObjectList() { m_list = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
};

#endif
