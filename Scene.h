#ifndef __SCENE_H__
#define __SCENE_H__

#include "Sphere.h"
#include "ObjectList.h"

class Scene
{

private:

    Material  **m_materials;
    int         m_materials_size;

    Object    **m_objects;
    int         m_objects_size;

public:

    explicit Scene(int materials_size, int objects_size);
    ~Scene(void);

    ObjectList *Create(void);
};

#endif 