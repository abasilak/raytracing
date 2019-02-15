#include "BvhNode.h"
#include <stdlib.h>

BVH_Node::BVH_Node(Object **list, int size, float t_start, float t_end)
{
    if(size == 1) {
        m_node_left = m_node_right = list[0];
    } 
    else if(size == 2) {
        m_node_left  = list[0];
        m_node_right = list[1];
    }
    else {
        int _div_size_2 = size/2;
        m_node_left  = new BVH_Node(list              ,        _div_size_2, t_start, t_end);
        m_node_right = new BVH_Node(list + _div_size_2, size - _div_size_2, t_start, t_end);
    }

    AABB _aabb_left, _aabb_right;

    if(!m_node_left->CreateBoundingBox (t_start, t_end, _aabb_left ) ||
       !m_node_right->CreateBoundingBox(t_start, t_end, _aabb_right)) {
           std::cerr << "Bounding Box Creation Error\n";
       }

    m_aabb = AABB::Merge(_aabb_left, _aabb_right);
}

bool
BVH_Node::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const
{

// if ray hits with Node's AABB
    if(m_aabb.Intersect(ray, t_min, t_max)) {

// Check if ray hits with Left child node's AABB
        hit_record_t _hit_record_left;
        bool         _hit_node_left  = m_node_left->Intersect(ray, t_min, t_max, _hit_record_left);

// Check if ray hits with Right child node's AABB
        hit_record_t _hit_record_right;
        bool         _hit_node_right = m_node_right->Intersect(ray, t_min, t_max, _hit_record_right);

// if we have intersection with both nodes
        if(_hit_node_left && _hit_node_right) {
            hit_record = (_hit_record_left.m_t < _hit_record_right.m_t) ? _hit_record_left : _hit_record_right;
            return true;
        }
// if we have intersection with left node
        else if(_hit_node_left) {
            hit_record = _hit_record_left;
            return true;
        }
// if we have intersection with right node
        else if(_hit_node_right) {
            hit_record = _hit_record_right;
            return true;
        }
    }

    return false;
}

bool
BVH_Node::CreateBoundingBox(float t_start, float t_end, AABB& aabb) const
{
    aabb = m_aabb;

    return true;
}