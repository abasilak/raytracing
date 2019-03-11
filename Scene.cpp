#include "Scene.h"
#include "Utils.h"

Scene::Scene(int materials_size, int objects_size)
: m_materials_size(materials_size), m_objects_size(objects_size)
{
    m_materials = new Material *[m_materials_size];
    for(int i=0; i<m_materials_size; ++i) {
        m_materials[i] = nullptr;
    }

    m_objects = new Object *[m_objects_size];
    for(int i=0; i<m_objects_size; ++i) {
        m_objects[i] = nullptr;
    }
}

Scene::~Scene()
{
    for(int i=0; i<m_materials_size; ++i) {
        safe_delete(m_materials[i]);
    }
    safe_array_delete(m_materials);

    for(int i=0; i<m_objects_size; ++i) {
        safe_delete(m_objects[i]);
    }
    safe_array_delete(m_objects);
}

Object *
Scene::Create(void)
{
    int i = 0;
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {

            float _radius = 0.25f*drand48();
            Vec3  _origin(a + 0.9f*drand48(), _radius, b + 0.9f*drand48()); 

            if ((_origin-Vec3(4.0f, _radius, 0.0f)).length() > 0.9f) {
                
                float           _f;
                Vec3            _albedo;
                Material::Type  _material_type;
                float           _material_type_f = drand48();
                bool            _animated;

                if (_material_type_f < 0.8f) {
                    _material_type  = Material::Type::lambertian;
                    _albedo         = Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48());
                    _f              = 0.0f;
                    _animated       = false;
                }
                else if (_material_type_f < 0.95f) { 
                    _material_type  = Material::Type::metal;
                    _albedo         = Vec3(0.5f*(1.0f + drand48()), 0.5f*(1.0f + drand48()), 0.5f*(1.0f + drand48()));
                    _f              = 0.5f*drand48();
                    _animated       = false;
                }
                else
                {
                    _material_type  = Material::Type::dielectric;
                    _albedo         = Vec3(1.0f, 1.0f, 1.0f);
                    _f              = 1.5f;
                    _animated       = false;
                }

                m_materials[i] = Material::Create(_material_type, _albedo, _f);
                m_objects[i]   = new Sphere(_origin, _radius, m_materials[i], _animated);
                i++;
            }
        }
    }
    
    m_materials[i] = new Lambertian(Vec3(0.5f,0.5f,0.5f));
    m_objects[i]   = new Sphere(Vec3(0.0f,-1000.0f,0.0f), 1000.0f, m_materials[i]);
    i++;

    m_materials[i] = new Dielectric(Vec3(1.0f, 1.0f, 1.0f), 1.5f);
    m_objects[i]   = new Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    m_materials[i] = new Lambertian(Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()));
    m_objects[i]   = new Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    m_materials[i] = new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.0f);
    m_objects[i]   = new Sphere(Vec3( 4.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    //return new ObjectList(m_objects, i);
    return new BVH_Node(m_objects, i, 0.0f, 1.0f, true);
}
