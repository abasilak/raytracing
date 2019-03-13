#ifndef __SCENE_H__
#define __SCENE_H__

#include "Sphere.h"
#include "Volume.h"
#include "ObjectList.h"
#include "BvhNode.h"

class Scene
{

private:

    Material  **m_materials;
    int         m_materials_size;

    Texture   **m_textures;
    int         m_textures_size;

    Object    **m_objects;
    int         m_objects_size;

public:

    explicit Scene() : m_materials(nullptr), m_materials_size(0), m_textures(nullptr), m_textures_size(0), m_objects(nullptr), m_objects_size(0) { };
    explicit Scene(int materials_size, int textures_size, int objects_size);
    ~Scene();

    Object *Create(void);
};

#endif 
