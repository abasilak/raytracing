#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Vec3.h"

class Texture
{

public:
    virtual ~Texture() {};
    
    virtual Vec3 GetValue(float u, float v, const Vec3& pos) const = 0;
};

class ConstantTexture : public Texture
{
private:
    Vec3     m_color;

public:
    explicit ConstantTexture() {};
    explicit ConstantTexture(Vec3 color) : m_color(color) {};
    ~ConstantTexture() {};
    
    virtual Vec3 GetValue(float u, float v, const Vec3& pos) const override {
        return m_color;
    }
};

#endif 
