#ifndef __SCENE_H__
#define __SCENE_H__

#include "Sphere.h"
#include "ObjectList.h"
#include "BvhNode.h"

class Scene
{

private:

    Material  **m_materials;
    int         m_materials_size;

    Object    **m_objects;
    int         m_objects_size;

public:

    explicit Scene() : m_materials(nullptr), m_materials_size(0), m_objects(nullptr), m_objects_size(0) { };
    explicit Scene(int materials_size, int objects_size);
    ~Scene();

    Object *Create(void);
};

#endif 