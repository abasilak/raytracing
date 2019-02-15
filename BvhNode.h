#ifndef __BVH_NODE_H__
#define __BVH_NODE_H__

#include "Aabb.h"
#include "Object.h"

class BVH_Node : public Object {

private:

    AABB         m_aabb;
    Object      *m_node_left;
    Object      *m_node_right;

public:
    explicit BVH_Node() : m_node_left(nullptr), m_node_right(nullptr) { };
    explicit BVH_Node(Object **list, int size, float t_start, float t_end);
    ~BVH_Node() { m_node_left = nullptr; m_node_right = nullptr; }

    virtual bool Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const override;
    virtual bool CreateBoundingBox(float t_start, float t_end, AABB& aabb) const override;
};

#endif