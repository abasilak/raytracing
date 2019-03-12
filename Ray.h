#ifndef __RAY_H__
#define __RAY_H__

#include "Vec3.h"

class Ray
{
private:
    Vec3  m_origin;
    Vec3  m_direction;
    float m_time;

public:
    explicit Ray() {}
    explicit Ray(const Vec3& origin, const Vec3& direction, float t) : m_origin(origin), m_direction(direction), m_time(t) { }
    ~Ray(){}

    inline Vec3  GetOrigin(void)     const { return m_origin;                 }
    inline Vec3  GetDirection(void)  const { return m_direction;              }
    inline Vec3  GetPoint(float t)   const { return m_origin + t*m_direction; }
    inline float GetTime(void)       const { return m_time;                   }
};

#endif 