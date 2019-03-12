#include "Scene.h"
#include "Image2D.h"
#include "Utils.h"

Scene::Scene(int materials_size, int textures_size, int objects_size)
: m_materials_size(materials_size), m_textures_size(textures_size) , m_objects_size(objects_size)
{
    m_materials = new Material *[m_materials_size];
    for(int i=0; i<m_materials_size; ++i) {
        m_materials[i] = nullptr;
    }

    m_textures = new Texture *[m_textures_size];
    for(int i=0; i<m_textures_size; ++i) {
        m_textures[i] = nullptr;
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

    for(int i=0; i<m_textures_size; ++i) {
        safe_delete(m_textures[i]);
    }
    safe_array_delete(m_textures);

    for(int i=0; i<m_objects_size; ++i) {
        safe_delete(m_objects[i]);
    }
    safe_array_delete(m_objects);
}

Object *
Scene::Create(void)
{
    int i = 0;
    
    m_textures[i]  = new ConstantTexture(Vec3(0.5f,0.5f,0.5f));
    m_materials[i] = new Lambertian(m_textures[i]);
    m_objects[i]   = new Sphere(Vec3(0.0f,-1000.0f,0.0f), 1000.0f, m_materials[i]);
    i++;

    m_textures[i]  = new ConstantTexture(Vec3(1.0f,1.0f,1.0f));
    m_materials[i] = new Dielectric(m_textures[i], 1.5f);
    m_objects[i]   = new Sphere(Vec3(0.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    m_textures[i]  = new ConstantTexture(Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()));
    m_materials[i] = new Lambertian(m_textures[i]);
    m_objects[i]   = new Sphere(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    m_textures[i]  = new ConstantTexture(Vec3(0.7f, 0.6f, 0.5f));
    m_materials[i] = new Metal(m_textures[i], 0.0f);
    m_objects[i]   = new Sphere(Vec3( 4.0f, 1.0f, 0.0f), 1.0f, m_materials[i]);
    i++;

    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {

            float _radius = 0.25f*RANDOM();
            Vec3  _origin(a + 0.9f*RANDOM(), _radius, b + 0.9f*RANDOM());

            if ((_origin-Vec3(4.0f, _radius, 0.0f)).length() > 0.9f) {
                
                float           _f;
                Vec3            _albedo;
                Material::Type  _material_type;
                float           _material_type_f = RANDOM();
                bool            _animated;

                if (_material_type_f < 0.8f) {
                    _material_type  = Material::Type::lambertian;
                    _albedo         = Vec3(RANDOM()*RANDOM(), RANDOM()*RANDOM(), RANDOM()*RANDOM());
                    _f              = 0.0f;
                    _animated       = true;
                }
                else if (_material_type_f < 0.95f) { 
                    _material_type  = Material::Type::metal;
                    _albedo         = Vec3(0.5f*(1.0f + RANDOM()), 0.5f*(1.0f + RANDOM()), 0.5f*(1.0f + RANDOM()));
                    _f              = 0.5f*RANDOM();
                    _animated       = true;
                }
                else
                {
                    _material_type  = Material::Type::dielectric;
                    _albedo         = Vec3(1.0f, 1.0f, 1.0f);
                    _f              = 1.5f;
                    _animated       = true;
                }

                m_textures[i]  = new ConstantTexture(_albedo);
                m_materials[i] = Material::Create(_material_type, m_textures[i], _f);
                m_objects[i]   = new Sphere(_origin, _radius, m_materials[i], _animated);
                i++;

                if(i == m_objects_size)
                    break;
            }
        }
        if(i == m_objects_size)
            break;
    }
    
    //return new ObjectList(m_objects, i);
    return new BVH_Node(m_objects, i, 0.0f, 1.0f, true);
}
