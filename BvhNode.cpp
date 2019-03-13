#include "Utils.h"
#include "BvhNode.h"
#include <stdlib.h>

BVH_Node::BVH_Node(Object **list, int size, float t_start, float t_end, bool is_root)
{
    m_is_root = is_root;

    if(size == 1) {
        m_node_left = m_node_right = list[0];
        m_is_leaf   = true;
    } 
    else if(size == 2) {
        m_node_left  = list[0];
        m_node_right = list[1];
        m_is_leaf    = true;
    }
    else {
        int _div_size_2 = size/2;
        m_node_left  = new BVH_Node(list              ,        _div_size_2, t_start, t_end);
        m_node_right = new BVH_Node(list + _div_size_2, size - _div_size_2, t_start, t_end);
        m_is_leaf    = false;
    }

    AABB _aabb_left, _aabb_right;
    if(!m_node_left->CreateBoundingBox (t_start, t_end, _aabb_left ) ||
       !m_node_right->CreateBoundingBox(t_start, t_end, _aabb_right)) {
           std::cerr << "Bounding Box Creation Error\n";
    }

    m_aabb = AABB::Merge(_aabb_left, _aabb_right);
}

BVH_Node::~BVH_Node(void)
{
    if(m_is_root) {
        Release(this);
    }
}

void
BVH_Node::Release(Object *node)
{
    if(node == nullptr) {
        return;
    }

    BVH_Node *_node_bvh = dynamic_cast<BVH_Node *>(node);
    if(!_node_bvh->IsLeaf()) {
        Release(_node_bvh->GetNodeLeft());
        Release(_node_bvh->GetNodeRight());
    }
    
    if(!_node_bvh->IsRoot()) {
        safe_delete(_node_bvh);
    }
}

bool
BVH_Node::Intersect(const Ray& ray, float t_min, float t_max, hit_record_t& hit_record) const
{

// if ray hits with Node's AABB
    if(m_aabb.Intersect(ray, t_min, t_max)) {

// if we have intersection with left node
        if(m_node_left->Intersect(ray, t_min, t_max, hit_record)) {
// if we have intersection with both nodes
            m_node_right->Intersect(ray, t_min, hit_record.m_t, hit_record);
            return true;
        } 
// if we have intersection with right node
		else {
            return m_node_right->Intersect(ray, t_min, t_max, hit_record);
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
